/*
 * quad.h
 *
 *  Created on: May 22, 2013
 *      Authors: Adrian Peralta y Jose Joaquin Acevedo
 */
 
#ifndef QUAD_H
#define QUAD_H

using namespace std;

#define N_CAP 3
#define MAX_TASKS 5
#define TAM_TASKS 14
#define MAX_AGENTES 5
#define MSG_LENGTH 3 
#define MAX_COMB 20
#define CTE_TPO 1
#define CTE_BENEFICIO 1
#define CTE_SEGUIR 10
#define CTE_VEL 10
#define CTE_CAMBIO 10
#define CTE_PERDIDO 1000
#define TAM_MAX_PATH 500


struct Agente
{
	double capacidades[N_CAP];
	double x;
	double y;
	double vel_max;
	double range;
	int estado;
	int id;
	int plan;
	int dir;
	double long_izq;
	double long_dcha;
	double speed_izq;
	double speed_dcha;
	int init_ind;
	int ind;

//definir propiedades
};

struct Costes
{
	double cost;
	double arrive_time;
//definir propiedades
};

struct Mensaje
{
	int id;
	int dir;
	double vel_max;
	double long_izq;
	double long_dcha;
	double speed_izq;
	double speed_dcha;
	int init_ind;
	int ind;
};

class QuadPatrolling
{
public:
    double capacidades[N_CAP];
	double x;
	double y;
	double z;
	double vel_max;
	double range;
	int estado;
	int id;
	double tasks [MAX_TASKS][TAM_TASKS];
	int id_contactado;
	int plan [MAX_TASKS];
	double contactados [MAX_AGENTES];
	double tpo_min_cont;
	int tarea_nueva;
	double coste_mision;
	double path[TAM_MAX_PATH][2];
	double path_dist[TAM_MAX_PATH];
	int tam_path;
	double vel;
	int dir;
	int ind;
	int init_ind;
	double long_izq;
	double long_dcha;
	double long_total;
	double speed_izq;
	double speed_dcha;
	double speed_total;
	int ind_inf;
	int ind_sup;
	double dist_inf;
	double dist_sup;
	int ind_aux;
	double dist_aux;
	int flag;
	int dir_aux;


public:
	QuadPatrolling(int id_in, double x_in, double y_in, double z_in, double vel_max_in, double range_in, double tpo_in, double path_in[4][2], int tam_path_in, int dir_in);
	~QuadPatrolling();
	void pathpartition_cv (struct Mensaje mensaje_rcv);
	void task_allocation_one (struct Agente agente_cont, double now);
	void monitoring_tasks (double tasks_in [MAX_TASKS][TAM_TASKS], double now);//i 0-5 j=1 (3-4) posicion x y (lo variamos) mostramos el tasks
	void join_tasks (double tasks_cont [MAX_TASKS][TAM_TASKS], int id_cont);//crear otro tasks distinto
	void incr_cont (double dT);
	int decide_cont (int msg_rcv[MAX_AGENTES][MSG_LENGTH], int tam);
	struct Agente calculaAgente ();
	void autoplan (double now);
	double norma(double x, double y);
	int combinaciones(int n, int C[MAX_TASKS], int C_out[MAX_COMB][MAX_TASKS]);
	struct Costes calcula_coste (int plan_in [MAX_TASKS],double tasks_cont [MAX_TASKS][TAM_TASKS], struct Agente a);
	void init_cont(int num, double tpo);
	void camino();
};

#endif
