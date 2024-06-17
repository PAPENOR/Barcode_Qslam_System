#include <ros/ros.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "std_msgs/String.h"
#include <vector>
#include "Barcode_Cam/Cam_Barcode.h"
#include "arpa/inet.h"
#include "std_msgs/Bool.h"
#include <yaml-cpp/yaml.h>
#define MESSAGE_FREQ 1
using namespace std;
using namespace ros;
class Barcode_Reader_UI {
private:
    NodeHandle Barcode_Reader;
    Subscriber Param_trigger_Sub;
    Publisher  Param_trigger_Pub;
    Publisher  Barcode_Pub;
    bool Param_Trigger;
    std_msgs::Bool Trigger_msg;
    std::string IP_Address;
    double X_Offset_Param = 0;
    double Y_Offset_Param = 0;
    int Port;
    int Spin_Rate;
    int Len_Name;
    int Sockfd, Portno, n;
public:
    Barcode_Reader_UI(std::string Name);
      ~Barcode_Reader_UI();
    void Param_trigger_Callback(const std_msgs::Bool::ConstPtr& msg);
    void param_loading();
    void Error(const char *msg);
    void Count_The_Value_Of_Coordinate_Word(bool &Coordinate_Word_Positive, int &Single_Word, vector<int> &Pose_Word);
    void QR_Cam_Decoder(string Bar_Code_data, double &Avg_X, double &Avg_Y, double &Avg_Angle, int &Tag_Short_Name);
};

void Barcode_Reader_UI::Error(const char *msg)
{
  // 印出 perror 訊息和輸出錯誤碼，並終止程式
  perror(msg);
  exit(0);
}
void Barcode_Reader_UI::Count_The_Value_Of_Coordinate_Word(bool &Coordinate_Word_Positive, int &Single_Word, vector<int> &Pose_Word) {
  if(Coordinate_Word_Positive == false) {
    Single_Word = Single_Word * -1;                 // 將單詞變成負數
  }
  Pose_Word.push_back(Single_Word);                 // 將單詞加入位值向量中
  ROS_DEBUG_STREAM("Single_Word" << Single_Word);
  Coordinate_Word_Positive = true;                  // 設定下一個單詞為正數
  Single_Word = 0;                                  // 將單詞設為 0，以便下一輪重新統計
}
void Barcode_Reader_UI::QR_Cam_Decoder(string Bar_Code_data, double &Avg_X, double &Avg_Y, double &Avg_Angle, int &Tag_Short_Name)
{
  vector<int> Pose_Ward;
  int Single_Word = 0;
  bool Coordinate_Word_Positive = true;

  for (int j = 0; j < Bar_Code_data.size(); j++)
  {
    int Character_Value = int(char(Bar_Code_data[j]) - '0'); // 取得字元對應的數字
    if (Character_Value >= 0 && Character_Value <= 9) // 若字元對應數字在 0~9 範圍內
    {
        Single_Word = Single_Word * 10 + Character_Value; // 將數字加進暫存的 Single_Word 變數
    }
    else if (Character_Value == -3) // 若字元對應數字為 -3
    {
        Coordinate_Word_Positive = false; // 將座標的正負號設為負
    }
        else if (Character_Value == 11) // 若字元對應數字為 11
    {
        Count_The_Value_Of_Coordinate_Word(Coordinate_Word_Positive, Single_Word, Pose_Ward); // 將目前的 Single_Word 加入座標值向量
    }
        else if (Character_Value == -7) // 若字元對應數字為 -7
    {
        Count_The_Value_Of_Coordinate_Word(Coordinate_Word_Positive, Single_Word, Pose_Ward); // 將目前的 Single_Word 加入座標值向量
        if (Pose_Ward.size() < 4)  // 若座標值向量尺寸小於 4，代表條碼格式不符，輸出警告訊息
        {
            ROS_WARN_STREAM("Lost msg");
        }
        else  // 若座標值向量尺寸正確，則將值存入對應的變數中
        {
            Avg_X = Pose_Ward.at(0) / 10.0;
            Avg_Y = Pose_Ward.at(1) / 10.0;
            Avg_Angle = Pose_Ward.at(2) / 10.0;
            Tag_Short_Name = Pose_Ward.at(3);
        }
        break;  // 跳出迴圈，因為已經解析完整個條碼資料
    }
    else
    {
      //ROS_WARN_STREAM(Bar_Code_data[j]);
      //ROS_WARN_STREAM(Character_Value);
    }
  }
}
void Barcode_Reader_UI::Param_trigger_Callback(const std_msgs::Bool::ConstPtr& msg)
{
    Param_Trigger= msg->data;
}
void Barcode_Reader_UI::param_loading()
{
    Barcode_Reader.param<double>("Barcode_Reader/offsetX",X_Offset_Param,0.0);
    Barcode_Reader.param<double>("Barcode_Reader/offsetY",Y_Offset_Param,0.0);
}
Barcode_Reader_UI::Barcode_Reader_UI(std::string Name)
{
    std::string file_path = "/home/admin1/BarCode_AMR/src/Barcode_Cam/src/barcode_reader.yaml";
    YAML::Node config = YAML::LoadFile("/home/admin1/BarCode_AMR/src/Barcode_Cam/src/barcode_reader.yaml");
    Param_trigger_Sub  = Barcode_Reader.subscribe("/Motion_param_trigger", 10, &Barcode_Reader_UI::Param_trigger_Callback,this);
    Param_trigger_Pub  = Barcode_Reader.advertise<std_msgs::Bool>("/Motion_param_trigger",10);
    Barcode_Pub        = Barcode_Reader.advertise<Barcode_Cam::Cam_Barcode>("/cam_barcode", 10);
    X_Offset_Param = config["offsetX"].as<double>();
    Y_Offset_Param = config["offsetY"].as<double>();
    Barcode_Reader.param<std::string>("Barcode_Reader/ip", IP_Address, "192.125.1.20");
    Barcode_Reader.param("Barcode_Reader/port", Port, 3000);
    Barcode_Reader.param("Barcode_Reader/spin_rate", Spin_Rate, 30);
    Barcode_Reader.param("Barcode_Reader/len_name", Len_Name, 8);
    // 建立 TCP socket 並連線到伺服器
    struct sockaddr_in Serv_Addr;
    memset(&Serv_Addr, 0, sizeof(Serv_Addr));                           // 初始化伺服器位址結構
    Sockfd = socket(AF_INET, SOCK_STREAM, 0);                           // 建立 TCP socket
    if (Sockfd < 0)
    Error("ERROR opening socket");                                      // 若建立 socket 失敗則輸出錯誤訊息
    Serv_Addr.sin_family = AF_INET;                                     // 設定伺服器位址為 IPv4
    Serv_Addr.sin_port = htons(Port);                                   // 設定伺服器連接埠號，並轉換為網路字節序
    char IP_char[16] = {};
    IP_Address.copy(IP_char, IP_Address.size(), 0);                     // 將 IP 位址字串複製到字元陣列中
    Serv_Addr.sin_addr.s_addr = inet_addr(IP_char);                     // 將字元陣列轉換為 IP 位址結構
    if (connect(Sockfd, (struct sockaddr *) &Serv_Addr, sizeof(Serv_Addr)) < 0)
    Error("ERROR connecting");                                          // 連線到伺服器，若連線失敗則輸出錯誤訊息
    char Buffer[256];
    double Avg_X, Avg_Y, Avg_Angle;
    int Tag_Short_Name;
    ROS_INFO("TCPIP_sub is active");
    ros::Rate Loop_Rate(Spin_Rate);                                     // 設定 ROS 迴圈頻率
    Barcode_Cam::Cam_Barcode Barcode_State;                             // 建立 ROS 發布訊息的物件
    while (ros::ok())
    {
      if(Param_Trigger==true)
        {
        param_loading();
        Trigger_msg.data=false;
        Param_trigger_Pub.publish(Trigger_msg);
        }
            bzero(Buffer, 255);                                         // 初始化緩衝區
            n = read(Sockfd, Buffer, 255);                              // 讀取資料
            if (n < 0 || n > 255)
            {                                                           // 判斷資料是否正確讀取
                Error("ERROR reading reply");                           // 若讀取失敗，則顯示錯誤訊息
            }
            else
            {
                ROS_DEBUG_STREAM(Buffer);                                // 若讀取成功，則顯示讀取的資料
                std::string Bar_Code_Data = Buffer;                       // 資料型別轉換
                QR_Cam_Decoder(Bar_Code_Data, Avg_X, Avg_Y, Avg_Angle, Tag_Short_Name); // 解碼 QR 碼
                // 計算位移
                double offset_X_mm = X_Offset_Param;
                double offset_Y_mm = Y_Offset_Param;
                Avg_Angle = Avg_Angle + 180;
                if (Avg_Angle > 360)
                {
                    Avg_Angle = Avg_Angle - 360;
                }
                // 計算平均位置與角度
                Barcode_State.AvgX = Avg_X + (offset_X_mm * cos(Avg_Angle * M_PI / 180) - offset_Y_mm * sin(Avg_Angle * M_PI / 180));
                Barcode_State.AvgY = Avg_Y + (offset_X_mm * sin(Avg_Angle * M_PI / 180) + offset_Y_mm * cos(Avg_Angle * M_PI / 180));
                Barcode_State.Avgangle = Avg_Angle;
                Barcode_State.Short_name = Tag_Short_Name;
                // 設定 header
                Barcode_State.header.frame_id = "/cam_barcode";
                Barcode_State.header.stamp = ros::Time::now();
                // 發佈資訊
                Barcode_Pub.publish(Barcode_State);
            }
            ros::spinOnce(); // 回應 callback 函式
            Loop_Rate.sleep(); // 暫停指定時間
    }
}
Barcode_Reader_UI::~Barcode_Reader_UI()
{

}
int main(int argc, char **argv)
{
    ros::init(argc, argv, "Barcode_Reader");
    Barcode_Reader_UI barcodeReader("Barcode");
    ros::spinOnce(); // 回應 callback 函式
    return 0;
}
