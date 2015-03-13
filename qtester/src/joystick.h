/*
 * joystick.h
 *
 *  Created on: Mar 22, 2012
 *      Author: catec
 */


#include <stdio.h>
#include <ros/ros.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <uav/FlightPlan.h>
#include <uav/CommandFlags.h>
#include <string>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <signal.h>

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#ifndef PI
#define PI 3.141592653589793
#endif

#define JOYSTICK_DEVNAME "/dev/input/js0"

#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */

using namespace std;

class Teleop {
public:
	Teleop(string nquad);
	void keyLoop();

private:
	double modulus()
	{
		return sqrt(vx*vx+vy*vy);
	}
	string name;
	double vx, vy ,h, heading, headingvel, x, y;
	bool trigger;
	unsigned int counter;
	ros::NodeHandle nh_;
	ros::Publisher vel_pub_;
	ros::Publisher com_pub_;
};



struct js_event {
	unsigned int time;	/* event timestamp in milliseconds */
	short value;   /* value */
	unsigned char type;     /* event type */
	unsigned char number;   /* axis/button number */
};

struct wwvi_js_event {
	int button[11];
	int stick_x;
	int stick_y;
};

class CJoystick
{
public:
	int open_joystick();
	int read_joystick_event(struct js_event *jse);
	void close_joystick();
	int get_joystick_status(struct wwvi_js_event *wjse);
	CJoystick():joystick_fd(-1)
	{

	}
protected:
	int joystick_fd;
};

/*
extern int open_joystick(char *joystick_device);
extern int read_joystick_event(struct js_event *jse);
extern void set_joystick_y_axis(int axis);
extern void set_joystick_x_axis(int axis);
extern void close_joystick();
extern int get_joystick_status(struct wwvi_js_event *wjse);
*/


#endif
