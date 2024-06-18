cmake_minimum_required(VERSION 3.0.2)
project(Motec_canopen)
find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  message_generation
  geometry_msgs
  roscpp
  rospy
  std_msgs
  sensor_msgs
  tf
  genmsg
  nav_msgs
)
include_directories(
    include
    ${catkin_INCLUDE_DIRS}
)

# search for all msg files
FILE(GLOB messages_to_build RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/msg"
    "${CMAKE_CURRENT_SOURCE_DIR}/msg/*.msg")

# notify catkin to look at the previously found msg files
add_message_files(
  FILES
  ${messages_to_build}
)


generate_messages(
  DEPENDENCIES actionlib_msgs std_msgs geometry_msgs # Or other packages containing msgs
)

catkin_package(
    CATKIN_DEPENDS actionlib_msgs geometry_msgs roscpp rospy std_msgs
)

add_executable(Can_tran src/Can_tran.cpp src/canalystii.cpp src/canalystii_node.cpp)
add_dependencies(Can_tran ${Motec_canopen_EXPORTED_TARGETS})
target_link_libraries(Can_tran ${PROJECT_SOURCE_DIR}/lib/libcontrolcan.so ${catkin_LIBRARIES})



