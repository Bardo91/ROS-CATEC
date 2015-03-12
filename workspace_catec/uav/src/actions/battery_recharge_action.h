#ifndef _BATTERY_ACTION_WRAPPER_
#define _BATTERY_ACTION_WRAPPER_

#include<ros/ros.h>
#include<actionlib/server/action_server.h>
#include<catec_actions_msgs/BatteryRechargeAction.h>
#include<common.h>

class BatteryActionWrapper
{

public:
    BatteryActionWrapper(ros::NodeHandle *n):
        as_(*n,"/battery_recharge",false),
        hasGoal(false)
	{
		//Know if have a goal running now
		hasGoal =false;

		//Register callback of the action server.
        as_.registerGoalCallback(boost::bind(&BatteryActionWrapper::goalCB, this, _1));
        as_.registerCancelCallback(boost::bind(&BatteryActionWrapper::preemptCB, this, _1));

        main_loop_timer_ = n->createTimer(ros::Duration(1.0),
                                              boost::bind(&BatteryActionWrapper::mainLoop, this, _1));
        main_loop_timer_.start();

		as_.start();
	}
    ~BatteryActionWrapper()
	{

	}
    void uavUpdateState(StateUAV actual_state)
    {
        //Receive state of uav
        last_state = actual_state;
    }
    bool getHasgoal()
    {
        return hasGoal;
    }
    unsigned int getLastBatteryLevel()
    {
        return battery_seconds_;
    }

private:
    void goalCB(actionlib::ServerGoalHandle<catec_actions_msgs::BatteryRechargeAction> goal_handle)
	{
        if(!hasGoal || last_state != LANDED)
        {
            hasGoal = true;
             this->goal_handle_ = goal_handle;
            goal_handle_.setAccepted();

            this->last_goal_ = *goal_handle.getGoal().get();
            feedback_.state = feedback_.MINIMUM_BATTERY_RECHARGE;
            goal_handle.publishFeedback(feedback_);
            battery_recharge_start_ = ros::Time::now();
        }
        else
        {
            goal_handle.setRejected(result_);
        }

	}
    void preemptCB(actionlib::ServerGoalHandle<catec_actions_msgs::BatteryRechargeAction> goal_handle)
	{
        if(feedback_.state==feedback_.EXTRA_BATTERY_RECHARGE)
        {
            result_.battery_level = (battery_seconds_/(30*60)*100);
            goal_handle.setCanceled(result_);
            hasGoal = false;
        }
	}

   void mainLoop(const ros::TimerEvent& te)
   {
       if(hasGoal)
       {
           battery_seconds_ = (ros::Time::now() - battery_recharge_start_).toSec()*6;
           result_.battery_level = (battery_seconds_/(30*60)*100);

           if(feedback_.state == feedback_.MINIMUM_BATTERY_RECHARGE && (battery_seconds_ > (15*60)))
           {
               feedback_.state = feedback_.EXTRA_BATTERY_RECHARGE;
               goal_handle_.publishFeedback(feedback_);
           }else if(battery_seconds_ > (30*60))
           {
               result_.battery_level = 100;
               goal_handle_.setSucceeded(result_);
               hasGoal = false;
           }
       }
   }

protected:
    actionlib::ActionServer<catec_actions_msgs::BatteryRechargeAction> as_;
    actionlib::ServerGoalHandle<catec_actions_msgs::BatteryRechargeAction> goal_handle_;
    catec_actions_msgs::BatteryRechargeGoal last_goal_;
    catec_actions_msgs::BatteryRechargeResult result_;
    catec_actions_msgs::BatteryRechargeFeedback feedback_;
    unsigned int battery_seconds_;
    bool hasGoal;
    ros::Time battery_recharge_start_;
    StateUAV last_state;
    ros::Timer main_loop_timer_;
};
#endif //_BATTERY_ACTION_WRAPPER_
