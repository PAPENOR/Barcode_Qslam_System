#include "barcode_reader_ui.h"
#include "ui_barcode_reader_ui.h"
#include <yaml-cpp/yaml.h>
#include <fstream>

Barcode_Reader_UI::Barcode_Reader_UI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Barcode_Reader_UI)
{
    YAML::Node config = YAML::LoadFile(file_path);
    ui->setupUi(this);
    ui->ip->setText(QString::fromStdString(config["ip"].as<std::string>()));
    ui->port->setText(QString::number(config["port"].as<double>()));
    ui->offsetX->setText(QString::number(config["offsetX"].as<double>()));
    ui->offsetY->setText(QString::number(config["offsetY"].as<double>()));

    QTimer *timer1 =new QTimer(this);
    connect(timer1,SIGNAL(timeout()),this,SLOT(MyTimerSlot()));
    timer1->start(100);
}
Barcode_Reader_UI::~Barcode_Reader_UI()
{
    delete ui;
}
void Barcode_Reader_UI::MyTimerSlot()
{
  ui->Xaxis->setText(QString::number(Barcode_state.AvgX));
  ui->Yaxis->setText(QString::number(Barcode_state.AvgY));
  ui->Zaxis->setText(QString::number(Barcode_state.Avgangle));
  //ui->Barcode_Name->setText(QString::fromStdString(Barcode_state.Barcode_name));
  ui->Short_Name->setText(QString::fromStdString(std::to_string(Barcode_state.Short_name)));
  spinOnce();
}
void Barcode_Reader_UI::Param_trigger_Callback(const std_msgs::Bool::ConstPtr& msg)
{
  trigger = msg->data;
  Trigger_msg.data = trigger;
}
void Barcode_Reader_UI::Cam_Barcode_Callback(const Barcode_Cam::Cam_Barcode::ConstPtr& msg)
{
    Barcode_state.AvgX=msg->AvgX;
    Barcode_state.AvgY=msg->AvgY;
    Barcode_state.Avgangle=msg->Avgangle;
    Barcode_state.Short_name=msg->Short_name;
    Barcode_state.Barcode_name=msg->Barcode_name;
    spinOnce();
}

void Barcode_Reader_UI::Setting_Init_param()
{
    Barcode_Reader.setParam("Barcode_Reader/offsetX", ui->offsetX->text().toDouble());
    Barcode_Reader.setParam("Barcode_Reader/offsetY", ui->offsetY->text().toDouble());
    YAML::Node config = YAML::LoadFile(file_path);
    config["ip"] = ui->ip->text().toStdString();
    config["port"] = ui->port->text().toDouble();
    config["offsetX"] = ui->offsetX->text().toDouble();
    config["offsetY"] = ui->offsetY->text().toDouble();
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
    Trigger_msg.data=true;
    Param_trigger_Pub.publish(Trigger_msg);
}
