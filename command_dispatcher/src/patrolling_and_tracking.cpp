#include <ros/ros.h>
#include <catec_msgs/UALStateStamped.h>
#include <catec_msgs/Position.h>
#include <geometry_msgs/Point.h>


#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;
using namespace catec_msgs;

#include "quad.h"
#include "radio.h"
#include <testbed/control/UavCatecRos.h>

string node_name;

string intruder_full_id[5];
//QuadPatrolling *agente[2];
std::vector<QuadPatrolling *> agents;
std::vector<ros_catec::UavCatecROS*> controlAgents;
class_radio *radio;
ros::Subscriber intruder_sub[3];



double t;
const double dt=1.0/10.0;
double h_des[2];

//Last state of our uav
UALStateStamped intruder_state[3];

int num_ag;
int num_intruders;
int cambio[2];
double speed_max[2];
// double path[4][2]; <--- Changed
double path[][2] = {	{-5.0, 	-5.0},
						{-5.0, 	5.0},
						{0.0,	-5.0},
						{5.0,	5.0},
						{5.0,	-5.0},
						{0.0, 	5.0},
						{-5.0,	-5.0}
					};

int tam_path = 7;
int indice[2];
double tasks_in [MAX_TASKS][TAM_TASKS];
double pos_inicial[2][2];


void sendControlReferences(const ros::TimerEvent& te);

void Intruder_StateCallBack(const UALStateStamped::ConstPtr& state);

void init(int _argc, char **_argv);


int main(int _argc, char** _argv) {
	cout << "Initializing main node" << endl;
	node_name = "Patrolling_and_tracking";
	ros::init(_argc,_argv,node_name);
	ros::NodeHandle n;

	controlAgents.push_back(new ros_catec::UavCatecROS(_argv[1]));
	controlAgents.push_back(new ros_catec::UavCatecROS(_argv[2]));

	init(_argc, _argv);

	cout << "Taking of controlAgents" << endl;
	ros::AsyncSpinner spinner(0);
	spinner.start();


	for(unsigned i = 0; i < controlAgents.size(); i++){
		controlAgents[i]->takeOff();
	}

	cout << "Main loop" << endl;
	ros::Timer timer = n.createTimer(ros::Duration(dt), sendControlReferences);

	while(ros::ok()) {
		sleep(10);
	}
}

void init(int _argc, char **_argv){
	num_ag = 2;
	int dir_ini[2];
	dir_ini[0] = 1;
	dir_ini[1] = -1;

	
	speed_max[0] = 0.5;
	speed_max[1] = 0.7;

	h_des[0] = atoi(_argv[3]);
	h_des[1] = atoi(_argv[4]);

	double range = 10;

	// Waypoints were defined previously

	// Intruder Data
	num_intruders=2;
	intruder_full_id[0] = _argv[5];
	intruder_full_id[1] = _argv[6];

	//-----------------------------------------------------------------------------------------------------------------
	// Initializing tasks
	for (int i=0; i<MAX_TASKS; i++){
		for (int j=0; j<TAM_TASKS; j++){
			tasks_in[i][j]=-1;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------
	// Real main
	cout << "Initalizing main node" << endl;
	node_name = "Patrolling_and_tracking";
	ros::init(_argc,_argv,node_name);
	ros::NodeHandle n;

	string topicname;
	// Init radio
	cout << "Initalizing radio" << endl;
	radio = new class_radio(0, 10.0, num_ag);

	// Subscribing to uav states
	cout << "Subscribing to uav states" << endl;
	for (int i=0; i<num_intruders; i++) {
		topicname=intruder_full_id[i];
		topicname.append("/ual_state");
		intruder_sub[i]=n.subscribe(topicname.c_str(), 0,Intruder_StateCallBack);
	}

	// Taking off and related...
	cout << "Configuring quads" << endl;
	for (int i=0; i<num_ag; i++) {
		sleep(5);
		double position[3];
		controlAgents[i]->position(position);

		agents.push_back(new QuadPatrolling(i, position[0], position[1], position[2], speed_max[i], range, 1.0, path, tam_path, dir_ini[i]));
		agents[i]->init_cont(num_ag, 1.0);
		cambio[i]=0;
		indice[i]=i+1;
	}
}

void sendControlReferences(const ros::TimerEvent& te) {
	ControlReferenceRwStamped res;
	double posiciones[AG_MAX][3];
	int tam;
	int msg_sent[MSG_LENGTH];
	int msg_env[AG_MAX][MSG_LENGTH];
	int id_cont;
	int quad_cont[AG_MAX];
	double tasks_before[AG_MAX][MAX_TASKS][TAM_TASKS];
	struct Agente agentes_before[AG_MAX];
	int tam_plan=0;
	struct Mensaje mensaje_rcv;

	t=t+dt;

	for (int i=0; i<num_ag; i++) {
		double position[3];

		controlAgents[i]->position(position);

		agents[i]->x=position[0];
		agents[i]->y=position[1];
		agents[i]->z=position[2];

		posiciones[i][POS_X]=position[0];
		posiciones[i][POS_Y]=position[1];
		posiciones[i][POS_Z]=position[2];
	}


	for (int i=0; i<num_intruders; i++) {
		tasks_in[i][1]=(intruder_state[i].ual_state.dynamic_state.position.x-tasks_in[i][3])/dt;
		tasks_in[i][2]=(intruder_state[i].ual_state.dynamic_state.position.y-tasks_in[i][4])/dt;
		tasks_in[i][3]=intruder_state[i].ual_state.dynamic_state.position.x;
		tasks_in[i][4]=intruder_state[i].ual_state.dynamic_state.position.y;
	}


	for (int i=0; i<num_ag; i++) {
		tam=radio->receiving(i, posiciones, msg_env);
		if (tam==0) {
			msg_sent[0]=i;
			msg_sent[1]=10;
			msg_sent[2]=1;
			radio->sending(i, msg_sent);
		} else {
			id_cont=agents[i]->decide_cont(msg_env,tam);
			msg_sent[0]=i;
			msg_sent[1]=id_cont;
			msg_sent[2]=2;
			radio->sending(i, msg_sent);
			agents[i]->id_contactado=id_cont;
		}

		for (int k=0;k<AG_MAX;k++){
			for (int j=0;j<MSG_LENGTH;j++){
				msg_env[k][j]=VALOR_NULO;
			}
		}

		agents[i]->incr_cont (dt);
		quad_cont[i]=agents[i]->id_contactado;
		for (int j=0;j<MAX_TASKS;j++){
			for (int k=0;k<TAM_TASKS;k++){
				tasks_before[i][j][k]=agents[i]->tasks[j][k];
			}
		}

		agentes_before[i]=agents[i]->calculaAgente();
	}

	for (int i=0; i<num_ag; i++){
		if (agents[i]->id_contactado>=0 && quad_cont[agents[i]->id_contactado]==i) {
			agents[i]->join_tasks(tasks_before[agents[i]->id_contactado],agents[i]->id_contactado);
			agents[i]->task_allocation_one (agentes_before[agents[i]->id_contactado], t);
		} else if (agents[i]->tarea_nueva==1) {
			agents[i]->autoplan(t);
			agents[i]->tarea_nueva=0;
		}

		tam_plan=0;

		while(agents[i]->plan[tam_plan]>-1){
			tam_plan++;
		}

		if (tam_plan>0) {
				agents[i]->estado=2;
				agents[i]->dir=-1;
				agents[i]->ind=0;
				res.c_reference_rw.position.x=agents[i]->tasks[agents[i]->plan[0]][3];
				res.c_reference_rw.position.y=agents[i]->tasks[agents[i]->plan[0]][4];
				res.c_reference_rw.position.z=h_des[i];
				res.c_reference_rw.cruise = speed_max[i];
				agents[i]->monitoring_tasks (tasks_in, t);

				res.header.frame_id = node_name;
				res.header.stamp = ros::Time::now();

				controlAgents[i]->move(res);

		} else {
			agents[i]->estado=1;

			if (agents[i]->id_contactado>0 && agentes_before[agents[i]->id_contactado].estado==1) {
				mensaje_rcv.id			=agents[i]->id_contactado;
				mensaje_rcv.dir			=agentes_before[agents[i]->id_contactado].dir;
				mensaje_rcv.vel_max		=agentes_before[agents[i]->id_contactado].vel_max;
				mensaje_rcv.long_izq	=agentes_before[agents[i]->id_contactado].long_izq;
				mensaje_rcv.long_dcha	=agentes_before[agents[i]->id_contactado].long_dcha;
				mensaje_rcv.speed_izq	=agentes_before[agents[i]->id_contactado].speed_izq;
				mensaje_rcv.speed_dcha	=agentes_before[agents[i]->id_contactado].speed_dcha;
				mensaje_rcv.init_ind	=agentes_before[agents[i]->id_contactado].init_ind;
				mensaje_rcv.ind			=agentes_before[agents[i]->id_contactado].ind;
			} else{
				mensaje_rcv.id=-1;
			}
			agents[i]->pathpartition_cv (mensaje_rcv);
			indice[i]=agents[i]->ind;
			res.c_reference_rw.position.x=path[indice[i]][0];
			res.c_reference_rw.position.y=path[indice[i]][1];
			res.c_reference_rw.position.z=h_des[i];
			res.c_reference_rw.cruise = speed_max[i];
			agents[i]->camino();

			agents[i]->monitoring_tasks (tasks_in, t);

			res.header.frame_id = node_name;
			res.header.stamp = ros::Time::now();

			controlAgents[i]->move(res);
		}
	}
}

void Intruder_StateCallBack(const UALStateStamped::ConstPtr& state) {
	const std::string name_node = state->header.frame_id; //getPublisherName();
	for (int i=0; i<num_intruders; i++) {
		if (strcmp(name_node.c_str(),intruder_full_id[i].c_str())==0) {
			intruder_state[i] = *state;
			tasks_in[i][0]=i;
		}
	}
}

