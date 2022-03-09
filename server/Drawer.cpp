//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/Drawer.cpp


#include "Drawer.h"

Drawer::Drawer()
{
	tools = NULL;
}

Drawer::~Drawer()
{
	delete tools;
}

int Drawer::getSensors()
{
	return sensors;
}

void Drawer::setSensors(int sensors)
{
	this->sensors = sensors;
	tools = new Tool[sensors];
}


Tool* Drawer::getTool(int number)
{
	if (number >=0 && number <= sensors && tools != NULL) // check if number is within range of sensors
		return &tools[number];
	else
		return NULL;
}

bool Drawer::toolSetup(int sensorNumber, std::string toolName, User* requesting)
{
	if (sensorNumber >=0 && sensorNumber <= sensors) // check if number is within range of sensors
	{
		if (requesting->hasAdminRights())
		{
			tools[sensorNumber].setName(toolName);
			//create log entry with User requesting
			return true;
		}
		else
			return false; // does not have admin rights
	}
	else
		return false; // invalid sensor number
}

bool Drawer::isConfigured()
{
	if (tools == NULL)
		return false;
	else
		return true;
}