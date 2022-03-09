//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/UDPSender.cpp

#include "UDPSender.h" 
#include <string.h>
#include <unistd.h>

UDPSender::UDPSender(std::string addr, int port)
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
}

UDPSender::~UDPSender()
{
	//freeaddrinfo(f_addrinfo);
	//close(f_socket);
}

int UDPSender::get_socket()
{
	return f_socket;
}
int UDPSender::get_port()
{
	return f_port;
}
std::string UDPSender::get_addr()
{
	return f_addr;
}

int UDPSender::send(char *msg, size_t size)
{
	return sendto(f_socket, msg, size, 0, f_addrinfo->ai_addr, f_addrinfo->ai_addrlen);
}
