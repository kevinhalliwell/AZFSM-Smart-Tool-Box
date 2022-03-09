//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//galileo/common.h 

#ifndef GalileoCommonH
#define GalileoCommonH

#include "Arduino.h"

using namespace std;

//Global Constants
const int UPDATE_DELAY_MS = 50;
const int BOX_RELOCK_COUNTER_MS = 20000;
const int MESSAGE_CHECK_MS = 50;
const int MSG_SEND_MS = 100;
const int UPDATE_STATUS_MS = 500;
const int COUNTDOWN_MS = 1000;
const bool SERIAL_DEBUG = true;

//Networking constants

const unsigned int PORT=1701;

#endif
