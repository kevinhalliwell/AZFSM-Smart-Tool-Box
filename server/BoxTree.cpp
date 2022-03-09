//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/BoxTree.cpp

#include "BoxTree.h"

BoxTree::BoxTree()
{
	this->root = NULL; // nothing at root
}

BoxTree::~BoxTree()
{
	if (this->root != NULL)
		delete this->root;
}

void BoxTree::insertBox(Box *toolBox)
{
	if (this->root == NULL)
		this->root = toolBox;
	else
		insertBox(this->root,toolBox);
}

void BoxTree::insertBox(Box *parentBox, Box *toolBox)
{
	if ((toolBox->getBay() < parentBox->getBay()) || (toolBox->getBay() == parentBox->getBay() && toolBox->getID() < parentBox->getID())) // new toolBox bay number or ID string is less than parent
		{
			if (parentBox->leftChild == NULL) // no left Child on parent Box
			{
				parentBox->leftChild = toolBox;
			}
			else // left child exists
				insertBox(parentBox->leftChild,toolBox);
		}
	else if ((toolBox->getBay() > parentBox->getBay()) || (toolBox->getBay() == parentBox->getBay() && toolBox->getID() > parentBox->getID())) // new toolBox bay number is greater than parent
	{
		if (parentBox->rightChild == NULL) // no right child on parent Box
			parentBox->rightChild = toolBox;
		else // right child exists
			insertBox(parentBox->rightChild,toolBox);
	}
}

void BoxTree::printTreeInventory(Box *node)
{
	if (node != NULL)
	{
		printTreeInventory(node->leftChild);
		cout << "Bay " << node->getBay() << ": " << node->getID() << endl;
		if (node->getDrawers() <= 0)
			cout << "No drawer data to display" << endl;
		else
		{
			for (int i = 0; i < node->getDrawers(); i++)
			{
				cout << "Drawer " << i+1 << " inventory:" << endl;
				Drawer *toPrint = node->getDrawer(i);
				if (toPrint != NULL)
					if (toPrint->isConfigured())
					{
						int sensors = toPrint->getSensors();
						for (int j = 0; j < sensors; j++)
						{
							Tool *toolToPrint = toPrint->getTool(j);
							cout << "Sensor " << j << ": ";
							if (toolToPrint->getName() == UNDEFINED_TOOL_NAME)
							{
								cout << "No tool data for this sensor." << endl;
							}
							else
							{
								cout << toolToPrint->getName() << " ";
								if (toolToPrint->isTracking())
								{
									if (toolToPrint->isPresent())
										cout << "Present" << endl;
									else
										cout << "Checked Out By: " << toolToPrint->isCheckedOutBy()->getWWID() << endl;
								}
								else
									cout << "Not Tracking" << endl;
							}
								


						}
					}
					else
						cout << "Sensors not configured for this drawer." << endl;
			}

		}
		printTreeInventory(node->rightChild);
	}
}

int BoxTree::listBoxes()
{
	int boxes = 0;

	if (this->root != NULL)
	{
		boxes = 1;
		boxes = printBox(this->root,boxes);
	}
	else
		cout << "No Boxes" << endl;

	return boxes;

}

int BoxTree::printBox(Box *node,int boxNumber)
{
	if (node != NULL)
	{
		boxNumber = printBox(node->leftChild,boxNumber);
		cout << "(" << boxNumber << ") - ID: (" << node->getBoxID() <<") Bay " << node->getBay() << ": " << node->getID() << endl;
		boxNumber++;
		boxNumber = printBox(node->rightChild,boxNumber);
	}
	return boxNumber;
}


Box* BoxTree::getBox(int boxNumber)
{
	int *boxNo, *boxToFind;
	boxNo = new int(1);
	boxToFind = new int(boxNumber);
	if (this->root != NULL)
	{
		return checkBox(this->root,boxNo,boxToFind);
	}
	else
		return NULL;


}

Box* BoxTree::checkBox(Box* node, int *boxNumber, int *boxToFind)
{
	Box *tmpBox = NULL;
	if (node != NULL)
	{
		tmpBox = checkBox(node->leftChild,boxNumber,boxToFind);
		if (tmpBox != NULL)
			return tmpBox;
		if (*boxNumber == *boxToFind)
		{
			return node;
		}
		else
			*boxNumber = *boxNumber + 1;
		tmpBox = checkBox(node->rightChild,boxNumber,boxToFind);
	}
	return tmpBox;
}

Box* BoxTree::getBox(char boxID)
{
	if (this->root != NULL)
	{
		return checkBox(this->root,boxID);
	}
	else
		return NULL;
}

Box* BoxTree::checkBox(Box* node, char boxID)
{
	if (node != NULL)
	{
		if (checkBox(node->leftChild,boxID) != NULL)
			return checkBox(node->leftChild,boxID);
		else if (node->getBoxID() == boxID)
			return node;
		else if (checkBox(node->rightChild,boxID) != NULL)
			return checkBox(node->rightChild,boxID);
	}
	else
		return NULL;
}
int BoxTree::numberBoxes()
{
	int *counter = new int(0);
	if (this->root != NULL)
	{
		getBoxes(this->root,counter);
	}
	else
		return *counter;
}

int BoxTree::getBoxes(Box *node,int *counter)
{
	if (node != NULL)
	{
		if (node->leftChild != NULL)
			getBoxes(node->leftChild,counter);
		*counter = *counter +1;
		if (node->rightChild !=NULL)
			getBoxes(node->rightChild,counter);
	}
}

void BoxTree::setViewing(bool status)
{
	viewing = status;
}

bool BoxTree::getViewing()
{
	return viewing;
}