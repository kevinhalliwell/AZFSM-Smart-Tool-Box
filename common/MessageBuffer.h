//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//common/MessageBuffer.h

#ifndef galileoMessageBufferH
#define galileoMessageBufferH

#include "Messages.h"

class MessageBuffer{
private:

	Message *first; // first in queue

public:
	MessageBuffer();
	~MessageBuffer();

	Message* getFirst();
	void storeMessage(Message *toStore);


};


#endif