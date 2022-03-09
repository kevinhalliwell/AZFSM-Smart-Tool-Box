//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//galileo/Drawer.cpp

#include "Drawer.h"

Drawer::Drawer()
{
	tools = NULL;
	server = NULL;
	serverNotifiedOpened = false;
	serverNotifiedClosed = false;
}

Drawer::~Drawer()
{
	delete tools;
	delete server;
}

bool Drawer::isOpen()
{
	int lightLevel = -1*(analogRead(openSensorPin) - openSensorAdjust);
	if(lightLevel > noLightAdjust)
		return true;
	else
		return false;
}


//Mutator functions
void Drawer::setDrawerNumber(int drawerNumber)
{
	this->drawerNumber = drawerNumber;
}
void Drawer::setToolSensors(int toolSensors)
{
	if (this->toolSensors != toolSensors)
	{
		if (tools != NULL)
			delete this->tools;
		tools = new Tool[toolSensors];
		this->toolSensors = toolSensors;
	}
}
void Drawer::setOpenSensorPin(int openSensorPin)
{
	this->openSensorPin = openSensorPin;
}
void Drawer::setOpenSensorAdjust(int openSensorAdjust)
{
	this->openSensorAdjust = openSensorAdjust;
}
void Drawer::setNoLightAdjust(int noLightAdjust)
{
	this->noLightAdjust = noLightAdjust;
}
void Drawer::setServer(ToolServer *server)
{
	this->server = server;
}
//Accessor Functions
int Drawer::getDrawerNumber()
{
	return this->drawerNumber;
}

int Drawer::getSensors()
{
	return this->toolSensors;
}

Tool* Drawer::getTool(int sensor)
{
	if (sensor >= 0 && sensor < toolSensors)
	{
		return &tools[sensor];
	}
	else
		return NULL;
}

void Drawer::updateStatus()
{
	if (isOpen())
		{
			if (SERIAL_DEBUG && serverNotifiedClosed)
			{
				Serial.print("DRAWER ");
				Serial.print(drawerNumber);
				Serial.println(" WAS OPENED.");
			}
			if (!serverNotifiedOpened)
			{
				if (SERIAL_DEBUG)
				{
					Serial.print("SERVER NOT YET NOTIFIED DRAWER ");
					Serial.print(drawerNumber);
					Serial.println(" WAS OPENED. ATTEMPTING TO NOTIFY.");
				}
			 	server->notifyDrawerOpened(this);
			 	serverNotifiedOpened = true;
				serverNotifiedClosed = false;
			}
			updateInventory();
		}
		else
		{
			if(SERIAL_DEBUG && serverNotifiedOpened)
			{
				Serial.print("DRAWER ");
				Serial.print(drawerNumber);
				Serial.println(" WAS CLOSED.");
			}
			if (!serverNotifiedClosed)
			{
				if (SERIAL_DEBUG)
				{
					Serial.print("SERVER NOT YET NOTIFIED DRAWER ");
					Serial.print(drawerNumber);
					Serial.println(" WAS CLOSED. ATTEMPTING TO NOTIFY.");
				}
				serverNotifiedClosed = true;
				server->notifyDrawerClosed(this);
				serverNotifiedOpened = false;
			}
		}
}

void Drawer::updateInventory()
{
		bool inventoryUpdated = false;
		for (int i = 0; i < toolSensors; i++)
		{	
			if (isOpen())
				if(tools[i].checkUpdate())
					inventoryUpdated = true;
		}
		if (inventoryUpdated)
			server->notifyInventoryUpdated(this);
}