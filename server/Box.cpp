//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/Box.cpp

#include "Box.h"

Box::Box(int boxID, std::string boxIP, std::string name, int bayNumber, int drawers, User* requesting)
{
	this->boxID = boxID;
	this->ipAddress = boxIP;
	ID = name;
	bay = bayNumber;
	numberDrawers = drawers;
	this->drawers = new Drawer[drawers];
	this->leftChild = NULL;
	this->rightChild = NULL;
	locked = true;
	sender = new UDPSender(this->ipAddress,outPort);
	//create log entry using User requesting
}

Box::~Box()
{
	delete this->drawers;
}

bool Box::drawerSetup(int drawerNumber, int sensors, User* requesting)
{
	if (drawerNumber >= 0 && drawerNumber <= numberDrawers) // check if valid drawer number
	{
		drawers[drawerNumber].setSensors(sensors);
		//create log entry using User requesting
		return true;
	}
	else
		return false;

}
bool Box::toolSetup(int drawerNumber, int sensorNumber, std::string toolName, User* requesting)
{
	if (drawerNumber >= 0 && drawerNumber <= numberDrawers) // check if valid drawer number
	{
			if (sensorNumber >= 0 && sensorNumber <= drawers[drawerNumber].getSensors()) // check if sensorNumber exists in drawerNumber
				{
					if (drawers[drawerNumber].toolSetup(sensorNumber, toolName, requesting))
						return true; // tool successfully added
					else
						return false; // not added successfully
				}
				else
					return false; // sensorNumber does not exist
	}
	else
		return false; // drawer number not valid
}

int Box::getBoxID()
{
	return this->boxID;
}

int Box::getBay()
{
	return bay;
}

int Box::getDrawers()
{
	return numberDrawers;
}

std::string Box::getID()
{
	return ID;
}

Drawer* Box::getDrawer(int drawerNumber)
{
	if (drawerNumber >= 0 && drawerNumber < numberDrawers)
		return &drawers[drawerNumber];
	else
		return NULL;
}

void Box::setID(std::string newName)
{
	ID = newName;
}

void Box::setBoxID(int boxID)
{
	this->boxID = boxID;
}

std::string Box::getIP()
{
	return this->ipAddress;
}
void Box::setIP(std::string IP)
{
	this->ipAddress = IP;
}

void Box::setLocked(bool newStatus)
{
	this->locked = newStatus;
}

bool Box::getLocked()
{
	return this->locked;
}

UDPSender* Box::getSender()
{
	return this->sender;
}