//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/User.h 

#ifndef ServerUserH
#define ServerUserH


#include "common.h"
#include "UDPSender.h"

class User
{
private:
	int WWID;
	Level accessLevel;
	std::string ipAddress;
	UDPSender *sender;
	bool registered;
public:
	User(int WWID, Level accessLevel);
	User();
	~User();
	int getWWID();
	Level getAccessLevel();
	bool hasAdminRights();
	bool hasRights();
	void setWWID(int newWWID);
	void setAccessLevel(Level accessLevel);
	void setIPAddress(std::string IP);
	void deregister();
	User *rightChild;
	User *leftChild;
	std::string getAccessLevelString();
	UDPSender* getSender();

};

#endif