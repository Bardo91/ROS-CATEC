cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)
#set(ROS_BUILD_TYPE Coverage)

rosbuild_init()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

#set(BOVIL_SOURCE_PATH /home/bardo91/programming/BOVIL/library/source)
#set(BOVIL_LIB_PATH /home/bardo91/programming/BOVIL/library/prj/linux)
#include_directories(${BOVIL_SOURCE_PATH})
#link_directories(${BOVIL_LIB_PATH})

SET( SOURCES 	src/uav_vision_node.cpp 
				src/UavCatecRos.cpp 
				src/ImageCatcher.cpp 
				src/vision/SegmentedRLEObject.cpp
				src/vision/ColorClusterSpace.cpp
				src/vision/ColorSpaceHSV8.cpp)

#rosbuild_add_executable(uav_vision_node src/uav_vision_node.cpp src/UavCatecRos.cpp src/ImageCatcher.cpp)

rosbuild_add_executable(uav_vision_node ${SOURCES} )

#target_link_libraries(uav_vision_node libBOViL.so)




