#include "barcode_reader_ui.h"
#include "ui_barcode_reader_ui.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
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

    int number = barcode_state_.Short_name;
    QString numberStr = QString("%1").arg(number, 8, 10, QChar('0'));
    QString formattedStr = numberStr.mid(0, 4) + "-" + numberStr.mid(4, 4);

    QGraphicsTextItem *textItem = new QGraphicsTextItem(formattedStr);
    QFont font("Arial", 17);
    textItem->setFont(font);
    textItem->setDefaultTextColor(Qt::black);
    textItem->setPos(250, 10);
    int pointsize=10;
    QGraphicsEllipseItem *ellipseItem = new QGraphicsEllipseItem((200-pointsize/2)+barcode_state_.AvgX*4, (200-pointsize/2)-barcode_state_.AvgY*4, pointsize, pointsize);
    // 設置圓形的填充顏色為藍色
    QBrush brush3(Qt::blue);
    ellipseItem->setBrush(brush3);
    // 設置圓形的邊框顏色為黑色
    QPen pen3(Qt::black);
    ellipseItem->setPen(pen3);
    QGraphicsRectItem *rectItem2 = new QGraphicsRectItem(30, 15, 160, 30);
    // 設置方塊的填充顏色為白色
    QBrush brush2(Qt::white);
    rectItem2->setBrush(brush2);
    // 設置方塊的邊框顏色為黑色
    QPen pen2(Qt::white);
    rectItem2->setPen(pen2);
    // 將方塊添加到場景

    QGraphicsRectItem *rectItem = new QGraphicsRectItem(250, 15, 120, 30);
    // 設置方塊的填充顏色為白色
    QBrush brush(Qt::white);
    rectItem->setBrush(brush);
    // 設置方塊的邊框顏色為黑色
    QPen pen(Qt::white);
    rectItem->setPen(pen);
    // 將方塊添加到場景



    QGraphicsPixmapItem *pic = new QGraphicsPixmapItem();
    pic->setPixmap(QPixmap(QString::fromStdString(Data_Matrix_file)));
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addItem(pic);
    scene->addItem(rectItem);
    scene->addItem(rectItem2);
    scene->addItem(textItem);
    scene->addItem(ellipseItem);

    ui->Data_matrix_view->setScene(scene);
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
void Barcode_Reader_UI::Exit()
{
  reject();
}
