#include "barcode_reader_ui.h"
#include "ui_barcode_reader_ui.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

// 條碼讀取UI構造函數
Barcode_Reader_UI::Barcode_Reader_UI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Barcode_Reader_UI),
    trigger_(false)
{
    // 加載配置文件

    YAML::Node config = YAML::LoadFile(file_path);

    // 設置UI
    ui->setupUi(this);
    ui->ip->setText(QString::fromStdString(config["ip"].as<std::string>()));
    ui->port->setText(QString::number(config["port"].as<int>()));
    ui->offsetX->setText(QString::number(config["offsetX"].as<double>()));
    ui->offsetY->setText(QString::number(config["offsetY"].as<double>()));
    ui->offsetW->setText(QString::number(config["offsetW"].as<double>()));

    // 設置計時器
    QTimer *timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &Barcode_Reader_UI::MyTimerSlot);
    timer1->start(100);
}

// 條碼讀取UI析構函數
Barcode_Reader_UI::~Barcode_Reader_UI()
{
    delete ui;
}

// 計時器槽函數
void Barcode_Reader_UI::MyTimerSlot()
{
    ui->Xaxis->setText(QString::number(barcode_state_.AvgX));
    ui->Yaxis->setText(QString::number(barcode_state_.AvgY));
    ui->Zaxis->setText(QString::number(barcode_state_.Avgangle));
    ui->Short_Name->setText(QString::fromStdString(std::to_string(barcode_state_.Short_name)));
    spinOnce();
}

// 參數觸發回調函數
void Barcode_Reader_UI::Param_trigger_Callback(const std_msgs::Bool::ConstPtr& msg)
{
    trigger_ = msg->data;
    trigger_msg_.data = trigger_;
}

// 條碼相機回調函數
void Barcode_Reader_UI::Cam_Barcode_Callback(const Barcode_Cam::Cam_Barcode::ConstPtr& msg)
{
    barcode_state_.AvgX = msg->AvgX;
    barcode_state_.AvgY = msg->AvgY;
    barcode_state_.Avgangle = msg->Avgangle;
    barcode_state_.Short_name = msg->Short_name;
    barcode_state_.Barcode_name = msg->Barcode_name;
    spinOnce();
}

// 初始化參數設置槽函數
void Barcode_Reader_UI::Setting_Init_param()
{
    // 設置參數
    nh_.setParam("Barcode_Reader/offsetX", ui->offsetX->text().toDouble());
    nh_.setParam("Barcode_Reader/offsetY", ui->offsetY->text().toDouble());
    nh_.setParam("Barcode_Reader/offsetW", ui->offsetW->text().toDouble());

    // 加載配置文件
    YAML::Node config = YAML::LoadFile(file_path);

    // 更新配置文件內容
    config["ip"] = ui->ip->text().toStdString();
    config["port"] = ui->port->text().toInt();
    config["offsetX"] = ui->offsetX->text().toDouble();
    config["offsetY"] = ui->offsetY->text().toDouble();
    config["offsetW"] = ui->offsetW->text().toDouble();

    // 保存配置文件
    std::ofstream fout(file_path);
    if (fout.is_open())
    {
        fout << config;
        fout.close();
        ROS_INFO("Values saved to YAML.");
    }
    else
    {
        ROS_ERROR("Error: Failed to open file for writing.");
    }

    // 發布觸發訊息
    trigger_msg_.data = true;
    param_trigger_pub_.publish(trigger_msg_);
}
