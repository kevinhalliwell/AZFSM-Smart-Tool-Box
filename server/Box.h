//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/Box.h

#ifndef ServerBoxH
#define ServerBoxH

#include "common.h"
#include "Drawer.h"
#include "UDPSender.h"

class Box
{
private:
	int bay;
	std::string ID;
	int boxID;
	std::string ipAddress;
	int numberDrawers;
	Drawer* drawers;
	bool locked;
	UDPSender *sender;
public:
	Box(int boxID,std::string boxIP, std::string name, int bayNumber, int drawers, User* requesting);
	~Box();
	bool drawerSetup(int drawerNumber, int sensors, User* requesting);
	bool toolSetup(int drawerNumber, int sensorNumber, std::string toolName, User* requesting);
	int getBoxID();
	int getBay();
	int getDrawers();
	std::string getID();
	void setID(std::string newName);
	void setBoxID(int boxID);
	std::string getIP();
	void setIP(std::string IP);
	Box *leftChild;
	Box *rightChild;
	Drawer* getDrawer(int drawerNumber);
	void setLocked(bool newStatus);
	bool getLocked();
	UDPSender* getSender();

};


#endif