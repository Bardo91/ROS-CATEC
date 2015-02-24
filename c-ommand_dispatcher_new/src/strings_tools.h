/*
 * strings_tools.h
 *
 *  Created on: Nov 2, 2012
 *      Author: catec-ros
 */

#ifndef STRINGS_TOOLS_H_
#define STRINGS_TOOLS_H_


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
string targetMessage(Target t)
{
	switch(t.target)
	{
		case Target::FIRST:
			return string("FIRST");
			break;
		case Target::SECOND:
			return string("SECOND");
			break;
		case Target::BOTH:
			return string("BOTH");
			break;

	}
	return string("UNKNOWN");
}



#endif /* STRINGS_TOOLS_H_ */
