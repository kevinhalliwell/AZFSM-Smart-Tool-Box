//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/common.h 

#ifndef ServerCommonH
#define ServerCommonH

#include <string>
#include <iostream>
#include <stdlib.h> // for atoi
#include <atomic>

using namespace std;

//Global Atomic Variables
extern std::atomic_int stopReading;
extern std::atomic_int stopHandling;
extern std::atomic_int monitorMessages;

//Define Global Constants

const std::string UNDEFINED_TOOL_NAME = "Undefined";
const int MAX_TOOLBOX_STRING_LENGTH = 20;
const std::string IPAddress = "192.168.1.101";
const int incPort = 1702;
const int outPort = 1701;
//Define types

typedef enum
{NONE, MT, ADMIN, GL, AM } Level;


#endif