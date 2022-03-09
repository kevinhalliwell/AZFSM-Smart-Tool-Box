//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/MessageHandler.cpp

#include "MessageHandler.h"
#include "common.h"

MessageHandler::MessageHandler(BoxTree *boxTree, UserTree *userTree,UDPServer *udpServ)
{
	this->incoming = new MessageBuffer();
	this->outgoing = new MessageBuffer();
	this->boxTree = boxTree;
	this->userTree = userTree;
	this->udpServ = udpServ;
}
MessageHandler::~MessageHandler()
{
	delete this->incoming;
	delete this->outgoing;
}
void MessageHandler::checkMessages()
{
	char message[MSG_BUFFER_SIZE];
	int bytes;
	while (!stopReading)
	{
		bytes = udpServ->receiveMessage(message,MSG_BUFFER_SIZE,MSG_WAIT_TIME);
			if (bytes >0)
				{
					incoming->storeMessage(new Message(message));
				}
	}
}
void MessageHandler::processMessages()
{
	Message *curMsg;
	char message[MSG_BUFFER_SIZE];
	Box *from;
	User *msgUsr;
	while (!stopHandling)
	{
		curMsg = incoming->getFirst();
		if (curMsg != NULL)
		{
			switch (curMsg->getSenderType())
			{
				case APP_SENDER_CHAR:
					from = boxTree->getBox(curMsg->getBoxID());
					msgUsr = userTree->getUser(curMsg->getWWID());
					curMsg->toChar(message);
					if (monitorMessages)
					{
						cout << "Message received from WWID: " << curMsg->getWWID() << endl;
					}
					switch (curMsg->getType())
					{
						case AS_UNLOCK_TYPE_CHAR:
							if (from != NULL)
							{
								if (monitorMessages)
								{
									cout << "Requesting box unlock for box " << from->getID() << endl;
								}
								appUnlockBox(from,msgUsr,curMsg);
							}
							else if (monitorMessages)
								cout << "Unable to find requested box." << endl;
							break;
						case AS_LOCK_TYPE_CHAR:
							if (from != NULL)
								appLockBox(from,msgUsr,curMsg);
							break;
						case AS_REGISTER_TYPE_CHAR:
							if (monitorMessages)
							{
								cout << "Requesting registration from IP: " << curMsg->getString() << endl;
							}
							registerUser(msgUsr,curMsg);
							break;
						case AS_DEREGISTER_TYPE_CHAR:
							deregisterUser(msgUsr,curMsg);
							break;
						case AS_INFO_TYPE_CHAR:
							appInfoRequest(msgUsr,curMsg);
					}
				break;

				case BOX_SENDER_CHAR:
					from = boxTree->getBox(curMsg->getBoxID());
					msgUsr = userTree->getUser(curMsg->getWWID());
					if (monitorMessages)
					{
						cout << "Message received from toolbox " << curMsg->getBoxID() << " : ";
						if (from != NULL)
							cout << from->getID() << " in bay " << from->getBay() << ":" << endl;
						else
							cout <<" Unable to find toolbox data." << endl;
					}
					if (from != NULL) // validate toolbox ID.
						switch (curMsg->getType())
						{
							case GS_UNLOCK_TYPE_CHAR:
								boxUnlocked(from,msgUsr,curMsg);
								break;
							case GS_LOCK_TYPE_CHAR:
								boxLocked(from,msgUsr,curMsg);
								break;
							case GS_OPEN_TYPE_CHAR:
								drawerOpened(from,msgUsr,curMsg);
								break;
							case GS_CLOSED_TYPE_CHAR:
								drawerClosed(from,msgUsr,curMsg);
								break;
							case GS_REMOVED_TYPE_CHAR:
								toolRemoved(from,msgUsr,curMsg);
								break;
							case GS_RETURNED_TYPE_CHAR:
								toolReturned(from,msgUsr,curMsg);
								break;
						}

			}
		}

		curMsg = outgoing->getFirst();
		if (curMsg != NULL)
		{
			switch (curMsg->getType())
			{
				case SG_UNLOCK_TYPE_CHAR:
				case SG_LOCK_TYPE_CHAR:
					from = boxTree->getBox(curMsg->getBoxID());
					curMsg->toChar(message);
					from->getSender()->send(message,MSG_BUFFER_SIZE);
					break;
				case SA_REGISTER_TYPE_CHAR:
				case SA_INFO_TYPE_CHAR:
					msgUsr = userTree->getUser(curMsg->getWWID());
					curMsg->toChar(message);
					if (msgUsr->getSender() != NULL)
						msgUsr->getSender()->send(message,MSG_BUFFER_SIZE);
					break;
			}
			delete curMsg;
		}
	}
}


void MessageHandler::addOutgoing(Message *message)
{
	outgoing->storeMessage(message);
}
void MessageHandler::drawerOpened(Box *from, User *loggedIn, Message *msg)
{
	if (msg->getDrawerID() >= 0 && msg->getDrawerID() < from->getDrawers())
	{
		if (monitorMessages)
		{
			if(loggedIn->getWWID() > 0)
			{
				cout << "Drawer number " << msg->getDrawerID() << " was opened by WWID: ";
				cout << loggedIn->getWWID() << endl;
			}
			else
			{
				cout << "WARNING: Unauthorized access to drawer number " << msg->getDrawerID() << endl;
			}
		}
	}
	else
	{
		if (monitorMessages)
			cout << "Box reporting unconfigured drawer number: " << msg->getDrawerID() << endl;
	}
}
void MessageHandler::drawerClosed(Box *from, User *loggedIn, Message *msg)
{
	if (msg->getDrawerID() >= 0 && msg->getDrawerID() < from->getDrawers())
	{
		if (monitorMessages)
		{
			if (loggedIn->getWWID() > 0)
			{
				cout << "Drawer number: " << msg->getDrawerID() << " was closed by WWID: ";
				cout << loggedIn->getWWID() << endl;
			}
			else
			{
				cout << "Drawer number: " << msg->getDrawerID() << " was closed by an unregistered user."<< endl;
			}
		}
	}
	else
	{
		if (monitorMessages)
			cout << "Box reporting unconfigured drawer number: " << msg->getDrawerID() << endl;	
	}
}
void MessageHandler::toolRemoved(Box *from, User *loggedIn, Message *msg)
{
	if (msg->getDrawerID() >= 0 && msg->getDrawerID() < from->getDrawers())
	{
		int sensorID = msg->getSensorID();
		if (sensorID >= 0 && sensorID <= from->getDrawer(msg->getDrawerID())->getSensors())
		{
			Tool *removed = from->getDrawer(msg->getDrawerID())->getTool(msg->getSensorID());
			if (monitorMessages)
			{
				cout <<"Box reporting that " << removed->getName() << " was removed from ";
				cout <<"sensor " << msg->getSensorID() << " in drawer " << msg->getDrawerID();
				if (loggedIn->getWWID() > 0)
					cout <<" by WWID: " << loggedIn->getWWID() << endl;
				else
					cout << " by an unregistered user." << endl;
			}
			//create log entry
			removed->checkOut(loggedIn);
			if (boxTree->getViewing())
			{
				cout << std::string(100,'\n');
				cout << "[---------------Tool Boxes---------------]" << endl << endl;
				if (boxTree->root == NULL)
					cout << "No boxes to display." << endl;
				else
				{
					boxTree->printTreeInventory(boxTree->root);
				}
				cout << "B to go back." << endl;
			}
		}
		else
		{
			if (monitorMessages)
				cout <<"Box reporting invalid sensor number." << endl;
		}
	}
	else
	{
		if (monitorMessages)
			cout << "Box reporting invalid drawer number." << endl;	
	}
}
void MessageHandler::toolReturned(Box *from, User *loggedIn, Message *msg)
{
	if (msg->getDrawerID() >= 0 && msg->getDrawerID() < from->getDrawers())
	{
		int sensorID = msg->getSensorID();
		if (sensorID >= 0 && sensorID <= from->getDrawer(msg->getDrawerID())->getSensors())
		{
			Tool *removed = from->getDrawer(msg->getDrawerID())->getTool(msg->getSensorID());
			if (monitorMessages)
			{
				cout <<"Box reporting that " << removed->getName() << " was returned to ";
				cout <<"sensor " << msg->getSensorID() << " in drawer " << msg->getDrawerID();
				if (loggedIn->getWWID() > 0)
					cout <<" by WWID: " << loggedIn->getWWID() << endl;
				else
					cout << " by an unregistered user." << endl;
			}
			//create log entry
			removed->checkIn(loggedIn);
			if (boxTree->getViewing())
			{
				cout << std::string(100,'\n');
				cout << "[---------------Tool Boxes---------------]" << endl << endl;
				if (boxTree->root == NULL)
					cout << "No boxes to display." << endl;
				else
				{
					boxTree->printTreeInventory(boxTree->root);
				}
				cout << "B to go back." << endl;
			}
		}
		else
		{
			if (monitorMessages)
				cout <<"Box reporting invalid sensor number." << endl;
		}
	}
	else
	{
		if (monitorMessages)
			cout << "Box reporting invalid drawer number." << endl;	
	}
}

void MessageHandler::boxLocked(Box *from, User *loggedIn, Message *msg)
{
	if (monitorMessages)
		cout <<"Box has been locked." << endl;
	//Log box locking
	from->setLocked(true);
}

void MessageHandler::boxUnlocked(Box *from, User *loggedIn, Message *msg)
{
	if (monitorMessages)
		cout <<"Box has been unlocked." << endl;
	//Log box unlocking
	from->setLocked(false);
}

void MessageHandler::appUnlockBox(Box *toUnlock, User *loggedIn, Message *msg)
{
	if (loggedIn->hasRights())
	{
		outgoing->storeMessage(new Message(SERVER_SENDER_CHAR,SG_UNLOCK_TYPE_CHAR,msg->getBoxID(),msg->getWWID()));
		//create log entry
	}	
}

void MessageHandler::appLockBox(Box *toLock, User *loggedIn, Message *msg)
{
	if (loggedIn->hasRights())
	{
		outgoing->storeMessage(new Message(SERVER_SENDER_CHAR,SG_LOCK_TYPE_CHAR,msg->getBoxID(),msg->getWWID()));
		//create log entry
	}

}

void MessageHandler::registerUser(User *toRegister, Message *msg)
{
	toRegister->setIPAddress(msg->getString());
	outgoing->storeMessage(new Message(SERVER_SENDER_CHAR,SA_REGISTER_TYPE_CHAR,msg->getWWID(),toRegister->getAccessLevelString()));
}

void MessageHandler::deregisterUser(User *toDeregister, Message *msg)
{
	toDeregister->deregister();
}

void MessageHandler::appInfoRequest(User *requesting, Message *msg)
{
	if (requesting->hasRights())
	{
		if (msg->getBoxID() == BOX_ID_ALL)
		{
			if (monitorMessages)
			{
				cout << "User has requested updated data for all toolboxes." << endl;
			}
			//queue messages for every single tool :v
		}

	}
	if (requesting->hasAdminRights())
	{
		if (msg->getWWID() == WWID_ALL)
		{
			if (monitorMessages)
			{
				cout << "User has requested updated data for all users." << endl;
			}
			//queue messages for every user in tree
		}
	}
}