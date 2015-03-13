/*
 * radio.h
 *
 *  Created on: May 14, 2013
 *      Author: José Joaquín Acevedo
 */

#ifndef RADIO_H
#define RADIO_H

using namespace std;

#define AG_MAX 10               
#define MSG_LENGTH 3      
#define POS_X 0
#define POS_Y 1
#define POS_Z 2
#define VALOR_NULO -1   
#define VALOR_ATODOS 10
#define CAMPO_DEST 1
#define CAMPO_ORIG 0
#define CAMPO_TIPO 2



class class_radio
{
private:
	int id;
	double range;
	int num_ag;
	


public:
	int msgs[AG_MAX][MSG_LENGTH];
	int active;	

	
	class_radio(int id_i, double range_i, int num);
	~class_radio();
	void sending(int id_i, int *msg);
	int receiving(int id_i, double posiciones[AG_MAX][3], int msg_env[AG_MAX][MSG_LENGTH]);
	void set_id(int id_i);
	int get_id();
	void set_range(double range_i);
	double get_range();
	void set_num_ag(int num);
	int get_num_ag();
	void print_msgs();
};

#endif
