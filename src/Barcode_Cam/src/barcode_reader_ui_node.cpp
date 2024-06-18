#include "ros/ros.h"
#include "barcode_reader_ui.h"
#include "std_msgs/Int64MultiArray.h"
#include <QApplication>
int main(int argc, char *argv[])
{
  ros::init(argc, argv, "barcode_reader_ui");
  ros::NodeHandle nh_;
  QApplication a(argc,argv);
  Barcode_Reader_UI w;
  w.showMaximized();
  return a.exec();
}
