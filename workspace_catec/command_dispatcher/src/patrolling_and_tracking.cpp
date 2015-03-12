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
#include <string.h>




using namespace std;
using namespace catec_actions_msgs;
using namespace catec_msgs;

#include "strings_tools.h"
#include "quad.h"
#include "radio.h"

string node_name;

string uav_full_id[5];
string intruder_full_id[5];
int uav_id[2];
class_quad *agente[2];
class_radio *radio;
double t;
double dt=1.0/10.0;
double h_des[2];
double speed_max[2];
int dir_ini[2];

double range;
int mode;


typedef actionlib::SimpleActionClient<LandAction> LandClient;
typedef actionlib::SimpleActionClient<TakeOffAction> TakeOffClient;

//My next waypoint
WayPointWithCruiseStamped my_next_waypoint[2];

//nextWayPoint
ros::Publisher my_waypoint_pub[2];

//Last state of our uav
UALStateStamped last_ual_state[2];

UALStateStamped intruder_state[3];

LandClient **cLand;
TakeOffClient **cTakeOff;

bool LandGoalSended[2];
bool TakeOffGoalSended[2];
bool volando[2];
int num_ag;
int num_intruders;
int cambio[2];
double path[4][2];
int indice[2];
double tasks_in [MAX_TASKS][TAM_TASKS];
double pos_inicial[2][2];
TakeOffGoal tOff_goal[2];

ofstream pos_quads[2];
ofstream pos_intruders[3];
ofstream task_assigned[2];
ofstream costes_totales[2];

void land_Active_CB0();
void land_Feedback_CB0(const LandFeedbackConstPtr& feedback);
void land_Done_CB0(const actionlib::SimpleClientGoalState& state, const LandResultConstPtr& result);

void tOff_Active_CB();
void tOff_Feedback_CB(const TakeOffFeedbackConstPtr& feedback);
void tOff_Done_CB(const actionlib::SimpleClientGoalState& state, const TakeOffResultConstPtr& result);


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
}


void sendControlReferences(const ros::TimerEvent& te)
{

	WayPointWithCruiseStamped res;
	double posiciones[AG_MAX][3];
	int tam;
	int msg_sent[MSG_LENGTH];
	int msg_env[AG_MAX][MSG_LENGTH];
	int id_cont;
	int quad_cont[AG_MAX];
	double tasks_before[AG_MAX][MAX_TASKS][TAM_TASKS];
	struct agente agentes_before[AG_MAX];
	int tam_plan=0;
	bool listo=true;
	struct mensaje mensaje_rcv;


	t=t+dt;

	
	for (int i=0; i<num_ag; i++)
	{
		agente[i]->x=last_ual_state[i].ual_state.dynamic_state.position.x;
		agente[i]->y=last_ual_state[i].ual_state.dynamic_state.position.y;
		agente[i]->z=last_ual_state[i].ual_state.dynamic_state.position.z;
		posiciones[i][POS_X]=agente[i]->x;
		posiciones[i][POS_Y]=agente[i]->y;
		posiciones[i][POS_Z]=agente[i]->z;
		pos_quads[i] << t << ", " << agente[i]->x << ", " << agente[i]->y << ", " << agente[i]->z << ";" << endl;
		task_assigned[i] << t;
		for (int j=0; j<MAX_TASKS; j++)
			if (agente[i]->plan[j]>-1)
				task_assigned[i] << ", " << agente[i]->tasks[agente[i]->plan[j]][0];
			else
				task_assigned[i] << ", " << "-1";
		task_assigned[i] << ";" <<endl;

		costes_totales[i] << t << ", " << agente[i]->coste_mision << ";" <<endl;
	}


	for (int i=0; i<num_intruders; i++)
	{
		
		
		tasks_in[i][1]=(intruder_state[i].ual_state.dynamic_state.position.x-tasks_in[i][3])/dt;
		tasks_in[i][2]=(intruder_state[i].ual_state.dynamic_state.position.y-tasks_in[i][4])/dt;
		tasks_in[i][3]=intruder_state[i].ual_state.dynamic_state.position.x;
		tasks_in[i][4]=intruder_state[i].ual_state.dynamic_state.position.y;
		pos_intruders[i] << t << ", " << tasks_in[i][3] << ", " << tasks_in[i][4] << ", " << "0.0"<< ";" << endl;
	}


	for (int i=0;i<num_ag;i++)
		listo=listo && volando[i];

	if (listo==false)
	{

	    for (int i=0;i<num_ag;i++)
	    if (volando[i]==false)
	    {
		res.way_point.x=pos_inicial[i][0];
	        res.way_point.y=pos_inicial[i][1];
	        res.way_point.z=h_des[i];
		if ((agente[i]->z-h_des[i])>-0.2)
			volando[i]=true;
		res.header.frame_id = node_name;
		res.header.stamp = ros::Time::now();
		res.way_point.cruise = 0.5;

		my_waypoint_pub[i].publish(res);
            }
	}
	else
	{



	for (int i=0; i<num_ag; i++)
	{
		if (volando[i]==true)
		{
			tam=radio->receiving(i, posiciones, msg_env);
			if (tam==0)
			{
				msg_sent[0]=i;
				msg_sent[1]=10;
				msg_sent[2]=1;
				radio->sending(i, msg_sent);
			}
			else
			{
				id_cont=agente[i]->decide_cont(msg_env,tam);
				msg_sent[0]=i;
				msg_sent[1]=id_cont;
				msg_sent[2]=2;
				radio->sending(i, msg_sent);
				agente[i]->id_contactado=id_cont;
			}
			
			for (int k=0;k<AG_MAX;k++)
				for (int j=0;j<MSG_LENGTH;j++)
					msg_env[k][j]=VALOR_NULO;

			agente[i]->incr_cont (dt);
			quad_cont[i]=agente[i]->id_contactado;
			for (int j=0;j<MAX_TASKS;j++)
				for (int k=0;k<TAM_TASKS;k++)
					tasks_before[i][j][k]=agente[i]->tasks[j][k];


			agentes_before[i]=agente[i]->calculaAgente ();

		}
		
	}



	for (int i=0; i<num_ag; i++)
	{
		if (volando[i]==true)
		{	
			if (agente[i]->id_contactado>=0 && quad_cont[agente[i]->id_contactado]==i && mode==1)
			{
				agente[i]->join_tasks(tasks_before[agente[i]->id_contactado],agente[i]->id_contactado);
				agente[i]->task_allocation_one (agentes_before[agente[i]->id_contactado], t);
			}
			else if (agente[i]->tarea_nueva==1)
			{	
				agente[i]->autoplan(t);	
				agente[i]->tarea_nueva=0;
			}

			tam_plan=0;
			while(agente[i]->plan[tam_plan]>-1)
				tam_plan++;

			if (tam_plan>0)
			{	
					agente[i]->estado=2;
					agente[i]->dir=-1;
					agente[i]->ind=0;
					res.way_point.x=agente[i]->tasks[agente[i]->plan[0]][3];
					res.way_point.y=agente[i]->tasks[agente[i]->plan[0]][4];
					res.way_point.z=h_des[i];

					agente[i]->monitoring_tasks (tasks_in, t);

					res.header.frame_id = node_name;
					res.header.stamp = ros::Time::now();
					res.way_point.cruise = 0.5;
	
					my_waypoint_pub[i].publish(res);	
			}
			else
			{
				agente[i]->estado=1;

				if (agente[i]->id_contactado>0 && agentes_before[agente[i]->id_contactado].estado==1)
				{
					mensaje_rcv.id=agente[i]->id_contactado;
					mensaje_rcv.dir=agentes_before[agente[i]->id_contactado].dir;
					mensaje_rcv.vel_max=agentes_before[agente[i]->id_contactado].vel_max;
					mensaje_rcv.long_izq=agentes_before[agente[i]->id_contactado].long_izq;
			        	mensaje_rcv.long_dcha=agentes_before[agente[i]->id_contactado].long_dcha;
					mensaje_rcv.speed_izq=agentes_before[agente[i]->id_contactado].speed_izq;
			    	        mensaje_rcv.speed_dcha=agentes_before[agente[i]->id_contactado].speed_dcha;
					mensaje_rcv.init_ind=agentes_before[agente[i]->id_contactado].init_ind;
			  	        mensaje_rcv.ind=agentes_before[agente[i]->id_contactado].ind;
				}
				else
					mensaje_rcv.id=-1;

				agente[i]->pathpartition_cv (mensaje_rcv);
				indice[i]=agente[i]->ind;

				res.way_point.x=path[indice[i]][0];
				res.way_point.y=path[indice[i]][1];
				res.way_point.z=h_des[i];
	
				agente[i]->camino();

				agente[i]->monitoring_tasks (tasks_in, t);

				res.header.frame_id = node_name;
				res.header.stamp = ros::Time::now();
				res.way_point.cruise = 0.5;

				my_waypoint_pub[i].publish(res);
			}

		}

	}
	}

}

void UAV_StateCallBack(const UALStateStamped::ConstPtr& state) 
{
	const std::string& name_node = state->header.frame_id; //getPublisherName();

	for (int i=0; i<num_ag; i++)
	{
		if (strcmp(name_node.c_str(),uav_full_id[i].c_str())==0)
			last_ual_state[i] = *state;
	}

}


void Intruder_StateCallBack(const UALStateStamped::ConstPtr& state) 
{
	const std::string& name_node = state->header.frame_id; //getPublisherName();

	for (int i=0; i<num_intruders; i++)
	{
		if (strcmp(name_node.c_str(),intruder_full_id[i].c_str())==0)
		{
			intruder_state[i] = *state;
			tasks_in[i][0]=i;
		}
	}
}

int main(int argc, char** argv)
{
	ROS_INFO("  arguments [%d]", argc);
	if (argc < 7)
	{
		cout << "This program should have at least eight input parameter.\n"<< endl <<
				"The parameter format is: uavs_file dir_file speed_file height_file range_file intruder_file path_file mode" << endl;
		return -1;
	}

	ifstream uavs_file(string(argv[1]).c_str());
	num_ag=0;
	if(uavs_file.is_open())
	{
		while(uavs_file.good())
		{
			uavs_file >> uav_full_id[num_ag];
			num_ag++;
		}
			
	}
	else
	{
		cout << "Error, cannot open the file: " << argv[1] << endl;
		return -1;
	}


	num_ag=0;
	ifstream dir_file(string(argv[2]).c_str());
	if(dir_file.is_open())
	{
		while(dir_file.good())
		{
			dir_file >> dir_ini[num_ag];
			num_ag++;
		}
			
	}
	else
	{
		cout << "Error, cannot open the file: " << argv[2] << endl;
		return -1;
	}

	
	num_ag=0;
	ifstream speed_file(string(argv[3]).c_str());
	if(speed_file.is_open())
	{
		while(speed_file.good())
		{
			speed_file >> speed_max[num_ag];
			num_ag++;
		}
			
	}
	else
	{
		cout << "Error, cannot open the file: " << argv[3] << endl;
		return -1;
	}

	num_ag=0;
	ifstream height_file(string(argv[4]).c_str());
	if(height_file.is_open())
	{
		while(height_file.good())
		{
			height_file >> h_des[num_ag];
			num_ag++;
		}
			
	}
	else
	{
		cout << "Error, cannot open the file: " << argv[4] << endl;
		return -1;
	}
		
	range=atof(argv[5]);

	
	num_intruders=0;
	ifstream intruder_file(string(argv[6]).c_str());
	if(intruder_file.is_open())
	{
		while(intruder_file.good())
		{
			intruder_file >> intruder_full_id[num_intruders];
			num_intruders++;
		}
			
	}
	else
	{
		cout << "Error, cannot open the file: " << argv[6] << endl;
		return -1;
	}

	t=0.0;

	int tam_path=0;
	ifstream path_file(string(argv[7]).c_str());
	if(path_file.is_open())
	{
		while(path_file.good())
		{
			path_file >> path[tam_path][0];
			path_file >> path[tam_path][1];
			tam_path++;
		}
			
	}
	else
	{
		cout << "Error, cannot open the file: " << argv[7] << endl;
		return -1;
	}

	mode=atoi(argv[8]);

	char nombre[50];

	for (int i=0; i<num_ag; i++)
	{
		sprintf(nombre,"%s_pos",uav_full_id[i].c_str());
		pos_quads[i].open(nombre, ofstream::out);
		if (!pos_quads[i])
		{
			ROS_INFO("Error, cannot open the output file %s",nombre);
			return -1;
		}
		sprintf(nombre,"%s_tasks",uav_full_id[i].c_str());
		task_assigned[i].open(nombre, ofstream::out);
		if (!task_assigned[i])
		{
			ROS_INFO("Error, cannot open the output file %s",nombre);
			return -1;
		}
		sprintf(nombre,"%s_costs",uav_full_id[i].c_str());
		costes_totales[i].open(nombre, ofstream::out);
		if (!costes_totales[i])
		{
			ROS_INFO("Error, cannot open the output file %s",nombre);
			return -1;
		}		
	}

	for (int i=0; i<num_intruders; i++)
	{
		sprintf(nombre,"%s_pos",intruder_full_id[i].c_str());
		pos_intruders[i].open(nombre, ofstream::out);
		if (!pos_intruders[i])
		{
			ROS_INFO("Error, cannot open the output file %s",nombre);
			return -1;
		}
	}

	for (int i=0; i<MAX_TASKS; i++)
		for (int j=0; j<TAM_TASKS; j++)
			tasks_in[i][j]=-1;

	node_name = "patrolling_and_tracking";
	ros::init(argc,argv,node_name);
	ros::NodeHandle n;

	string topicname;
	ros::Subscriber agente_sub[2];
	ros::Subscriber intruder_sub[3];

	radio = new class_radio(0, 10.0, num_ag);

	for (int i=0; i<num_intruders; i++)
	{
		topicname=intruder_full_id[i];
		topicname.append("/ual_state");
		intruder_sub[i]=n.subscribe(topicname.c_str(), 0,Intruder_StateCallBack);
	}

	for (int i=0; i<num_ag; i++)
	{	
		topicname= node_name;
		topicname.append("/out_waypoint_");
		topicname.append(uav_full_id[i]);
		my_waypoint_pub[i] = n.advertise<WayPointWithCruiseStamped> (topicname.c_str(), 0);
		TakeOffGoalSended[i]=false;
		LandGoalSended[i]=false;
		topicname=uav_full_id[i];
		topicname.append("/ual_state");
		agente_sub[i] = n.subscribe(topicname.c_str(), 0,UAV_StateCallBack);
		topicname = uav_full_id[i];
		topicname.append("/land_action");
		cLand[i] = new LandClient(topicname,true);
		topicname = uav_full_id[i];
		topicname.append("/take_off_action");
		cTakeOff[i] = new TakeOffClient(topicname,true);
		sleep(5);
		agente[i]= new class_quad(i, last_ual_state[i].ual_state.dynamic_state.position.x, last_ual_state[i].ual_state.dynamic_state.position.y, 0.0, speed_max[i], range, 1.0, path, tam_path, dir_ini[i]);
		agente[i]->init_cont(num_ag, 1.0);
		volando[i]=false;
		cambio[i]=0;
		indice[i]=i+1;
	}
	
	ROS_INFO("Waiting for all servers...");	
	for (int i=0; i<num_ag; i++)
	{
		cLand[i]->waitForServer();
		cTakeOff[i]->waitForServer();	
        }
	ROS_INFO("All servers OK.");	

	for (int i=0; i<num_ag; i++)
	{
		cTakeOff[i]->sendGoal(tOff_goal[0], &tOff_Done_CB, &tOff_Active_CB, &tOff_Feedback_CB);
		pos_inicial[i][0]=last_ual_state[i].ual_state.dynamic_state.position.x;
		pos_inicial[i][1]=last_ual_state[i].ual_state.dynamic_state.position.y;	
		sleep(10);
	}
		
	for (int i=0; i<num_ag; i++)
		TakeOffGoalSended[i] = true;

	ros::Timer timer = n.createTimer(ros::Duration(dt), sendControlReferences);


	ros::AsyncSpinner spinner(0);
	spinner.start();

	while(ros::ok())
	{
		sleep(5);
	}
}