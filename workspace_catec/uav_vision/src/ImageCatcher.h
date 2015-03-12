///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		EC-SAFEMOBIL:	PatrollingCV - uav_vision
//			Author:	Pablo R.S.
//			Date:	2015-FEB-18
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef Image_Catcher_H_
#define	Image_Catcher_H_

#include <ros/ros.h>

#include <string>
#include <functional>

// CATEC specific includes
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/Image.h>

class ImageCatcher{
public:
	ImageCatcher(std::string _nodeName, /*std::function<void(const sensor_msgs::Image &msg)> _callback*/ void (*_callback)(const sensor_msgs::Image &msg) );

private:
	ros::Subscriber mSubscriber;
};


#endif // !Image_Catcher_H_
