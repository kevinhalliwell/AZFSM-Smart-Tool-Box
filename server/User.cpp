//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/User.cpp

#include "User.h"

User::User(int WWID, Level accessLevel){
	this->WWID = WWID;
	this->accessLevel = accessLevel;
	this->rightChild=NULL;
	this->leftChild=NULL;
	registered = false;
	this->sender = NULL;
}

User::User(){
	accessLevel = NONE;
	this->rightChild = NULL;
	this->leftChild = NULL;
	WWID = 0; // represents no user
	registered = false;
	this->sender = NULL;
}

User::~User()
{	
	if (this->leftChild != NULL)
		delete this->leftChild;
	if (this->rightChild != NULL)
		delete this->rightChild;
	if (this->sender != NULL)
		delete this->sender;
}

int User::getWWID(){
	return WWID;
}

Level User::getAccessLevel(){
	return accessLevel;
}

bool User::hasRights(){
	if (accessLevel == MT || accessLevel == ADMIN || accessLevel == GL || accessLevel == AM)
		return true;
	else
		return false;
}
bool User::hasAdminRights(){
	if (accessLevel == ADMIN || accessLevel == GL || accessLevel == AM)
		return true;
	else
		return false;
}

void User::setWWID(int newWWID){
	WWID = newWWID;
	if (WWID == 001) // Temporary measures to test access level based features
		accessLevel = MT;
	else if (WWID == 002)
		accessLevel = ADMIN;
	else if (WWID == 003)
		accessLevel = GL;
	else if (WWID == 004)
		accessLevel = AM;
}

void User::setAccessLevel(Level accessLevel){
	this->accessLevel = accessLevel;
}

void User::setIPAddress(std::string IP){
	this->ipAddress = IP;
	sender = new UDPSender(this->ipAddress,outPort);
	registered = true;
}

void User::deregister(){
	this->ipAddress = "\0";
	delete this->sender;
	registered = false;
}

std::string User::getAccessLevelString(){
	if (accessLevel == NONE)
		return "NONE";
	else if (accessLevel == MT)
		return "MT";
	else if (accessLevel == ADMIN)
		return "ADMIN";
	else if (accessLevel == GL)
		return "GL";
	else if (accessLevel == AM)
		return "AM";
	else
		return "UNDEFINED";
}

UDPSender* User::getSender(){
	return sender;
}