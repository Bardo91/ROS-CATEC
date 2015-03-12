#ifndef _LAND_ACTION_CLASS
#define _LAND_ACTION_CLASS

class GTWPActionClass
{

public:
	GTWPActionClass(std::string name, std::string uavID) :
		as_(nh_,name,false),
		action_name_(name)
	{
		hasGoal =false;

		as_.registerGoalCallback(boost::bind(&GTWPActionClass::goalCB, this, _1));
		as_.registerCancelCallback(boost::bind(&GTWPActionClass::preemptCB, this, _1));


		uavID_ = uavID;

		last_distance = 125;

		timer = nh_.createTimer(ros::Duration(0.1), &GTWPActionClass::uavUpdate, this);
		actual_way_point = 0;

		string path=uavID;
		path.append("/way_point_callback");
		fp_pub = nh_.advertise<catec_msgs::WayPointWithCruiseStamped> (path.c_str(), 0);


		path = uavID;
		path.append("/ual_state");
		subCommandFlags = nh_.subscribe(path.c_str(), 0, &GTWPActionClass::positionUpdate, this);

		as_.start();

	}

	~GTWPActionClass()
	{

	}
	void goalCB(actionlib::ServerGoalHandle<catec_actions_msgs::GoToWayPointsAction> goal_handle)
	{

		//TakeOff advertise;
		if(hasGoal)
		{
			goal_handle.setRejected();
		}
		else
		{
			goal_handle_ = goal_handle;
			hasGoal = true;
			actual_way_point = 0;
			goal_handle.setAccepted();
		}

	}
	void preemptCB(actionlib::ServerGoalHandle<catec_actions_msgs::GoToWayPointsAction> goal_handle)
	{
		//Try to cancel callback
		//Ignore actually cant cancel take off action.
	}
	void uavUpdate(const ros::TimerEvent& te)
	{

		if(hasGoal)
		{
			catec_msgs::Position v_distance;
			v_distance.x = goal_handle_.getGoal().get()->way_points[actual_way_point].way_point.x - actual_position.x;
			v_distance.y = goal_handle_.getGoal().get()->way_points[actual_way_point].way_point.y - actual_position.y;
			v_distance.z = goal_handle_.getGoal().get()->way_points[actual_way_point].way_point.z - actual_position.z;

			double distance = sqrt(pow(v_distance.x,2) + pow(v_distance.y,2) +pow(v_distance.z,2));

			if(distance < 0.9)
			{
				actual_way_point++;
				last_distance = 125;

				if(actual_way_point >= goal_handle_.getGoal().get()->size)
				{
					//Hemos terminado con todos los wayPoints

					hasGoal = false;
					catec_actions_msgs::GoToWayPointsResult res;
					res.final_position.header.frame_id = string("path_planner");
					res.final_position.header.stamp = ros::Time::now();

					res.final_position.position.valid = 1;
					res.final_position.position.x = actual_position.x;
					res.final_position.position.y = actual_position.y;
					res.final_position.position.z = actual_position.z;

					goal_handle_.setSucceeded(res);
				}

			}
			else if((last_distance) > (distance + 0.5))
			{
				last_distance = distance;

				feedback_.way_point = goal_handle_.getGoal().get()->way_points[actual_way_point];
				feedback_.distance_to_goal = distance;
				feedback_.distance_to_next_waypoint = distance;

				goal_handle_.publishFeedback(feedback_);


			}


			//Enviamos el flightplan

			catec_msgs::WayPointWithCruiseStamped fp;

			fp.header.frame_id="temporal_wpa";
			fp.header.stamp = ros::Time::now();
			fp.header.seq = 0;


			fp.way_point.x = goal_handle_.getGoal().get()->way_points[actual_way_point].way_point.x;
			fp.way_point.y = goal_handle_.getGoal().get()->way_points[actual_way_point].way_point.y;
			fp.way_point.z = goal_handle_.getGoal().get()->way_points[actual_way_point].way_point.z;
			fp.way_point.cruise = goal_handle_.getGoal().get()->way_points[actual_way_point].way_point.cruise;

			if(hasGoal)
			{
				fp_pub.publish(fp);
			}


		}

	}
	void positionUpdate(const catec_msgs::UALStateStamped::ConstPtr& state)
	{
		actual_position = state->ual_state.dynamic_state.position;
	}
protected:

	ros::NodeHandle nh_;
	actionlib::ActionServer<catec_actions_msgs::GoToWayPointsAction> as_;
	actionlib::ServerGoalHandle<catec_actions_msgs::GoToWayPointsAction> goal_handle_;
	ros::Publisher fp_pub;
	ros::Subscriber pos_sub;
	bool hasGoal;
	std::string action_name_;
	catec_actions_msgs::GoToWayPointsFeedback feedback_;
	catec_actions_msgs::GoToWayPointsResult result_;
	std::string uavID_;
	double last_distance;
	unsigned int actual_way_point;
	catec_msgs::PositionWithCheck actual_position;
	ros::Timer timer;
	ros::Subscriber subCommandFlags;
};
#endif
