//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//common/Messages.h


#ifndef GalileoMessagesH
#define GalileoMessagesH
#include <stdlib.h>
#include <sstream>
#include <string>
#include <cstring>
#include "MessageProtocol.h"

class Message
{
private:
	char senderType;
	char mesType;
	int boxID;
	int drawerID;
	int sensorID;
	bool locked;
	bool present; 
	int bayNumber;
	int WWID;
	std::string stringData;
	

public:
	Message *next;
	// Ack message constructor
	Message(char sender, char mesType, std::string stringData);
	// Server->app open confirmation constructor
	Message(char sender, char mesType, int WWID, std::string stringData);
	// Box lock/unlock request/command/report constructor
	Message(char sender, char mesType, int boxID, int WWID);
	// Drawer opened or closed report
	Message(char sender, char mesType, int boxID, int drawerID, bool locked, int WWID);
	// Tool removed or returned report
	Message(char sender, char mesType, int boxID, int drawerID, int sensorID, bool locked, int WWID);
	// Tool info message constructor
	Message(char sender, char mesType, int boxID, int drawerID, int sensorID, bool present, bool locked, int bayNumber, int WWID, std::string stringData);
	// Constructor for a message directly from a char buffer
	Message(char* incBuffer);
	~Message();
	void toChar(char* mesBuf);
	char getSenderType();
	char getType();
	int getBoxID();
	int getDrawerID();
	int getSensorID();
	bool getLocked();
	bool getPresent();
	int getBayNumber();
	int getWWID();
	std::string getString();

	void parseID(int toParse, int size, char* toStart);
	int unParseID(char* toUnParse, int size);
	char* parseBuffer(char* toParse, int size);
	bool unParseBool(char *toParse);
	void parseBool(bool toParse, char* toWrite);
	void copyChars(char* fromStart, char* toStart, int toCopy);
};

#endif