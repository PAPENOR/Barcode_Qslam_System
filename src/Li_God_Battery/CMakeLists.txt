cmake_minimum_required(VERSION 3.0.2)
project(Li_God_Battery)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    rospy
    std_msgs
    message_generation
    geometry_msgs
    cv_bridge
    image_transport
    genmsg
    sensor_msgs
    tf
)
generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)
catkin_package(
    CATKIN_DEPENDS geometry_msgs std_msgs
)
link_directories( /usr/local/lib)
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)
add_executable(Battery_485_232 src/Battery_485_232.cpp )
target_link_libraries(Battery_485_232 ${catkin_LIBRARIES} modbus)
add_dependencies(Battery_485_232 ${Li_God_Battery_EXPORTED_TARGETS})
