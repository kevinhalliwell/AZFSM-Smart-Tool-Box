//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//galileo/ToolServer.h

#ifndef GalileoToolServerH
#define GalileoToolServerH


#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "Drawer.h"
#include "common.h"
#include "MessageBuffer.h"

class Drawer;
class ToolServer
{
private:
	
	char packetBuffer[MSG_BUFFER_SIZE];
	int boxID;
	String replyBuffer;
	bool unlockCommandReceived;
	bool lockCommandReceived;
	EthernetUDP *Udp;
	IPAddress serverIP;
	unsigned int serverPort;
	MessageBuffer *inBuf;
	MessageBuffer *outBuf;
	int WWID;
	bool locked;

public:
	
	ToolServer(EthernetUDP *udp,IPAddress serverIP, unsigned int serverPort, int boxID);
	~ToolServer();
	void sendMessage(Message* toSend);
	void checkForMessage();
	void sendOut();
	void processInBuffer();
	void notifyDrawerOpened(Drawer *opened);
	void notifyDrawerClosed(Drawer *closed);
	void notifyInventoryUpdated(Drawer *updated);
	bool unlockReceived();
	bool lockReceived();
	void setUnlockReceived(bool setting);
	void setLockReceived(bool setting);
	void clearWWID();
	void setLocked(bool setting);
	void notifyLocked();
	void notifyUnlocked();

};
#endif 