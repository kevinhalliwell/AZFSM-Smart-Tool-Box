//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/Drawer.h 

#ifndef serverDrawerH
#define serverDrawerH


#include "common.h"
#include "Tool.h"

class Drawer
{
private:
	int sensors;
	Tool* tools;

public:
	Drawer();
	~Drawer();
	int getSensors();
	void setSensors(int sensors);
	Tool* getTool(int number);
	bool toolSetup(int sensorNumber, std::string toolName, User* requesting);
	bool isConfigured();

};

#endif