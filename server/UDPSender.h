//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/UDPSender.h 


#ifndef UDPSenderH
#define UDPSenderH

#include "UDPServer.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <stdio.h>

class UDPSender
{
private:

	int f_socket;
	int f_port;
	std::string f_addr;
	struct addrinfo * f_addrinfo;


public:
	UDPSender(std::string addr, int port);
	~UDPSender();
	int get_socket();
	int get_port();
	std::string get_addr();
	int send(char *msg, size_t size);

};


#endif