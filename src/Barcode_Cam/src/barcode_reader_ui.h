#ifndef BARCODE_READER_UI_H
#define BARCODE_READER_UI_H
#include "ros/ros.h"
#include "std_msgs/Bool.h"
#include <QDialog>
#include <QString>
#include "Barcode_Cam/Cam_Barcode.h"
#include <QThread>
#include "QTimer"

using namespace ros;
using namespace std;
namespace Ui
{
class Barcode_Reader_UI;
}
class Barcode_Reader_UI : public QDialog
{
    Q_OBJECT
protected:
    NodeHandle Barcode_Reader;
    std_msgs::Bool Trigger_msg;
    bool trigger;

    ros::Publisher  Param_trigger_Pub  =Barcode_Reader.advertise<std_msgs::Bool>("/Motion_param_trigger",10);
    ros::Subscriber Cam_Barcode = Barcode_Reader.subscribe("/cam_barcode", 10, &Barcode_Reader_UI::Cam_Barcode_Callback, this);
    ros::Subscriber Param_trigger_Sub  = Barcode_Reader.subscribe("/Motion_param_trigger", 10, &Barcode_Reader_UI::Param_trigger_Callback,this);
    bool Param_Trigger = false;
    Barcode_Cam::Cam_Barcode Barcode_state;
    string file_path = "/home/admin1/BarCode_AMR/src/Barcode_Cam/src/barcode_reader.yaml";


public:
    explicit Barcode_Reader_UI(QWidget *parent = nullptr);
    ~Barcode_Reader_UI();
public slots:
   void Setting_Init_param();
   void Cam_Barcode_Callback(const Barcode_Cam::Cam_Barcode::ConstPtr& msg);
   void Param_trigger_Callback(const std_msgs::Bool::ConstPtr& msg);
   void MyTimerSlot();
private:
    Ui::Barcode_Reader_UI *ui;
};

#endif // BARCODE_READER_UI_H
