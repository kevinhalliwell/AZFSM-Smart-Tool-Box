//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/BoxTree.h


#ifndef ServerBoxTreeH
#define ServerBoxTreeH
#include "Box.h"

class BoxTree
{
private:
	bool viewing;

public:
	Box *root;

	BoxTree();
	~BoxTree();

	void insertBox(Box *toolBox);
	void insertBox(Box *parentBox, Box *toolBox);

	void printTreeInventory(Box *node);
	int listBoxes();
	int printBox(Box *node,int boxNumber);
	Box *getBox(int boxNumber);
	Box *checkBox(Box* node, int *boxNumber, int *boxToFind);
	Box *getBox(char boxID);
	Box *checkBox(Box* node, char BoxID);
	int numberBoxes();
	int getBoxes(Box *node,int *counter);
	void setViewing(bool status);
	bool getViewing();

};


#endif