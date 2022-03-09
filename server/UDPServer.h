//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/UDPServer.h 

#ifndef UDPServerH
#define UDPServerH


#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdexcept>
#include <stdio.h>

class UDPServer
{
private:
	int f_socket;
	int f_port;
	std::string f_addr;
	struct addrinfo * f_addrinfo;

public:
	UDPServer(std::string addr, int port);
	~UDPServer();
	int getSocket();
	int getPort();
	std::string getAddr();

	int receiveMessage(char *msg, size_t max_size,int max_wait_ms);

};


#endif