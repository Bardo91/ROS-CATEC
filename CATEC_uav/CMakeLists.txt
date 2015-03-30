cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

FILE(GLOB_RECURSE HDRS "include/*.h")

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})


rosbuild_add_library(battery_model src/batterymodel.cpp)

#rosbuild_add_executable(uav_stage src/uav_stage.cpp ${HDRS})

rosbuild_add_executable(uav_gazebo src/uav_gazebo.cpp)
target_link_libraries(uav_gazebo battery_model)

#rosbuild_add_executable(uav_hector_gazebo src/uav_hector.cpp)
rosbuild_add_executable(uav_qnx_hummingbird src/uav_qnx_hummingbird.cpp)
target_link_libraries(uav_qnx_hummingbird battery_model)
rosbuild_add_executable(qnx_hb_state_receiver src/qnx_hb_state_receiver.cpp)

rosbuild_add_library(uav_gazebo_plugin src/uav_gazebo_plugin.cpp)
rosbuild_link_boost(uav_gazebo_plugin thread)
