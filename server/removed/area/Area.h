//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/Area.h

#ifndef ServerAreaH
#define ServerAreaH
#include "common.h"
#include "Box.h"


class Area
{
private:
	std::string name;
	int numberOfBoxes;
	Box[] boxes;
public:
	Area(std::string name, int boxes);
	~Area();
	bool addBox(std::string name, int bay, int drawers,User* requesting);
	bool addDrawer(int box, int drawer, int sensors,User* requesting);
	bool addTool(int box, int drawer, int sensor, std::string name,User* requesting);

};


#endif