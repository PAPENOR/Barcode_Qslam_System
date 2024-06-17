#ifndef BARCODE_READER_UI_H
#define BARCODE_READER_UI_H

#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <QDialog>
#include <QString>
#include "Barcode_Cam/Cam_Barcode.h"
#include <QThread>
#include <QTimer>

using namespace ros;
using namespace std;

namespace Ui {
class Barcode_Reader_UI;
}

// 條碼讀取UI類別，繼承自QDialog
class Barcode_Reader_UI : public QDialog {
    Q_OBJECT

protected:
    NodeHandle nh_;                    // ROS 節點處理器
    std_msgs::Bool trigger_msg_;       // 觸發消息
    bool trigger_;                     // 觸發標誌

    // ROS 發布者和訂閱者
    Publisher param_trigger_pub_ = nh_.advertise<std_msgs::Bool>("/Motion_param_trigger", 10);
    Subscriber cam_barcode_sub_ = nh_.subscribe("/cam_barcode", 10, &Barcode_Reader_UI::Cam_Barcode_Callback, this);
    Subscriber param_trigger_sub_ = nh_.subscribe("/Motion_param_trigger", 10, &Barcode_Reader_UI::Param_trigger_Callback, this);

    Barcode_Cam::Cam_Barcode barcode_state_;  // 條碼狀態

public:
    std::string file_path = "/home/admin1/BarCode_AMR/src/Barcode_Cam/src/barcode_reader.yaml";
    explicit Barcode_Reader_UI(QWidget *parent = nullptr); // 構造函數
    ~Barcode_Reader_UI();  // 析構函數

public slots:
    void Setting_Init_param();  // 設置初始參數槽函數
    void Cam_Barcode_Callback(const Barcode_Cam::Cam_Barcode::ConstPtr& msg);  // 條碼相機回調槽函數
    void Param_trigger_Callback(const std_msgs::Bool::ConstPtr& msg);  // 參數觸發回調槽函數
    void MyTimerSlot();  // 計時器槽函數

private:
    Ui::Barcode_Reader_UI *ui;  // UI 指針
};

#endif // BARCODE_READER_UI_H
