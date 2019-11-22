cmake_minimum_required(VERSION 2.8.3)
project(pegasus_gazebo_plugins)
#原来的文件里是没这句的，没这个就会出错
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GAZEBO_CXX_FLAGS}")
# Load catkin and all dependencies required for this package
find_package(catkin REQUIRED COMPONENTS
  roscpp
  gazebo_ros
  control_toolbox
)

# Depend on system install of Gazebo
find_package(gazebo REQUIRED)
find_package(Boost REQUIRED)

catkin_package(
  DEPENDS
    roscpp
    gazebo_ros
    control_toolbox
)

link_directories(${GAZEBO_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${GAZEBO_INCLUDE_DIRS} include)

add_library(pegasus_gazebo_closed_loop_plugin src/closed_loop_plugin.cpp)
target_link_libraries(pegasus_gazebo_closed_loop_plugin ${catkin_LIBRARIES} ${GAZEBO_LIBRARIES})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)

install(TARGETS
  pegasus_gazebo_closed_loop_plugin
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
