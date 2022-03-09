//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/UDPServer.cpp

#include "UDPServer.h"
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace std;

UDPServer::UDPServer(std::string addr, int port)
{
	this->f_port = port;
	this->f_addr = addr;

	char decimal_port[16];
    snprintf(decimal_port, sizeof(decimal_port), "%d", f_port);
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_protocol = IPPROTO_UDP;
    int r(getaddrinfo(addr.c_str(), decimal_port, &hints, &f_addrinfo));
    if (r != 0 || f_addrinfo == NULL)
    {
    	//throw udp_client_server_runtime_error(("Invalid address or port: \"" + addr + ":" + decimal_port + "\"").c_str());
    }
    f_socket = socket(f_addrinfo->ai_family, SOCK_DGRAM | SOCK_CLOEXEC, IPPROTO_UDP);
    if (f_socket == -1)
    {
    	freeaddrinfo(f_addrinfo);
    	//throw udp_client_server_runtime_error(("Could not create socket for: \"" + addr + ":" + decimal_port _ "\"").c_str());
    }
    r = bind(f_socket, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
    if (r != 0)
    {
    	freeaddrinfo(f_addrinfo);
    	close(f_socket);
    	//throw udp_client_server_runtime_error(("Could not bind UDP socket with: \"" + addr + ":" + decimal_port + "\"").c_str());
    }
}

UDPServer::~UDPServer()
{
	//freeaddrinfo(f_addrinfo);
	//close(socket);
}

int UDPServer::getSocket()
{
	return f_socket;
}

int UDPServer::getPort()
{
	return f_port;
}

std::string UDPServer::getAddr()
{
	return f_addr;
}

int UDPServer::receiveMessage(char *msg, size_t max_size,int max_wait_ms)
{
	fd_set s;
	FD_ZERO(&s);
	FD_SET(f_socket, &s);
	struct timeval timeout;
	timeout.tv_sec = max_wait_ms / 1000;
	timeout.tv_usec = (max_wait_ms % 1000) * 1000;
	int retval = select(f_socket + 1, &s, &s, &s, &timeout);
	if (retval == -1)
	{
		return -1;
	}
	if (retval >0)
	{
		return ::recv(f_socket,msg,max_size,0);
	}

	return -1;
}
