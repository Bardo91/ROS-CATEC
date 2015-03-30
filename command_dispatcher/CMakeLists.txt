cmake_minimum_required(VERSION 2.4.6)
include($ENV{ROS_ROOT}/core/rosbuild/rosbuild.cmake)

# Set the build type.  Options are:
#  Coverage       : w/ debug symbols, w/o optimization, w/ code-coverage
#  Debug          : w/ debug symbols, w/o optimization
#  Release        : w/o debug symbols, w/ optimization
#  RelWithDebInfo : w/ debug symbols, w/ optimization
#  MinSizeRel     : w/o debug symbols, w/ optimization, stripped binaries
#set(ROS_BUILD_TYPE RelWithDebInfo)
set(ROS_BUILD_TYPE Debug)

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

## Add define to tell library that will use ROS definition
 add_definitions(-DINCLUDE_ROS_LIBRARY)

## Compiling GRVC library
set(INCLUDE_GRVC ../libs/grvc_catec/library/src)
rosbuild_add_library(grvc 	${INCLUDE_GRVC}/testbed/control/RosAgent.cpp 
							${INCLUDE_GRVC}/testbed/control/UavCatecRos.cpp 
							${INCLUDE_GRVC}/testbed/control/UgvCatecRos.cpp )

## Compiling Patrolling and tracking test
set(prjName patrolling_and_tracking)
include_directories( ${INCLUDE_GRVC} )

rosbuild_add_boost_directories()
rosbuild_add_executable(${prjName} 	src/patrolling_and_tracking.cpp 
									src/radio.cpp 
									src/quad.cpp )

target_link_libraries	(${prjName}	grvc)

rosbuild_link_boost	(${prjName} 	thread	
					signals	
					system )
