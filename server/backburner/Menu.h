//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/Menu.h 


#ifndef ServerMenuH
#define ServerMenuH


#include "BoxTree.h"

class Menu
{
private:
std::string header;
std::string prompt;
User *currentUser;

public:
void mainMenu();
void userSettingsMenu();	
void setHeader();
void ClearScreen();
void getInput(std::string *stringInput);
void getInput(int *intInput);
void getInput(char *charInput);
void getMenuInput();
void setMenuOption(char option, std::string label, Level minLevel, void* fnToDo);
};





#endif
