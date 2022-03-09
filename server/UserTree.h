//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/UserTree.h

#ifndef ServerUserTreeH
#define ServerUserTreeH


#include "User.h"

class UserTree
{
private:

public:
	User* root;

	UserTree();
	~UserTree();
	void insertUser(User *toInsert);
	void insertUser(User *node, User *toInsert);
	User* getUser(int WWID);
	User* getUser(User *node,int WWID);
	void printUserTree();
	void printUserTree(User *node);
	int numberUsers();
	void getUsers(User *node,int *counter);

};

#endif