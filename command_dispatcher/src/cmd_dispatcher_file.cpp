/*
 * cmd_dispatcher.cpp
 *
 *  Created on: Oct 22, 2012
 *      Author: Jonathan Ruiz Páez
 */


#include <ros/ros.h>
#include <fstream>
#include <actionlib/client/simple_action_client.h>
#include <catec_actions_msgs/GoToWayPointsAction.h>
#include <catec_actions_msgs/LandAction.h>
#include <catec_actions_msgs/TakeOffAction.h>
#include <catec_actions_msgs/TargetAction.h>
#include <catec_msgs/UALStateStamped.h>
#include <catec_msgs/Target.h>


using namespace std;
using namespace catec_actions_msgs;
using namespace catec_msgs;

#include "strings_tools.h"

string uav_full_id;
int uav_id;

typedef actionlib::SimpleActionClient<GoToWayPointsAction> WayPointClient;
typedef actionlib::SimpleActionClient<LandAction> LandClient;
typedef actionlib::SimpleActionClient<TakeOffAction> TakeOffClient;
typedef actionlib::SimpleActionClient<TargetAction> TargetClient;

//Clients definition
WayPointClient *cWayPoint;
LandClient *cLand;
TakeOffClient *cTakeOff;
TargetClient *cTarget;

//For getState
bool targetGoalSended,gTWPGoalSended,LandGoalSended,TakeOffGoalSended;

void land_Active_CB();
void land_Feedback_CB(const LandFeedbackConstPtr& feedback);
void land_Done_CB(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result);


void gTWP_Active_CB();
void gTWP_Feedback_CB(const GoToWayPointsFeedbackConstPtr& feedback);
void gTWP_Done_CB(const actionlib::SimpleClientGoalState& state, const GoToWayPointsResultConstPtr& result);
GoToWayPointsGoal wp_goal;

void tOff_Active_CB();
void tOff_Feedback_CB(const TakeOffFeedbackConstPtr& feedback);
void tOff_Done_CB(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result);

void target_Active_CB();
void target_Feedback_CB(const TargetFeedbackConstPtr& feedback);
void target_Done_CB(const actionlib::SimpleClientGoalState& state, const TargetResultConstPtr& result);



/*
 * Callbacks for GoToWayPoint
 *
 *
 * */

void gTWP_Active_CB()
{
	//Se ejecutara cuando la tarea pase al estado activo
	ROS_INFO("Go to Way Point just went active.");

	//Start target detection
	//TargetGoal target_goal;
	//target_goal.target_type = Target::BOTH;
	//cTarget->sendGoal(target_goal, &target_Done_CB, &target_Active_CB, &target_Feedback_CB);
	targetGoalSended = true;
}

void gTWP_Feedback_CB(const GoToWayPointsFeedbackConstPtr& feedback)
{
	//Se ejecutara cada cierta distancia ¿Cada Cuanto?
	ROS_INFO("Distance to waypoint is: %f", feedback->distance_to_next_waypoint);
}

void gTWP_Done_CB(const actionlib::SimpleClientGoalState& state, const GoToWayPointsResultConstPtr& result)
{
	//Se ejecutara cuando la tarea haya terminado, podemos comprobar el estado para saber si termino correctamente, cancelada o abortada.
	//Podemos enviar la siguiente tarea desde aquí.
	ROS_INFO("Go To WayPoint finished in state [%s]", state.toString().c_str());
	ROS_INFO("UAV final point: [%.2f,%.2f,%.2f]", result->final_position.position.x, result->final_position.position.y, result->final_position.position.z);

	//Stop target detection
	//cTarget->cancelAllGoals();

	//Land
	LandGoal land_goal;
	cLand->sendGoal(land_goal, &land_Done_CB, &land_Active_CB, &land_Feedback_CB);
	LandGoalSended = true;

}

/*
 * Callbacks for Land
 *
 *
 * */

void land_Active_CB()
{
	//Se ejecutara cuando la tarea pase al estado activo
	ROS_INFO("Land Active.");
}

void land_Feedback_CB(const LandFeedbackConstPtr& feedback)
{
	//Se ejecutara cada vez que se cambie de etapa en el aterrizaje.
	ROS_INFO("Land phase: %d", feedback->phase);
}

void land_Done_CB(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result)
{
	//Se ejecutara cuando la tarea haya terminado, podemos comprobar el estado para saber si termino correctamente, cancelada o abortada.
	//Podemos enviar la siguiente tarea desde aquí.
	ROS_INFO("Land finished in state [%s]", state.toString().c_str());
	ROS_INFO("Land task return: [%s]", landMessage(result).c_str());
}

/*
 * Callbacks for TakeOff
 *
 *
 * */

void tOff_Active_CB()
{
	//Se ejecutara cuando la tarea pase al estado activo
	ROS_INFO("Take Off Active.");
}

void tOff_Feedback_CB(const TakeOffFeedbackConstPtr& feedback)
{
	//Se ejecutara cada vez que se cambie de etapa en el despegue.
	ROS_INFO("Take Off phase: %d", feedback->phase);
}

void tOff_Done_CB(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result)
{
	//Se ejecutara cuando la tarea haya terminado, podemos comprobar el estado para saber si termino correctamente, cancelada o abortada.
	//Podemos enviar la siguiente tarea desde aquí.
	ROS_INFO("Take off finished in state [%s]", state.toString().c_str());
	ROS_INFO("Take off task return: [%s]", takeOffMessage(result).c_str());


	//Si estamos volando enviamos la tarea.
	if(state.state_==state.SUCCEEDED || result->result==TakeOffResult::ALREADY_FLYING)
	{
		cWayPoint->sendGoal(wp_goal,&gTWP_Done_CB,&gTWP_Active_CB,&gTWP_Feedback_CB);
		gTWPGoalSended = true;
	}


	//ROS_INFO("Answer: %i", result->sequence.back());
}

/*
 * Callbacks for Target
 *
 *
 * */

void target_Active_CB()
{
	//Se ejecutara cuando la tarea pase al estado activo
	ROS_INFO("Target task just went active.");
}

void target_Feedback_CB(const TargetFeedbackConstPtr& feedback)
{
	//Se ejecutara cada vez que encontremos un nuevo objetivo

	ROS_INFO("New targets found:");
	for(unsigned int i=0;i < feedback->targets.targets.size; i++)
	{
		ROS_INFO("  Target [%d]", i);
		ROS_INFO("    Position: [%.2f,%.2f,%.2f]", feedback->targets.targets.targets[i].position.x,feedback->targets.targets.targets[i].position.y,feedback->targets.targets.targets[i].position.z);
		ROS_INFO("    Target type: [%s]", targetMessage(feedback->targets.targets.targets[i]).c_str());
	}
}

void target_Done_CB(const actionlib::SimpleClientGoalState& state, const TargetResultConstPtr& result)
{
	//Se ejecutara cuando la tarea haya terminado, podemos comprobar el estado para saber si termino correctamente, cancelada o abortada.
	//Podemos enviar la siguiente tarea desde aquí.
	ROS_INFO("Target task finished in state [%s]", state.toString().c_str());

	ROS_INFO("Total Targets found:");
		for(unsigned int i=0;i < result->targets.targets.size; i++)
		{
			ROS_INFO("  Target [%d]", i);
			ROS_INFO("    Position: [%.2f,%.2f,%.2f]", result->targets.targets.targets[i].position.x,result->targets.targets.targets[i].position.y,result->targets.targets.targets[i].position.z);
			ROS_INFO("    Target type: [%s]", targetMessage(result->targets.targets.targets[i]).c_str());
		}
}

/*
 * Callback para conocer el estado del UAV
 * */

void UAV0_StateCallBack(const UALStateStamped::ConstPtr& state) {
	//Se ejecutara periodicamente con el estao del uav.
/*ROS_INFO("New UALState Receive...");

	ROS_INFO("Velocity: [%f;%f;%f]", state->ual_state.dynamic_state.velocity.x, state->ual_state.dynamic_state.velocity.y, state->ual_state.dynamic_state.velocity.z);
	ROS_INFO("Position: [%f;%f;%f]", state->ual_state.dynamic_state.position.x, state->ual_state.dynamic_state.position.y, state->ual_state.dynamic_state.position.z);
	cout << endl << endl;*/
}



int main(int argc, char** argv)
{

	if (argc < 3)
			{
				cout << "This program has two input parameter.\n"<< endl <<
						"The first input parameter is the number of the UAV." << endl <<
						"The second input parameter is a file with waypoints." << endl;
				return -1;
			}

			//The UAV ID is stored in a global variable
			uav_full_id="uav_";
			uav_full_id.append(string(argv[1]));

			try
			{
				uav_id = boost::lexical_cast<int>(argv[1]);
			}
			catch(boost::bad_lexical_cast const&)
			{
				perror("The second argument is not a number.");
				return 1;
			}

    ifstream file(argv[2]);

    if(file.is_open())
    {
    	while(file.good())
    	{
    		WayPointWithCruiseStamped wp;
    		file >> wp.way_point.x;
    		file >> wp.way_point.y;
    		file >> wp.way_point.z;
    		if(!file.good())
    			break;
    		file >> wp.way_point.cruise;
    		wp.header.frame_id="command_dispatcher_X";
    		wp_goal.way_points.push_back(wp);

    		cerr << "WayPoint anadido: [" << wp.way_point.x << ";" << wp.way_point.y << ";" << wp.way_point.z << "]" << endl;
    	}
    	wp_goal.size = wp_goal.way_points.size();

    }else
    {
    	cerr << "Imposible abrir el fichero." << endl;
    	return 1;
    }

	string node_name = "CommandDispatcher_";
	node_name.append(uav_full_id);
	ros::init(argc,argv,node_name);
	ros::NodeHandle n;

	//Nos suscribimos al topico para conocer el estado del UAV
	ros::Subscriber sub1 = n.subscribe("uav_1/ual_state",1000,UAV0_StateCallBack);


	string topicname = uav_full_id;
	topicname.append("/go_to_way_point_action");
	cWayPoint = new WayPointClient(topicname,true);

	topicname = uav_full_id;
	topicname.append("/land_action");
	cLand = new LandClient(topicname,true);

	topicname = uav_full_id;
	topicname.append("/take_off_action");
	cTakeOff = new TakeOffClient(topicname,true);

/*	topicname = uav_full_id;
	topicname.append("/target_action");
	cTarget = new TargetClient(topicname,true);
*/

	targetGoalSended = false;
	TakeOffGoalSended = false;
	LandGoalSended = false;
	gTWPGoalSended =false;

	ROS_INFO("Waiting for all servers...");
	cWayPoint->waitForServer();
	cLand->waitForServer();
	cTakeOff->waitForServer();
	//cTarget->waitForServer();
	ROS_INFO("All servers OK.");

	sleep(4);


	//Iniciamos la tarea de despegue.

	TakeOffGoal tOff_goal;
	cTakeOff->sendGoal(tOff_goal, &tOff_Done_CB, &tOff_Active_CB, &tOff_Feedback_CB);
	TakeOffGoalSended = true;



	ros::AsyncSpinner spinner(0);
	spinner.start();

	while(ros::ok()){
		//Nuestro codigo aqui...
	/*	cout << endl << endl;
		cout <<"Estado de las Actions"<< endl;
		cout << "----------" << endl;

		if(gTWPGoalSended)
			cout << "Go To Way Point Action: [" << cWayPoint->getState().toString().c_str() << "]"<< endl;

		if(LandGoalSended)
			cout << "Land Action: [" << cLand->getState().toString().c_str() << "]"<< endl;

		if(TakeOffGoalSended)
			cout << "Take Off Action: [" << cTakeOff->getState().toString().c_str() << "]"<< endl;

		if(targetGoalSended)
			cout << "Target Detection Action: [" << cTarget->getState().toString().c_str() << "]"<< endl;

		cout << endl << endl;*/
		sleep(5);
	}
}
