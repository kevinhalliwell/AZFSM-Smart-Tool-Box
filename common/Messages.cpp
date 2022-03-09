//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//common/Messages.cpp

#include "Messages.h"


// Ack message constructor
Message::Message(char sender, char mesType, std::string stringData)
{
	this->senderType = sender;
	this->mesType = mesType;
	this->stringData = stringData;
	this->boxID = 0;
	this->drawerID = 0;
	this->sensorID = 0;
	this->locked = false;
	this->present = false;
	this->WWID = 0;
	this->bayNumber = 0;
	this->next = NULL;
}
// Server->App open connection confirmation
Message::Message(char sender, char mesType, int WWID, std::string stringData)
{
	this->senderType = sender;
	this->mesType = mesType;
	this->stringData = stringData;
	this->boxID = 0;
	this->drawerID = 0;
	this->sensorID = 0;
	this->locked = false;
	this->present = false;
	this->WWID = WWID;
	this->bayNumber = 0;
	this->next = NULL;
}
// Box lock/unlock request/command/report constructor
Message::Message(char sender, char mesType, int boxID, int WWID)
{
	this->senderType = sender;
	this->mesType = mesType;
	this->boxID = boxID;
	this->WWID = WWID;
	this->drawerID = 0;
	this->sensorID = 0;
	this->locked = false;
	this->present = false;
	this->bayNumber = 0;
	stringData.assign(STRING_SIZE,'0');
	this->next = NULL;
}
// Drawer opened or closed report
Message::Message(char sender, char mesType, int boxID, int drawerID, bool locked, int WWID)
{
	this->senderType = sender;
	this->mesType = mesType;
	this->boxID = boxID;
	this->drawerID = drawerID;
	this->locked = locked;
	this->sensorID = 0;
	this->present = false;
	this->bayNumber =0;
	stringData.assign(STRING_SIZE,'0');
	this->WWID = WWID;
	this->next = NULL;
}
// Tool removed or returned report
Message::Message(char sender, char mesType, int boxID, int drawerID, int sensorID, bool locked, int WWID)
{
	this->senderType = sender;
	this->mesType = mesType;
	this->boxID = boxID;
	this->drawerID = drawerID;
	this->sensorID = sensorID;
	this->locked = locked;
	this->WWID = WWID;
	this->bayNumber = 0;
	this->present = false;
	stringData.assign(STRING_SIZE,'0');
	this->next = NULL;
}
// Tool info message constructor
Message::Message(char sender, char mesType, int boxID, int drawerID, int sensorID, bool present, bool locked, int bayNumber, int WWID, std::string stringData)
{
	this->senderType = sender;
	this->mesType = mesType;
	this->boxID = boxID;
	this->drawerID = drawerID;
	this->sensorID = sensorID;
	this->locked = locked;
	this->present = present;
	this->bayNumber = bayNumber;
	this->WWID = WWID;
	this->stringData = stringData;
	this->next = NULL;
}
// Constructor for a message directly from a char buffer
Message::Message(char* incBuffer)
{
	char header[] = HEADER_STRING;
	char testHeader[HEADER_SIZE];
	copyChars(&testHeader[0],&incBuffer[HEADER_POSITION],HEADER_SIZE);
	if (strncmp(testHeader,header,HEADER_SIZE) == 0)
	{
		this->senderType = incBuffer[SENDER_CODE_POSITION];
		this->mesType = incBuffer[TYPE_CODE_POSITION];
		this->boxID = unParseID(&incBuffer[BOX_ID_POSITION],BOX_ID_SIZE);
		this->drawerID = unParseID(&incBuffer[DRAWER_ID_POSITION],DRAWER_ID_SIZE);
		this->sensorID = unParseID(&incBuffer[SENSOR_ID_POSITION],SENSOR_ID_SIZE);
		this->locked = unParseBool(&incBuffer[LOCKED_STATUS_POSITION]);
		this->present = unParseBool(&incBuffer[PRESENT_STATUS_POSITION]);
		this->bayNumber = unParseID(&incBuffer[BAY_NUMBER_POSITION],BAY_NUMBER_SIZE);
		this->WWID = unParseID(&incBuffer[WWID_POSITION],WWID_SIZE);
		char cString[STRING_SIZE];
		copyChars(&cString[0],&incBuffer[STRING_POSITION],STRING_SIZE);
		std::string newString(cString);
		stringData = newString;
	}
	else
	{
		this->mesType = INVALID_TYPE_CHAR;
		this->senderType = INVALID_TYPE_CHAR;
		this->boxID = 0;
		this->drawerID = 0;
		this->sensorID = 0;
		this->locked = false;
		this->present = false;
		this->WWID = 0;
		this->bayNumber = 0;
		this->stringData.assign(STRING_SIZE,INVALID_TYPE_CHAR);

	}
	this->next = NULL;
}
Message::~Message()
{
	if (this->next != NULL)
		delete this->next;
}

void Message::toChar(char* mesBuf)
{

	char header[] = HEADER_STRING;
	copyChars(&mesBuf[HEADER_POSITION],&header[0],HEADER_SIZE);
	mesBuf[SENDER_CODE_POSITION] = senderType;
	mesBuf[TYPE_CODE_POSITION] = mesType;
	parseID(boxID,BOX_ID_SIZE,&mesBuf[BOX_ID_POSITION]);
	parseID(drawerID,DRAWER_ID_SIZE,&mesBuf[DRAWER_ID_POSITION]);
	parseID(sensorID,SENSOR_ID_SIZE,&mesBuf[SENSOR_ID_POSITION]);
	parseBool(locked,&mesBuf[LOCKED_STATUS_POSITION]);
	parseBool(present,&mesBuf[PRESENT_STATUS_POSITION]);
	parseID(bayNumber,BAY_NUMBER_SIZE,&mesBuf[BAY_NUMBER_POSITION]);
	parseID(WWID,WWID_SIZE,&mesBuf[WWID_POSITION]);;
	char stringC[STRING_SIZE];
	strcpy(stringC,stringData.c_str());
	copyChars(&mesBuf[STRING_POSITION],&stringC[0],STRING_SIZE);
	mesBuf[STRING_POSITION + stringData.length()] = END_CHAR;

}

char Message::getSenderType()
{
	return senderType;
}
char Message::getType()
{
	return mesType;
}
int Message::getBoxID()
{
	return boxID;
}
int Message::getDrawerID()
{
	return drawerID;
}
int Message::getSensorID()
{
	return sensorID;
}
bool Message::getLocked()
{
	return locked;
}
bool Message::getPresent()
{
	return present;
}
int Message::getBayNumber()
{
	return bayNumber;
}
int Message::getWWID()
{
	return WWID;
}
std::string Message::getString()
{
	return stringData;
}

void Message::parseID(int toParse, int size, char* toStart)
{
	std::ostringstream os;
	os << toParse;
	std::string osStr = os.str();
	if (osStr.length() < size)
		osStr = std::string(size-osStr.length(),'0').append(osStr);
	char tmpBuf[size];
	std::strcpy(tmpBuf,osStr.c_str());
	//itoa(toParse,tmpBuf,10);
	for (int i=0; i<size; i++)
		toStart[i] = tmpBuf[i];
}

int Message::unParseID(char* toUnParse, int size)
{
	char tmpBuf[size];
	for (int i = 0; i<size; i++)
		tmpBuf[i] = toUnParse[i];
	tmpBuf[size] = 0;
	return atoi(tmpBuf);
}

char* Message::parseBuffer(char* toParse, int size)
{
	char *tmpBuf =(char*) malloc (size);
	for (int i = 0;i<size;i++)
		tmpBuf[i] = toParse[i];
	return tmpBuf;
}

bool Message::unParseBool(char *toParse)
{
	if (toParse[0] == '1')
		return true;
	else
		return false;
}

void Message::parseBool(bool toParse, char* toWrite)
{
	if (toParse)
		toWrite[0] = '1';
	else
		toWrite[0] = '0';
}

void Message::copyChars(char* toStart, char* fromStart, int toCopy)
{
	for (int i = 0; i < toCopy;i++)
		toStart[i] = fromStart [i];
}
