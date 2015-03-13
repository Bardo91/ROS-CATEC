/*
 * string_tools.cpp

 *
 *  Created on: 26/11/2012
 *      Author: catec
 */
#include "strings_tools.h"

string landMessage(const LandResultConstPtr& result)
{
	switch(result->result)
	{
		case LandResult::LANDED:
			return string("LANDED");
			break;
		case LandResult::ALREADY_LANDED:
			return string("ALREADY_LANDED");
			break;
		case LandResult::LAND_CANCELED:
			return string("LAND_CANCELED");
			break;
		case LandResult::TAKINGOFF:
			return string("TAKINGOFF");
			break;
	}
	return string("UNKNOWN");
}
string takeOffMessage(const TakeOffResultConstPtr& result)
{
	switch(result->result)
	{
		case TakeOffResult::FLYING:
			return string("FLYING");
			break;
		case TakeOffResult::ALREADY_FLYING:
			return string("ALREADY_FLYING");
			break;
		case TakeOffResult::LANDING:
			return string("LANDING");
			break;
		case TakeOffResult::TAKEOFF_CANCELED:
			return string("TAKEOFF_CANCELED");
			break;
	}
	return string("UNKNOWN");
}


