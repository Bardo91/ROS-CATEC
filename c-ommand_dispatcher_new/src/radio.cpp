/*
 * radio.cpp
 *
 *  Created on: May 14, 2013
 *      Author: José Joaquín Acevedo
 */

#include "radio.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


  class_radio::class_radio(int id_i, double range_i, int num)
  {
	id=id_i;
	range=range_i;
	if (num<=AG_MAX)
		num_ag=num;
	else
		num_ag=AG_MAX;

	for (int i=0;i<AG_MAX;i++)
		for (int j=0;j<MSG_LENGTH;j++)
			msgs[i][j]=VALOR_NULO;
	    
  }

  class_radio::~class_radio()
  {
;
  }

  void class_radio::sending(int id_i, int *msg)
  {
	for (int i=0;i<MSG_LENGTH;i++)
		msgs[id_i][i]=msg[i];

  }

 int class_radio::receiving(int id_i, double posiciones[AG_MAX][3], int msg_env[AG_MAX][MSG_LENGTH])
  {
	double pos[MSG_LENGTH]={posiciones[id_i][POS_X],posiciones[id_i][POS_Y],posiciones[id_i][POS_Z]};
	double pos_cont[MSG_LENGTH];
	double distancia=0.0;
	
	int k=0;

	for (int i=0;i<AG_MAX;i++)
		for (int j=0;j<MSG_LENGTH;j++)
			msg_env[i][j]=VALOR_NULO;

	for (int i=0;i<num_ag;i++)
		if ((msgs[i][CAMPO_DEST]==id_i || msgs[i][CAMPO_DEST]==VALOR_ATODOS) && (id_i!=msgs[i][CAMPO_ORIG]))
		{
			pos_cont[POS_X]=posiciones[i][POS_X];
			pos_cont[POS_Y]=posiciones[i][POS_Y];
			pos_cont[POS_Z]=posiciones[i][POS_Z];
			distancia=(pos[POS_X]-pos_cont[POS_X])*(pos[POS_X]-pos_cont[POS_X])+(pos[POS_Y]-pos_cont[POS_Y])*(pos[POS_Y]-pos_cont[POS_Y])+(pos[POS_Z]-pos_cont[POS_Z])*(pos[POS_Z]-pos_cont[POS_Z]);
			if (distancia<=range*range)
			{
				msg_env[k][CAMPO_ORIG]=msgs[i][CAMPO_ORIG];
				msg_env[k][CAMPO_DEST]=msgs[i][CAMPO_DEST];
				msg_env[k][CAMPO_TIPO]=msgs[i][CAMPO_TIPO];
				k++;
				if (msgs[i][CAMPO_DEST]!=VALOR_ATODOS && msgs[i][CAMPO_DEST]!=VALOR_NULO)
					for (int j=0; j<MSG_LENGTH; j++)
						msgs[i][j]=VALOR_NULO;
			}	
		}
	return k;

  }

	
  void class_radio::set_id(int id_i)
  {
	id=id_i;
  }
	
  int class_radio::get_id()
  {
	return id;
  }
	
  void class_radio::set_range(double range_i)
  {
	range=range_i;
  }

  double class_radio::get_range()
  {
	return range;
  }
	
  void class_radio::set_num_ag(int num)
  {
	num_ag=num;
  }
	
  int class_radio::get_num_ag()
  {
	return num_ag;
  }

  void class_radio::print_msgs()
  {
	for (int i=0; i<num_ag;i++)
		printf("%d %d %d \n",msgs[i][CAMPO_ORIG],msgs[i][CAMPO_DEST],msgs[i][CAMPO_TIPO]);


  }



