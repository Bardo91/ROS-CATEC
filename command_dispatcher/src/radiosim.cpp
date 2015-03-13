#include <ros/ros.h>
#include <fstream>
#include <actionlib/client/simple_action_client.h>
#include <catec_actions_msgs/GoToWayPointsAction.h>
#include <catec_actions_msgs/LandAction.h>
#include <catec_actions_msgs/TakeOffAction.h>
#include <catec_actions_msgs/TargetAction.h>
#include <catec_msgs/UALStateStamped.h>
#include <catec_msgs/Target.h>
#include <catec_msgs/WayPoint.h>
#include <catec_msgs/WayPointWithCruise.h>
#include <catec_msgs/WayPointWithCruiseStamped.h>
#include <catec_msgs/Position.h>

#include <geometry_msgs/Point.h>

#include <ros/ros.h>
#include <iostream>
#include <cmath>


#include "ros/ros.h"
#include "beginner_tutorials/AddTwoInts.h"

bool receiving(beginner_tutorials::AddTwoInts::Request  &req,
         beginner_tutorials::AddTwoInts::Response &res)
{
  res.sum = req.a + req.b;
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  return true;
}

bool sending(beginner_tutorials::AddTwoInts::Request  &req,
         beginner_tutorials::AddTwoInts::Response &res)
{
  res.sum = req.a + req.b;
  ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_two_ints_server");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("add_two_ints", add);
  ROS_INFO("Ready to add two ints.");
  ros::spin();

  return 0;
}
