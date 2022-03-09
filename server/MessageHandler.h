//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/MessageHandler.h 


#ifndef ServerMessageHandlerH
#define ServerMessageHandlerH

#include "UDPServer.h"
#include "MessageBuffer.h"
#include "BoxTree.h"
#include "UserTree.h"
#include "UDPSender.h"



class MessageHandler
{
private:
MessageBuffer *incoming;
MessageBuffer *outgoing;
BoxTree *boxTree;
UserTree *userTree;
UDPServer *udpServ;

public:
	MessageHandler(BoxTree *boxTree, UserTree *userTree,UDPServer *udpServ);
	~MessageHandler();
	void checkMessages();
	void processMessages();
	void addOutgoing(Message *message);

	void drawerOpened(Box *from, User *loggedIn, Message *msg);
	void drawerClosed(Box *from, User *loggedIn, Message *msg);
	void toolRemoved(Box *from, User *loggedIn, Message *msg);
	void toolReturned(Box *from, User *loggedIn, Message *msg);
	void boxLocked(Box *from, User *loggedIn, Message *msg);
	void boxUnlocked(Box *from, User *loggedIn, Message *msg);
	void appUnlockBox(Box *toUnlock, User *loggedIn, Message *msg);
	void appLockBox(Box *toLock, User *loggedIn, Message *msg);
	void registerUser(User *toRegister, Message *msg);
	void deregisterUser(User *toDeregister, Message *msg);
	void appInfoRequest(User *requesting, Message *msg);
};


#endif

