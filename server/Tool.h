//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/Tool.h


#ifndef serverToolH
#define serverToolH


#include "common.h"
#include "User.h"

class Tool
{
private:
	std::string name;
	bool present;
	bool tracking;
	User* checkedOutBy;
public:
	Tool(std::string name);
	Tool();
	std::string getName();
	bool isPresent();
	bool isTracking();
	User* isCheckedOutBy();
	void setName(std::string newName);
	void setPresent(bool present);
	void checkOut(User* checkingOut);
	void checkIn(User* checkingIn);
	bool stopTracking(User* requesting);
	bool startTracking(User* requesting);
};

#endif