//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//common/MessageBuffer.cpp

#include "MessageBuffer.h"

MessageBuffer::MessageBuffer()
{
	this->first = NULL;
}

MessageBuffer::~MessageBuffer()
{
	delete this->first;

}

Message* MessageBuffer::getFirst()
{
	if (this->first != NULL)
	{
		Message *tmpStore = this->first;
		this->first = tmpStore->next;
		tmpStore->next = NULL;
		return tmpStore;
	}
	else
		return NULL;
}

void MessageBuffer::storeMessage(Message *toStore)
{
	Message *mesPtr;
	if (this->first == NULL) // no messages in buffer
		this->first = toStore;  // store as first message in buffer
	else
	{
		mesPtr = this->first;
		while (mesPtr->next != NULL) // keep going until last message in buffer is found
			mesPtr = mesPtr->next;
		mesPtr->next = toStore; // set new message as next on last message
	}

}
