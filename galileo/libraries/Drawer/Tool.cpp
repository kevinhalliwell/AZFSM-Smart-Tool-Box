//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//galileo/Tool.cpp

#include "Tool.h"

Tool::Tool()
{
	serverNotifiedChange = true;
	toolPresentOnServer = false;
}

//Mutators
void Tool::setPin(int pin)
{
	toolPin = pin;
}
void Tool::setSensorAdjust(int sensorAdjust)
{
	toolSensorAdjust = sensorAdjust;
}

void Tool::setNoLightAdjust(int noLightAdjust)
{
	this->noLightAdjust = noLightAdjust;
}
void Tool::setServerNotified(bool notified)
{
	serverNotifiedChange = notified;
}
void Tool::setServerPresent(bool present)
{
	toolPresentOnServer=present;
}

//Accessors
int Tool::getPin()
{
	return toolPin;
}

int Tool::getToolSensorAdjust()
{
	return toolSensorAdjust;
}
int Tool::getNoLightAdjust()
{
	return noLightAdjust;
}
bool Tool::getServerNotified()
{
	return serverNotifiedChange;
}
bool Tool::getServerPresent()
{
	return toolPresentOnServer;
}



//Functions
bool Tool::checkUpdate() // returns true if the tool's status has changed
{
	if (toolPresentOnServer && serverNotifiedChange) // server doesn't think tool is here, no change reported
	{
		if (!isPresent())
		{
			if (SERIAL_DEBUG)
			{
				Serial.print("TOOL AT SENSOR ");
				Serial.print(toolPin);
				Serial.println(" WAS REMOVED.");
			}
			serverNotifiedChange = false;
			return true;
		}
	}
	else if(!toolPresentOnServer && serverNotifiedChange) // server doesn't think tool is here, no change reported
	{
		if (isPresent())
		{
			if(SERIAL_DEBUG)
			{
				Serial.print("TOOL AT SENSOR ");
				Serial.print(toolPin);
				Serial.println(" WAS REPLACED");
			}
			serverNotifiedChange = false;
			return true;
		}

	}
	else
		return false;
}

bool Tool::isPresent()
{
	int lightLevel = -1*(analogRead(toolPin) - toolSensorAdjust);
	if(lightLevel > noLightAdjust)
		return false;
	else
		return true;
}