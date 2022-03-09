//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//galileo/ToolServer.cpp


#include "ToolServer.h"

ToolServer::ToolServer(EthernetUDP *udp,IPAddress serverIP, unsigned int serverPort,int boxID)
{
	Udp = udp;
	this->boxID = boxID;
	this->serverIP = serverIP;
	this->serverPort = serverPort;
	lockCommandReceived= false;
	unlockCommandReceived = false;
	outBuf = new MessageBuffer();
	inBuf = new MessageBuffer();
	WWID = 0;
	locked = true;
}

ToolServer::~ToolServer()
{
	Udp->stop();
	delete this->outBuf;
	delete this->inBuf;
}

void ToolServer::sendMessage(Message *toSend)
{
	char replyBuffer[MSG_BUFFER_SIZE];

	
	toSend->toChar(replyBuffer);
	if (SERIAL_DEBUG)
	{
		Serial.println("Sending: ");
		Serial.println(replyBuffer);
	}
	Udp->beginPacket(serverIP,serverPort);
	Udp->write(replyBuffer);
	Udp->endPacket();
	if (SERIAL_DEBUG)
		Serial.println("Sent.");
	//delete toSend;
}

void ToolServer::checkForMessage()
{
	
	char msgBuf[MSG_BUFFER_SIZE];
	if (Udp->parsePacket() > 0)
	{
		Serial.println("Message received.");
		Udp->read(msgBuf,MSG_BUFFER_SIZE);
		inBuf->storeMessage(new Message(msgBuf));
	}
}

void ToolServer::sendOut()
{
	Message *toGo = outBuf->getFirst();
	if (toGo != NULL)
	{
		sendMessage(toGo);
	}

}

void ToolServer::processInBuffer()
{
	Message *toProcess = inBuf->getFirst();
	if (toProcess != NULL)
	{
		switch(toProcess->getType())
		{
			case ACK_TYPE_CHAR:
				if (SERIAL_DEBUG)
					Serial.println("ACK MESSAGE RECEIVED.");
				break;
			case SG_UNLOCK_TYPE_CHAR:
				if (SERIAL_DEBUG)
				{
					Serial.println("UNLOCK BOX COMMAND RECEIVED.");
					Serial.print("WWID: ");
					Serial.println(toProcess->getWWID());
				}
				unlockCommandReceived = true;
				WWID = toProcess->getWWID();
				break;
			case SG_LOCK_TYPE_CHAR:
				if (SERIAL_DEBUG)
					Serial.println("LOCK BOX COMMAND RECEIVED.");
				lockCommandReceived = true;
				break;
		}
		delete toProcess;
	}
}
void ToolServer::notifyDrawerOpened(Drawer *opened)
{
	outBuf->storeMessage(new Message(BOX_SENDER_CHAR,GS_OPEN_TYPE_CHAR,boxID,opened->getDrawerNumber(),locked,WWID));
}

void ToolServer::notifyDrawerClosed(Drawer *closed)
{
	outBuf->storeMessage(new Message(BOX_SENDER_CHAR,GS_CLOSED_TYPE_CHAR,boxID,closed->getDrawerNumber(),locked,WWID));	
}

void ToolServer::notifyInventoryUpdated(Drawer *updated)
{
	
	for (int i = 0; i < updated->getSensors(); i++)
	{
		if (!(updated->getTool(i)->getServerNotified()))
		{
			if(updated->getTool(i)->getServerPresent()) // not notified of change from present (aka removed)
			{
				outBuf->storeMessage(new Message(BOX_SENDER_CHAR,GS_REMOVED_TYPE_CHAR,boxID,updated->getDrawerNumber(),i,locked,WWID));
				updated->getTool(i)->setServerPresent(false);
			}
			else //not notified of change from not present (aka replaced)
			{
				outBuf->storeMessage(new Message(BOX_SENDER_CHAR,GS_RETURNED_TYPE_CHAR,boxID,updated->getDrawerNumber(),i,locked,WWID));
				updated->getTool(i)->setServerPresent(true);
			}
			updated->getTool(i)->setServerNotified(true);
		}
	}
}

bool ToolServer::unlockReceived()
{
	return unlockCommandReceived;
}
bool ToolServer::lockReceived()
{
	return lockCommandReceived;
}

void ToolServer::setUnlockReceived(bool setting)
{
	unlockCommandReceived = setting;
}

void ToolServer::setLockReceived(bool setting)
{
	lockCommandReceived = setting;
}

void ToolServer::clearWWID()
{
	WWID = 0;
}

void ToolServer::setLocked(bool setting)
{
	locked = setting;
}

void ToolServer::notifyLocked()
{
	outBuf->storeMessage(new Message(BOX_SENDER_CHAR,GS_LOCK_TYPE_CHAR,boxID,WWID));
	clearWWID();
}

void ToolServer::notifyUnlocked()
{
	outBuf->storeMessage(new Message(BOX_SENDER_CHAR,GS_UNLOCK_TYPE_CHAR,boxID,WWID));
}