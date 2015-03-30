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

# Generate messages in the 'msg' folder
rosbuild_genmsg()

#set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#uncomment if you have defined messages
#rosbuild_genmsg()
#uncomment if you have defined services
#rosbuild_gensrv()

FILE(GLOB_RECURSE HDRS "include/*.h")
include_directories(${PROJECT_SOURCE_DIR}/include_ext_mode)

include_directories(${PROJECT_SOURCE_DIR}/src/ext_mode ${PROJECT_SOURCE_DIR}/src/car_controller_ert_rtw)
add_definitions( -DCLASSIC_INTERFACE=1 -DGLNXA32  -O -fPIC -DEXT_MODE=1 -DHAVESTDIO -DINTEGER_CODE=0 -DMAT_FILE=0 -DMODEL=car_controller -DMT=0 -DNCSTATES=0 -DNUMST -DON_TARGET_WAIT_FOR_START=0 -DONESTEPFNC=1 -DTERMFCN=1 -DTID01EQ=0 -DUNIX )

FILE(GLOB ext_mode src/ext_mode/*.c)
rosbuild_add_library(matlab_ext_mode_car  ${ext_mode})

FILE(GLOB model_library src/car_controller_ert_rtw/*.c)
rosbuild_add_library(car_controller ${model_library})

#common commands for building c++ executables and libraries
#rosbuild_add_library(${PROJECT_NAME} src/example.cpp)
#target_link_libraries(${PROJECT_NAME} another_library)
#rosbuild_add_boost_directories()
#rosbuild_link_boost(${PROJECT_NAME} thread)
#rosbuild_add_executable(example examples/example.cpp)
#target_link_libraries(example ${PROJECT_NAME})

rosbuild_add_executable(CATEC_ugv src/ugv.cpp)
target_link_libraries(CATEC_ugv matlab_ext_mode_car car_controller)

rosbuild_add_executable(sendWP src/sendWP.cpp)

rosbuild_add_executable(dynamic_tf src/dynamic_tf.cpp)

