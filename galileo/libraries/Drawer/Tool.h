//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//galileo/Tool.h 

#ifndef GalileoToolH
#define GalileoToolH

#include "common.h"

class Tool
{
private:
	int toolPin;
	int toolSensorAdjust;
	int noLightAdjust;
	bool serverNotifiedChange;
	bool toolPresentOnServer;

public:
	Tool();

	//Mutators
	void setPin(int pin);
	void setSensorAdjust(int sensorAdjust);
	void setNoLightAdjust(int noLightAdjust);
	void setServerNotified(bool notified);
	void setServerPresent(bool present);
	//Accessors
	int getPin();
	int getToolSensorAdjust();
	int getNoLightAdjust();
	bool getServerNotified();
	bool getServerPresent();

	//Functions
	bool checkUpdate();
	bool isPresent();

};

#endif