#include "ros/ros.h"
#include <std_msgs/Int64MultiArray.h>
#include <std_msgs/Int16.h>
#include <modbus/modbus.h>

using namespace std;

class ModbusRTUManager
{
public:
    ModbusRTUManager();
private:
    ros::NodeHandle Node;
    ros::Publisher BatteryState;
    ros::Publisher Error_pub;
    string address_port;
    modbus_t *plc;
    int BaudRate, Endmode, Datasize, SlaveID;
    int Now_VoltAddr, Now_AmAddr, Now_AhAddr, Now_Temp1Addr, Now_Temp2Addr, Now_PowerAddr;
    string oddmode;
    std_msgs::Int64MultiArray PowerState;
};

// 读取数据的函数
// PowerState: 存储读取的值的数组
// plc: modbus 连接
// Addr: 寄存器地址
// Unit: 单位值
// offset: 偏移量
int ReadTheData(std_msgs::Int64MultiArray &PowerState, modbus_t *plc, int Addr, int Unit, int offset)
{
    uint16_t bits[1] = {0};
    int ret = modbus_read_registers(plc, Addr, 1, bits);
    int ParamValue = (short)bits[0] * Unit + offset;
    PowerState.data.push_back(ParamValue);
    return ParamValue;
}

// 读取两个地址中较大的一个的函数
// PowerState: 存储读取的值的数组
// plc: modbus 连接
// Addr1: 寄存器地址 1
// Addr2: 寄存器地址 2
// Unit: 单位值
// offset: 偏移量
int ReadTheDataMax(std_msgs::Int64MultiArray &PowerState, modbus_t *plc, int Addr1, int Addr2, int Unit, int offset)
{
    uint16_t bits[1] = {0};
    int ret;
    ret = modbus_read_registers(plc, Addr1, 1, bits);
    int ParamValue1 = -2730;
    ParamValue1 = (short)bits[0] * Unit + offset;
    ret = modbus_read_registers(plc, Addr2, 1, bits);
    int ParamValue2 = -2730;
    ParamValue2 = (short)bits[0] * Unit + offset;
    if (ParamValue1 > ParamValue2)
    {
        PowerState.data.push_back(ParamValue1);
        return ParamValue1;
    }
    else
    {
        PowerState.data.push_back(ParamValue2);
        return ParamValue2;
    }
}

ModbusRTUManager::ModbusRTUManager()
{
  // 初始化ROS发布者，用于发布电池状态到话题上
  BatteryState = Node.advertise<std_msgs::Int64MultiArray>("Cleon/battery_state", 100);
  stringstream Cam_error_name;
  Cam_error_name<<ros::this_node::getName()<<"/Error_Code_Battery";
  Error_pub = Node.advertise<std_msgs::Int16>(Cam_error_name.str(), 10);

  // 从ROS参数服务器中获取Modbus串口地址和波特率等配置参数
  Node.param<std::string>("Battery_485_232/address_port", address_port, "/dev/ttyUSB0");
  Node.param("Battery_485_232/baudrate", BaudRate, 9600);
  Node.param<std::string>("Battery_485_232/Oddmode", oddmode, "N");
  Node.param("Battery_485_232/Endmode", Endmode, 1);
  Node.param("Battery_485_232/Datasize", Datasize, 8);
  Node.param("Battery_485_232/SlaveID", SlaveID, 1);

  // 获取电池组各项状态的Modbus寄存器地址
  Node.param("Battery_485_232/Now_VoltAddr", Now_VoltAddr, 18);
  Node.param("Battery_485_232/Now_AmAddr", Now_AmAddr, 19);
  Node.param("Battery_485_232/Now_AhAddr", Now_AhAddr, 20);
  Node.param("Battery_485_232/Now_Temp1Addr", Now_Temp1Addr, 41);
  Node.param("Battery_485_232/Now_Temp2Addr", Now_Temp2Addr, 42);
  Node.param("Battery_485_232/Now_PowerAddr", Now_PowerAddr, 46);

  bool connect_to_modbus=true;
  bool Battery_error=false;

  // 初始化Modbus RTU串口通信
  uint16_t bits[1] = {0};
  int ret;
  char Oddmode = oddmode.at(0);
  plc = modbus_new_rtu(address_port.c_str(), BaudRate, Oddmode, Datasize, Endmode);
  if (plc == NULL) {
    ROS_FATAL("Unable to allocate libmodbus context\n");
  }
  if (modbus_connect(plc) == -1) {
    ROS_FATAL("Failed to connect to modbus device!!!");
    connect_to_modbus=false;
    ROS_FATAL("%s", modbus_strerror(errno));
    modbus_free(plc);
  }
  else {
    ROS_INFO("Connection to modbus device established");
    connect_to_modbus=true;
  }
  modbus_set_slave(plc, SlaveID);

  // 循环读取电池组状态，并发布到ROS话题上
  ros::Rate loop_rate(30);
  while (ros::ok())
  {
    // 通过 Modbus 读取 PLC 的 48 个寄存器中的数据
    for(int i=0;i<48;i++)
    {
      uint16_t bits[1]={0};
      int ret;
      ret= modbus_read_registers(plc,i,1,bits);
      int ParamValue=(short)bits[0]*1;     
    }

    // 读取电池状态的数据
    PowerState.data.clear();
    // 读取电压
    int PowerVolt =ReadTheData(PowerState,plc,Now_VoltAddr,10,0);
    // 读取电流
    int PowerAm   =ReadTheData(PowerState,plc,Now_AmAddr,10,0);
    // 读取电量
    int PowerAh   =ReadTheData(PowerState,plc,Now_AhAddr,10,0);
    // 读取电池温度
    int PowerTemp =ReadTheDataMax(PowerState,plc,Now_Temp1Addr,Now_Temp2Addr,1,-2731);
    // 读取电池电量百分比
    int Power100  =ReadTheData(PowerState,plc,Now_PowerAddr,1,0);
    // 打印读取到的数据
    if(PowerVolt==0)
    {
    Battery_error=true;
    }
    else
    {
    Battery_error=false;
    }
    ROS_INFO_STREAM("Now_Volt["<<Now_VoltAddr<<"]:"<<PowerVolt<<"mv,Now_Power["<<Now_PowerAddr<<"]"<<Power100<<"%");
    ROS_DEBUG_STREAM("Now_AmAddr["<<Now_AmAddr<<"]:"<<PowerAm<<"mA");
    ROS_DEBUG_STREAM("Now_Ah["<<Now_AhAddr<<"]:"<<PowerAh<<"mA");
    ROS_DEBUG_STREAM("PowerTempMax["<<Now_Temp1Addr<<"]["<<Now_Temp2Addr<<"]:"<<PowerTemp<<"C");
    std_msgs::Int16 Error_pub_msg;
    if (connect_to_modbus == false) {
        Error_pub_msg.data = 1;  // 將Error_pub_msg的數值設為1，表示系統未連接的錯誤碼
        Error_pub.publish(Error_pub_msg);  // 發佈Error_pub_msg到Error_pub主題
    }
    else
    {
        if (Battery_error == true) {
            Error_pub_msg.data = 2;  // 將Error_pub_msg的數值設為1，表示battery未連接的錯誤碼
            Error_pub.publish(Error_pub_msg);  // 發佈Error_pub_msg到Error_pub主題
        }
        else
        {
            Error_pub_msg.data = 0;  // 將Error_pub_msg的數值設為0，表示系統未連接的錯誤碼
            Error_pub.publish(Error_pub_msg);  // 發佈Error_pub_msg到Error_pub主題
        }
    }
    // 发布电池状态话题
    BatteryState.publish(PowerState);
    // 处理 ROS 的回调函数
    ros::spinOnce();
    // 按照指定的频率休眠
    loop_rate.sleep();
  }
  ros::spin();

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "Battery_485_232");
    ModbusRTUManager MTRUM;
    ros::NodeHandle nh;
    return 0;

}
