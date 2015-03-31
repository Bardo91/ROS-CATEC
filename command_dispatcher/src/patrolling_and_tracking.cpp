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

string 			*intruder_full_id;
ros::Subscriber *intruder_sub;
UALStateStamped *intruder_state;

std::vector<QuadPatrolling *> agents;
std::vector<ros_catec::UavCatecROS*> controlAgents;
class_radio *radio;

double t;
const double dt=1.0/10.0;

//Last state of our uav

unsigned num_ag;
int num_intruders;

double *h_des;
double *speed_max;
int *cambio;
int *indice;

int tam_path = 9;						// Not generalized
double path[][2] = {	{-5.0, 	-5.0},	// Not generalized
						{-5.0, 	5.0},
						{0.0,	-5.0},
						{0.0, 	0.0},
						{5.0, 	0.0},
						{5.0,	5.0},
						{5.0,	-5.0},
						{0.0, 	5.0},
						{-5.0,	-5.0}
					};
double pos_inicial[2][2];				// Not generalized
double tasks_in [MAX_TASKS][TAM_TASKS];	// Not generalized


void sendControlReferences(const ros::TimerEvent& te);
void Intruder_StateCallBack(const UALStateStamped::ConstPtr& state);
void init(int _argc, char **_argv);

int main(int _argc, char** _argv) {
	cout << "Initializing main node" << endl;
	node_name = "Patrolling_and_tracking";
	ros::init(_argc,_argv,node_name);
	ros::NodeHandle n;

	init(_argc, _argv);

	ros::AsyncSpinner spinner(0);
	spinner.start();

	cout << "Taking off controlAgents" << endl;
	for(unsigned i = 0; i < controlAgents.size(); i++){
		controlAgents[i]->takeOff();

		double position[3];
		controlAgents[i]->position(position);
		ControlReferenceRwStamped res = controlAgents[i]->reference();
		res.c_reference_rw.position.x = position[0];
		res.c_reference_rw.position.y = position[1];
		res.c_reference_rw.position.z = h_des[i];
		controlAgents[i]->move(res);

	}
	usleep(2000000);

	cout << "Main loop" << endl;
	ros::Timer timer = n.createTimer(ros::Duration(dt), sendControlReferences);

	while(ros::ok()) {
		sleep(10);
	}
}

void init(int _argc, char **_argv){
	//-----------------------------------------------------------------------------------------------------------------
	cout << "Initalizing main node" << endl;
	node_name = "Patrolling_and_tracking";
	ros::init(_argc,_argv,node_name);
	ros::NodeHandle n;


	std::string exePath(_argv[0]);
	exePath = exePath.substr(0, exePath.find("patrolling_and_tracking"));

	//-----------------------------------------------------------------------------------------------------------------
	// Init Agents
	const int BUFF_SIZE = 1024;
	char buffer[BUFF_SIZE];

	ifstream agentIds((exePath + "agent_ids").c_str());
	assert(agentIds.is_open());
	agentIds.getline(buffer, BUFF_SIZE);
	num_ag = atoi(buffer);

	// Allocating.
	h_des 		= new double[num_ag];
	speed_max 	= new double[num_ag];
	int *dir_ini = new int[num_ag];
	cambio 		= new int[num_ag];
	indice 		= new int[num_ag];

	// Init agents
	for(unsigned i = 0; i < num_ag ; i++){
		agentIds.getline(buffer, BUFF_SIZE);
		std::string agentInfo(buffer);

		unsigned index 	= agentInfo.find('\t');
		std::string agentName = agentInfo.substr(0, index);
		controlAgents.push_back(new ros_catec::UavCatecROS(agentName));
		agentInfo 		= agentInfo.substr(index+1, agentInfo.size());
		index 			= agentInfo.find('\t');

		h_des[i] 		= atof(agentInfo.substr(0, index).c_str());
		agentInfo 		= agentInfo.substr(index+1, agentInfo.size());
		index 			= agentInfo.find('\n');

		speed_max[i] 	= atof(agentInfo.substr(0, index).c_str());
		dir_ini[i] 		= (i%2)*2 - 1;	// 1 or -1

		double range = 10;

		double position[3];
		controlAgents[i]->position(position);

		agents.push_back(new QuadPatrolling(i, position[0], position[1], position[2], speed_max[i], range, 1.0, path, tam_path, dir_ini[i]));
		agents[i]->init_cont(num_ag, 1.0);
		cambio[i]=0;
		indice[i]=i+1;
	}

	//-----------------------------------------------------------------------------------------------------------------
	// Init radio
	cout << "Initalizing radio" << endl;
	radio = new class_radio(0, 10.0, num_ag);

	//-----------------------------------------------------------------------------------------------------------------
	// Initializing tasks
	for (int i=0; i<MAX_TASKS; i++){
		for (int j=0; j<TAM_TASKS; j++){
			tasks_in[i][j]=-1;
		}
	}

	//-----------------------------------------------------------------------------------------------------------------
	// Intruder Data
	ifstream intruderIds((exePath + "intruder_ids").c_str());
	assert(intruderIds.is_open());
	intruderIds.getline(buffer, BUFF_SIZE);
	num_intruders = atoi(buffer);

	intruder_full_id 	= new std::string[num_intruders];
	intruder_sub 		= new ros::Subscriber[num_intruders];
	intruder_state		= new UALStateStamped[num_intruders];

	for (int i=0; i<num_intruders; i++) {
		intruderIds.getline(buffer, BUFF_SIZE);
		std::string topicname(buffer);
		intruder_full_id[i] = topicname;
		topicname.append("/ual_state");
		intruder_sub[i]=n.subscribe(topicname.c_str(), 0,Intruder_StateCallBack);
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
		if (strcmp(name_node.c_str(),intruder_full_id[i].c_str())==0) { // 666 TODO check if necessary
			intruder_state[i] = *state;
			tasks_in[i][0]=i;
		}
	}
}

