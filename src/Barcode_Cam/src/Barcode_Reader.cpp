#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include <yaml-cpp/yaml.h>
#include <vector>
#include "Barcode_Cam/Cam_Barcode.h"

#define MESSAGE_FREQ 1

using namespace std;
using namespace ros;

class BarcodeReaderUI {
private:
    NodeHandle nh_;                      // ROS 節點處理器
    Subscriber param_trigger_sub_;       // 參數觸發訂閱者
    Publisher param_trigger_pub_;        // 參數觸發發布者
    Publisher barcode_pub_;              // 條碼發布者
    bool param_trigger_;                 // 參數觸發標誌
    std_msgs::Bool trigger_msg_;         // 觸發訊息
    std::string ip_address_;             // IP 地址
    double x_offset_param_ = 0;          // X 軸偏移參數
    double y_offset_param_ = 0;          // Y 軸偏移參數
    double w_offset_param_ = 0;          // W 軸偏移參數
    int port_;                           // 端口
    int spin_rate_;                      // 自旋速率
    int len_name_;                       // 名稱長度
    int sockfd_, portno_, n_;            // 套接字相關變數
    struct sockaddr_in serv_addr_;       // 服務器地址結構

public:
    BarcodeReaderUI(const std::string& name);
    ~BarcodeReaderUI();
    void paramTriggerCallback(const std_msgs::Bool::ConstPtr& msg);
    void loadParams();
    void handleError(const char *msg);
    void countCoordinateValue(bool &is_positive, int &single_word, vector<int> &pose_words);
    void decodeQRCode(const string& bar_code_data, double &avg_x, double &avg_y, double &avg_angle, int &tag_short_name);
};

void BarcodeReaderUI::handleError(const char *msg) {
    perror(msg); // 輸出錯誤信息
    exit(EXIT_FAILURE); // 終止程序
}

void BarcodeReaderUI::countCoordinateValue(bool &is_positive, int &single_word, vector<int> &pose_words) {
    if (!is_positive) {
        single_word = -single_word; // 如果是負數，將單詞變成負數
    }
    pose_words.push_back(single_word); // 將單詞加入位值向量中
    ROS_DEBUG_STREAM("單詞: " << single_word);
    is_positive = true; // 重置為正數
    single_word = 0; // 單詞歸零
}

void BarcodeReaderUI::decodeQRCode(const string& bar_code_data, double &avg_x, double &avg_y, double &avg_angle, int &tag_short_name) {
    vector<int> pose_words;
    int single_word = 0;
    bool is_positive = true;

    for (char ch : bar_code_data) {
        int char_value = ch - '0'; // 將字符轉換為數字
        if (char_value >= 0 && char_value <= 9) {
            single_word = single_word * 10 + char_value; // 將數字加入單詞中
        } else if (char_value == -3) {
            is_positive = false; // 負數標記
        } else if (char_value == 11) {
            countCoordinateValue(is_positive, single_word, pose_words); // 計算並加入座標值
        } else if (char_value == -7) {
            countCoordinateValue(is_positive, single_word, pose_words); // 計算並加入座標值
            if (pose_words.size() < 4) {
                ROS_WARN_STREAM("Missing_Msg");
            } else {
                avg_x = pose_words[0] / 10.0;
                avg_y = pose_words[1] / 10.0;
                avg_angle = pose_words[2] / 10.0;
                tag_short_name = pose_words[3];
            }
            break;
        }
    }
}

void BarcodeReaderUI::paramTriggerCallback(const std_msgs::Bool::ConstPtr& msg) {
    param_trigger_ = msg->data; // 更新參數觸發標誌
}

void BarcodeReaderUI::loadParams() {
    nh_.param<double>("Barcode_Reader/offsetX", x_offset_param_, 0.0);
    nh_.param<double>("Barcode_Reader/offsetY", y_offset_param_, 0.0);
    nh_.param<double>("Barcode_Reader/offsetW", w_offset_param_, 0.0);
}

BarcodeReaderUI::BarcodeReaderUI(const std::string& name) {
    YAML::Node config = YAML::LoadFile("/home/admin1/Barcode_Qslam_System/src/Barcode_Cam/src/barcode_reader.yaml");
    param_trigger_sub_ = nh_.subscribe("/Motion_param_trigger", 10, &BarcodeReaderUI::paramTriggerCallback, this);
    param_trigger_pub_ = nh_.advertise<std_msgs::Bool>("/Motion_param_trigger", 10);
    barcode_pub_ = nh_.advertise<Barcode_Cam::Cam_Barcode>("/cam_barcode", 10);

    x_offset_param_ = config["offsetX"].as<double>();
    y_offset_param_ = config["offsetY"].as<double>();
    w_offset_param_ = config["offsetW"].as<double>();
    nh_.param<std::string>("Barcode_Reader/ip", ip_address_, "192.125.1.20");
    nh_.param("Barcode_Reader/port", port_, 3000);
    nh_.param("Barcode_Reader/spin_rate", spin_rate_, 30);
    nh_.param("Barcode_Reader/len_name", len_name_, 8);

    memset(&serv_addr_, 0, sizeof(serv_addr_));
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ < 0) handleError("開啟套接字錯誤");

    serv_addr_.sin_family = AF_INET;
    serv_addr_.sin_port = htons(port_);
    serv_addr_.sin_addr.s_addr = inet_addr(ip_address_.c_str());
    if (connect(sockfd_, (struct sockaddr*)&serv_addr_, sizeof(serv_addr_)) < 0) {
        handleError("連接錯誤");
    }

    ROS_INFO("TCPIP_sub 已啟動");
    ros::Rate loop_rate(spin_rate_);
    Barcode_Cam::Cam_Barcode barcode_state;

    while (ros::ok()) {
        if (param_trigger_) {
            loadParams();
            trigger_msg_.data = false;
            param_trigger_pub_.publish(trigger_msg_);
        }

        char buffer[256];
        bzero(buffer, 255);
        n_ = read(sockfd_, buffer, 255);
        if (n_ < 0 || n_ > 255) {
            handleError("讀取回應錯誤");
        } else {
            ROS_DEBUG_STREAM(buffer);
            std::string bar_code_data(buffer);
            double avg_x, avg_y, avg_angle;
            int tag_short_name;
            decodeQRCode(bar_code_data, avg_x, avg_y, avg_angle, tag_short_name);

            double offset_x_mm = x_offset_param_;
            double offset_y_mm = y_offset_param_;
            avg_angle =avg_angle+ w_offset_param_;
            if (avg_angle > 360) {
                avg_angle -= 360;
            }

            barcode_state.AvgX = avg_x + (offset_x_mm * cos(avg_angle * M_PI / 180) - offset_y_mm * sin(avg_angle * M_PI / 180));
            barcode_state.AvgY = avg_y + (offset_x_mm * sin(avg_angle * M_PI / 180) + offset_y_mm * cos(avg_angle * M_PI / 180));
            barcode_state.Avgangle = avg_angle;
            barcode_state.Short_name = tag_short_name;
            barcode_state.header.frame_id = "/cam_barcode";
            barcode_state.header.stamp = ros::Time::now();
            barcode_pub_.publish(barcode_state);
        }

        ros::spinOnce();
        loop_rate.sleep();
    }
}

BarcodeReaderUI::~BarcodeReaderUI() {
    close(sockfd_); // 關閉套接字
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "Barcode_Reader");
    BarcodeReaderUI barcodeReader("Barcode");
    ros::spinOnce();
    return 0;
}
