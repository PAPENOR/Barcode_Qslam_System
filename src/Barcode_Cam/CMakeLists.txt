cmake_minimum_required(VERSION 3.0.2)
project(Barcode_Cam)
find_package(catkin REQUIRED)
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
find_package(Qt5 REQUIRED COMPONENTS Widgets )
find_package(yaml-cpp REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SOURCES
    src/barcode_reader_ui.cpp
    )
set(FORMS
    src/barcode_reader_ui.ui
    )

add_message_files(
    FILES
    Cam_Barcode.msg
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
add_executable(Barcode_Reader src/Barcode_Reader.cpp)
target_link_libraries(Barcode_Reader ${catkin_LIBRARIES} ${YAML_CPP_LIBRARIES})
add_dependencies(Barcode_Reader ${Barcode_Cam_EXPORTED_TARGETS})

add_executable          (barcode_reader_ui ${SOURCES} ${FORMS} src/barcode_reader_ui_node.cpp)
target_link_libraries   (barcode_reader_ui Qt5::Widgets)
target_link_libraries   (barcode_reader_ui ${catkin_LIBRARIES} ${YAML_CPP_LIBRARIES})
add_dependencies        (barcode_reader_ui ${Barcode_Cam_EXPORTED_TARGETS})
