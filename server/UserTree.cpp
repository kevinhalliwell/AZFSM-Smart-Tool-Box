//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/UserTree.cpp

#include "UserTree.h"


UserTree::UserTree()
{
	this->root = NULL;
}

UserTree::~UserTree()
{
	if (this->root != NULL)
		delete this->root;
}

void UserTree::insertUser(User *toInsert)
{
	if (this->root == NULL)
		this->root = toInsert;
	else
		insertUser(this->root,toInsert);
}

void UserTree::insertUser(User *node, User *toInsert)
{
	if (toInsert->getWWID() < node->getWWID()) // Goes down left child tree
		if (node->leftChild == NULL){
			node->leftChild = toInsert;
		}
		else{
			insertUser(node->leftChild,toInsert);
		}
	else if (toInsert->getWWID() > node->getWWID()) // Goes down right child tree
		if (node->rightChild == NULL){
			node->rightChild = toInsert;
		}
		else{
			insertUser(node->rightChild,toInsert);
		}
		//if they are equal it will exit without storing the user, because the user already exists in memory.
}

User* UserTree::getUser(int WWID)
{
	User *toReturn = NULL;
	if (!(this->root == NULL))
		toReturn = getUser(this->root,WWID);
	if (toReturn == NULL)
	 	{
	 		toReturn = new User(WWID, NONE);
	 		insertUser(toReturn);
	 	}
	
		return toReturn;
}

User* UserTree::getUser(User* node,int WWID)
{
	if (node != NULL)
	{
		if (node->getWWID() == WWID)
			return node;
		else if (WWID < node->getWWID())
			return getUser(node->leftChild,WWID);
		else if (WWID > node->getWWID())
			return getUser(node->rightChild,WWID);
	}
	else
		return NULL;
}

void UserTree::printUserTree()
{
	if (this->root == NULL)
		cout << "No users to display." << endl;
	else
	{
		printUserTree(this->root);
	}
}

void UserTree::printUserTree(User* node)
{
	if (node != NULL)
	{
		if (node->leftChild != NULL)
			printUserTree(node->leftChild);
		cout << node->getWWID() << ": " << node->getAccessLevelString() << endl;
		if (node->rightChild != NULL)
			printUserTree(node->rightChild);
	}
}

int UserTree::numberUsers()
{
	int *counter = new int(0);
	if (this->root != NULL)
	{
		getUsers(this->root,counter);
	}
	else
		return *counter;
}

void UserTree::getUsers(User *node,int *counter)
{
	if (node != NULL)
	{
		if (node->leftChild != NULL)
			getUsers(node->leftChild,counter);
		*counter = *counter +1;
		if (node->rightChild !=NULL)
			getUsers(node->rightChild,counter);
	}
}