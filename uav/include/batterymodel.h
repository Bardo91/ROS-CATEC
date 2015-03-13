#ifndef BATTERYMODEL_H
#define BATTERYMODEL_H
#include <ros/ros.h>

class BatteryModel
{
public:
    BatteryModel(ros::NodeHandle &n);
    void setBatterytime(ros::Duration battery_time);
    unsigned int update(bool scientific_node_enable,bool motors_on);
    void mainLoop(const ros::TimerEvent& te);

private:
    ros::Duration battery_time_;
    bool scientific_node_on_;
    bool motor_on_;
    ros::Timer main_loop_timer_;
};

#endif // BATTERYMODEL_H
