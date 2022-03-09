//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//galileo/Drawer.h 

#ifndef GalileoDrawerH
#define GalileoDrawerH

#include "common.h"
#include "Tool.h"
#include "ToolServer.h"

class ToolServer;
class Drawer
{
private:
	int drawerNumber;
	int toolSensors;
	int openSensorPin;
	int openSensorAdjust;
	int noLightAdjust;
	Tool* tools;
	ToolServer* server;
	bool serverNotifiedOpened;
	bool serverNotifiedClosed;

public:
	
	Drawer();
	~Drawer();

	bool isOpen();

	void setDrawerNumber(int drawerNumber);
	void setToolSensors(int toolSensors);
	void setOpenSensorPin(int openSensorPin);
	void setOpenSensorAdjust(int openSensorAdjust);
	void setNoLightAdjust(int noLightAdjust);
	void setServer(ToolServer *server);

	int getSensors();
	int getDrawerNumber();
	Tool* getTool(int sensor);

	void updateStatus();
	void updateInventory();
};

#endif