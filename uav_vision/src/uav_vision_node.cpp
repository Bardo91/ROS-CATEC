///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	command_uav_node.cpp
//		Author: Pablo R.S.
//		Date: 14/08/2014
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <ros/ros.h>
#include <signal.h>
#include <iostream>
#include <catec_msgs/ControlReferenceRwStamped.h>
#include <catec_msgs/UALStateStamped.h>


//-------- camera includes  ------------------------------------------------
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>

//----------------------------------------------------------------------
//-------- opencv includes -----------------------------------------------
#include <opencv/cv.h>
#include <opencv/highgui.h>

//----------------------------------------------------------------------
//
#include "ImageCatcher.h"
#include "UavCatecRos.h"

#include "vision/ColorSpaceHSV8.h"
#include "vision/BasicTypes.h"
#include "vision/ColorClustering.h"

#include <tf/transform_datatypes.h>

using namespace catec_msgs;
using namespace catec_actions_msgs;
using namespace std;
using namespace cv;
using namespace BOViL;
using namespace BOViL::algorithms;

void visionCallback(const sensor_msgs::Image &_msg){
	ColorClusterSpace *ccs = CreateHSVCS_8c(255, 255, 255);
	std::vector<ImageObject> objects;

	std::vector<uint8_t> imgData = _msg.data;

	ColorClustering<uint8_t>(imgData.data(), _msg.width, _msg.height, 10, objects, ccs);

	Mat img(_msg.height, _msg.width, CV_8UC3, imgData.data());
	imshow("uav_camera", img);
	ROS_INFO("Img showed");
	waitKey(1);
}

//---------------------------------
int main(int argc, char **argv) {
	// 
	if (argc < 2) {
		cout << "This program has one input parameter.\n"<< endl <<
				"The input parameter is the id of uav." << endl;
		return -1;
	}

	// Init ROS
	ros::init(argc, argv, "uav_vision_node");
	// Image source subscriber
	ImageCatcher imgCatcher("/overhead_camera/image_raw", &visionCallback);

	// Class to command uav
	UavCatecROS uav(argv[1]);

	catec_msgs::UALStateStamped last_ual_state, safe_ual_state;
	

	ros::AsyncSpinner spinner_(0);
	spinner_.start();

	//bool positionSentLastTime = false;
	while(ros::ok()) {
		
		if(!uav.hasTakeOff()){
			uav.takeOff();
		}else{
			ControlReferenceRwStamped reference = uav.reference();

			reference.c_reference_rw.position.x = 0.0;
			reference.c_reference_rw.position.y = 0.0;
			reference.c_reference_rw.position.z = 1.5;

			uav.move(reference);
		}

		//~20Hz
		usleep(50000);
	}

	ros::shutdown();
	return 0;
}
