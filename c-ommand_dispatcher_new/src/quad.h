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


struct agente
{
	double capacidades[N_CAP];
	double x;
	double y;
	double vel_max;
	double range;
	int estado;
	int id;
	int plan;

//definir propiedades
};

struct costes
{
	double cost;
	double arrive_time;
//definir propiedades
};


class class_quad
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


//public:
       class_quad(int id_in, double x_in, double y_in, double z_in, double vel_max_in, double range_in, double tpo_in);
       ~class_quad();
       void task_allocation_one (struct agente agente_cont, double now);
       void monitoring_tasks (double tasks_in [MAX_TASKS][TAM_TASKS], double now);//i 0-5 j=1 (3-4) posicion x y (lo variamos) mostramos el tasks
       void join_tasks (double tasks_cont [MAX_TASKS][TAM_TASKS], int id_cont);//crear otro tasks distinto
       void incr_cont (double dT);
       int decide_cont (int msg_rcv[MAX_AGENTES][MSG_LENGTH], int tam);
       struct agente calculaAgente ();
       void autoplan (double now);
       double norma(double x, double y);
       int combinaciones(int n, int C[MAX_TASKS], int C_out[MAX_COMB][MAX_TASKS]);
       struct costes calcula_coste (int plan_in [MAX_TASKS],double tasks_cont [MAX_TASKS][TAM_TASKS], struct agente a);
       void init_cont(int num, double tpo);
};

#endif
