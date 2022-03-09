//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/Area.cpp


#include "Area.h"

Area::Area(std::string name, int boxes)
{
	this.boxes = Box[boxes];
	this.name = name;
	this.numberOfBoxes = boxes;
}

Area::~Area()
{
	delete boxes;
}

bool Area::addBox(std::string name, int bay, int drawers,User* requesting)
{
	
}
	bool addDrawer(int box, int drawer, int sensors,User* requesting);
	bool addTool(int box, int drawer, int sensor, std::string name,User* requesting);