//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/Tool.cpp

#include "Tool.h"

Tool::Tool(std::string name)
{
	this->name = name;
	present = false;
	tracking = false;
	checkedOutBy = NULL;
}

Tool::Tool()
{
	name = UNDEFINED_TOOL_NAME;
	present = false;
	tracking = false;
	checkedOutBy = NULL;
}

std::string Tool::getName()
{
	return name;
}


bool Tool::isPresent()
{
	return present;
}


bool Tool::isTracking()
{
	return tracking;
}


User* Tool::isCheckedOutBy()
{
	return checkedOutBy;
}


void Tool::setName(std::string newName)
{
	name = newName;
}

void Tool::setPresent(bool present)
{
	this->present = present;
}

void Tool::checkOut(User* checkingOut)
{
	present = false;
	checkedOutBy = checkingOut;
	//if (checkingOut->hasRights()) // check if user has rights to check out tool
		//create log entry with checkingOut
	//else
		//create log entry specifying invalid user removed item
}

void Tool::checkIn(User* checkingIn)
{
	present = true;
	checkedOutBy = NULL;
	//Create log entry specifying which user returned item
}


bool Tool::stopTracking(User* requesting)
{
	if(requesting->hasAdminRights())
	{
		present = false;
		tracking = false;
		checkedOutBy = NULL;
		//create log entry specifying that requesting stopped tracking item
		return true;
	}
	else
	{
		//create log entry specifying that requesting attempted to start tracking without admin rights
		return false;
	}
}

bool Tool::startTracking(User* requesting)
{
	if(requesting->hasAdminRights()) // check if user has admin rights
	{
		present = false;
		tracking = true;
		checkedOutBy = requesting;
		//create log entry specifying that requesting started item tracking
		return true;
	}
	else
	{
		//create log entry specifying that requesting attempted to start tracking without admin rights
		return false;
	}

}
