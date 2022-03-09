//test driver main.cpp
#include "common.h"
#include "BoxTree.h"
#include "UserTree.h"
#include "UDPSender.h"
#include "MessageHandler.h"
#include <thread>


char mainMenu();
char userSettings();
void ClearScreen();
void newBox();
void drawerSetup(Box *boxToSetUp);
void displayBoxes();
void boxConfigMenu();
void boxMenu(Box* toSet);
void setupTools(Drawer *toSetup);
void drawerTrack(Drawer *toTrack);
void drawerStopTrack(Drawer *toStopTrack);
Drawer* drawerSelect(Box* toolBox);
Tool* toolSelect(Drawer *activeDrawer);
void toolMenu(Tool *activeTool);
void accessListMenu();
void displayAccessList();
void newUser();
Level selectAccessLevel();
void userMenu(User *toChange);
void monitor();
void lockUnlockMenu();



User *currentUser;
BoxTree *boxTree;
UserTree *userTree;
MessageHandler *handler;
std::atomic_int stopReading;
std::atomic_int stopHandling;
std::atomic_int monitorMessages;
int main()
{
	currentUser = new User();
	userTree = new UserTree();
	boxTree = new BoxTree();
	handler = new MessageHandler(boxTree,userTree,new UDPServer(IPAddress,incPort));
	stopReading = 0;
	stopHandling = 0;
	monitorMessages = 0;
	std::thread handling (&MessageHandler::processMessages,handler);
  	std::thread checking (&MessageHandler::checkMessages,handler);
	char userInput;
	do{
	userInput = mainMenu();
	} while (userInput != 'q' && userInput != 'Q');
	stopReading = 1;
	stopHandling = 1;
	handling.join();
	checking.join();
	delete handler;
	delete userTree;
	delete boxTree;
	delete currentUser;
	return 0;

}


char mainMenu()
{
	char input;
	char secondInput;
	bool userIn = false;
	do{
	ClearScreen();
	cout <<"[---------------Main Menu---------------]\n\n";
	if (currentUser->hasRights())
	{
		cout <<"(1) Display Toolboxes\n";
		cout <<"(2) Lock/Unlock a box.\n";
	}
	if (currentUser->hasAdminRights())
	{
		cout <<"(3) Toolbox Configuration\n";
		cout << "(4) Add a new toolbox\n";
	}
	cout << "(5) Monitor Mode\n";
	cout << "(S) User Settings\n";
	cout << "(Q) Quit\n";
	cin >> input;
	if ((currentUser->hasRights() && (input == '1' || input == '2')) || (currentUser->hasAdminRights() && (input == '3' || input == '4')) || input == 's' || input == 'S' || input == 'q' || input == 'Q' || input == '5')
		userIn = true;
	} while (userIn != true);
	switch (input)
	{
		case '1':
				displayBoxes();
				break;
		case '2':
				lockUnlockMenu();
				break;
		case '3':
				boxConfigMenu();
				break;
		case '4':
				newBox();
				break;
		case '5':
				monitor();
				break;
		case 's':
		case 'S':
				do{
				secondInput = userSettings();
				} while (secondInput != 'b' && secondInput != 'B');
				break;


	}
	return input;
}

char userSettings()
{
	char input;
	bool userIn = false;
	int userWWID;
	char secondInput;
	do{
	ClearScreen();
	cout <<"[---------------User Settings---------------]\n\n";
	cout << "(1) Set WWID\n";
	if (currentUser->hasAdminRights())
	{
		cout << "(2) Display Access List\n";
		cout << "(3) Manage Access List\n";
	}
	cout << "(B) Back to Main\n";
	cin >> input;
	if (input == '1' || (currentUser->hasAdminRights() && (input == '2' || input == '3')) || input == 'B' || input == 'b')
		userIn = true;
	} while(userIn != true);
	switch (input)
	{
		case '1':
				cout << "Please enter your WWID: ";
				cin >> userWWID;
				if (userWWID > 0)
				{	
					if (userTree->root == NULL)
					{
						currentUser = userTree->getUser(userWWID);
						currentUser->setAccessLevel(ADMIN);
					}
					currentUser = userTree->getUser(userWWID);
				}
				else
					cout << "\nError: Invalid WWID\n";
				break;
		case '2':
				displayAccessList();
				cout << "Enter B to go back." << endl;
				cin >> secondInput;
				break;
		case '3':
				accessListMenu();
				break;
	}
	return input;
}


void newBox()
{
	int bayNumber;
	std::string boxName;
	int drawers;
	char doDrawers;
	Box *newBox;
	std::string boxIPadd;
	ClearScreen();
	cout << "New Toolbox Setup\n";
	cout << "Enter bay number of new tool box: ";
	cin >> bayNumber;
	cin.sync();
	cout << "Enter tool box name: ";
	while(getline(cin,boxName))
	if (boxName != "")
	{
		break;
	}
	cout << "Enter number of drawers: ";
	cin >> drawers;
	cout << "Please enter the box IPAddress (192.168.1.xxx): ";
	cin >> boxIPadd;
	newBox = new Box(boxTree->numberBoxes() + 1, boxIPadd, boxName, bayNumber, drawers, currentUser);
	cout << "Would you like to configure drawers now? Y/N: ";
	cin >> doDrawers;
	switch (doDrawers)
	{
		case 'y':
		case 'Y':
				drawerSetup(newBox);
				break;
	}
	boxTree->insertBox(newBox);
}

void drawerSetup(Box *boxToSetUp)
{
	int sensors;
	std::string cont;
	ClearScreen();
	cout << "Beginning Drawer Setup for Box " << boxToSetUp->getID() << " in bay " << boxToSetUp->getBay() << endl;
	int drawers = boxToSetUp->getDrawers();
	if (drawers > 0)
		for (int i = 0; i < drawers; i++)
		{
			cout << "Please enter the number of sensors installed in drawer " << i << ":";
			cin >> sensors;
			if (boxToSetUp->drawerSetup(i,sensors,currentUser))
				cout << "\nDrawer " << i << " set up successfully." << endl;
			else
				cout << "\nDrawer " << i << " not set up successfully." << endl;
		}
	cout << "Press any key to continue." << endl;
	cin >> cont;
}

void ClearScreen()
{
	cout << std::string(100,'\n');
}

void displayBoxes()
{
	std::string b;
	ClearScreen();
	cout << "[---------------Tool Boxes---------------]" << endl << endl;
	if (boxTree->root == NULL)
		cout << "No boxes to display." << endl;
	else
	{
		boxTree->printTreeInventory(boxTree->root);
	}
	boxTree->setViewing(true);
	cout << "B to go back." << endl;
	cin >> b;
	boxTree->setViewing(false);

}

void boxConfigMenu()
{
	std::string input;
	int boxes;
	int selection;
	Box *boxSet;
	ClearScreen();
	cout << "[------------------Select a Tool Box to Configure----------------]" << endl;
	boxes = boxTree->listBoxes();
	cout << "(N) - Configure a new toolbox" << endl;
	cin >> input;
	if (input == "n" || input == "N")
		newBox();
	else
	{
		selection = atoi(input.c_str());
		if (selection > 0 && selection <= boxes)
		{
			boxSet = boxTree->getBox(selection);
			boxMenu(boxSet);
		}
	}	
}

void boxMenu(Box* toSet)
{
	char selection;
	std::string newName;
	char choice;
	int choiceI;
	Drawer *toSetup;
	Tool *selectedTool;
	do{
	ClearScreen();
	cout << "[Settings for Bay " << toSet->getBay() << ": " << toSet->getID() << "]" << endl;
	cout << "(1) Change tool box name" << endl;
	cout << "(2) Reconfigure drawer sensors" << endl;
	cout << "(3) Set up all tools in a drawer" << endl;
	cout << "(4) Begin tracking all tools in a drawer" << endl;
	cout << "(5) Stop tracking all tools in a drawer" << endl;
	cout << "(6) Change a single tool" << endl;
	cout << "(7) Delete box" << endl;
	cout << "(B) Back to main menu" << endl << endl;
	cout <<"Please make a selection: ";
	cin >> selection;
	switch (selection)
	{
		case '1':
				ClearScreen();
				cout << "Please enter a new name for this box: ";
				while(getline(cin,newName))
					if (newName != "")
					{
						break;
					}
				toSet->setID(newName);
				break;
		case '2':
				ClearScreen();
				cout << "This will clear all existing sensor and tool data." << endl << "Do you wish to continue? Y/N: ";
				cin >> choice;
				if (choice == 'y' || choice == 'Y')
					drawerSetup(toSet);
				break;
		case '3':
				ClearScreen();
				if (toSet->getDrawers() > 0)
				{
					cout << "This will configure all tools in a drawer." << endl << "Please choose a drawer (1) - ";
					cout << "(" << toSet->getDrawers() << "):";
					cin >> choiceI;
					if (choiceI > 0 && choiceI <= toSet->getDrawers())
					{
						setupTools(toSet->getDrawer(choiceI-1));
						cout << "Would you like to begin tracking all of these tools? Y/N: ";
						cin >> choice;
						if (choice == 'y' || choice == 'Y')
							drawerTrack(toSet->getDrawer(choiceI-1));

					}
					else
						cout << "Invalid choice." << endl;
				}
					break;
		case '4':
				ClearScreen();
				if (toSet->getDrawers() > 0)
				{
					cout << "This will begin tracking all tools in a drawer." << endl << "Please choose a drawer (1) - ";
					cout << "(" << toSet->getDrawers() << "):";
					cin >> choiceI;
					if (choiceI > 0 && choiceI <= toSet->getDrawers())
						drawerTrack(toSet->getDrawer(choiceI-1));
					else
						cout << "Invalid choice." << endl;
				}
				else
				{
					cout << "No drawers configured." << endl << "Enter B to return to previous menu." << endl;
					cin >> choice;
				}
				break;
		case '5':
				ClearScreen();
				if (toSet->getDrawers() > 0)
				{
					cout << "This will disable tracking for all tools in a drawer." << endl << "Please choose a drawer (1) - ";
					cout << "(" << toSet->getDrawers() << "):";
					cin >> choiceI;
					if (choiceI > 0 && choiceI <= toSet->getDrawers())
						drawerStopTrack(toSet->getDrawer(choiceI-1));
					else
						cout << "Invalid choice." << endl;
				}
				else
				{
					cout << "No drawers configured." << endl << "Enter B to return to previous menu." << endl;
					cin >> choice;
				}
				break;
		case '6':
				ClearScreen();
				if (toSet->getDrawers() > 0)
					toolMenu(toolSelect(drawerSelect(toSet)));
				else
					cout << "No drawers configured." << endl << "Enter B to return to previous menu." << endl;
				break;
		case '7':
				ClearScreen();
				cout << "This will delete the toolbox and all associated data. Are you sure? Y/N: ";
				cin >> choice;
				if (choice == 'y' || choice == 'Y')
					delete toSet;
				break;

	}
} while (selection != 'b' && selection != 'B');


}


void setupTools(Drawer *toSetup)
{
	ClearScreen();
	std::string toolName;
	cout << "Tool Configuration" << endl;
	for (int i = 0; i < toSetup->getSensors() ; i++)
	{
		cout << "Enter tool name for sensor " << i+1 << ": ";
		while(getline(cin,toolName))
					if (toolName != "")
					{
						break;
					}
		toSetup->toolSetup(i,toolName,currentUser);
	}
}

void drawerTrack(Drawer *toTrack)
{
	for (int i = 0; i < toTrack->getSensors() ; i++)
		toTrack->getTool(i)->startTracking(currentUser);

}

void drawerStopTrack(Drawer *toStopTrack)
{
	for (int i = 0; i < toStopTrack->getSensors(); i++)
		toStopTrack->getTool(i)->stopTracking(currentUser);
}


Drawer* drawerSelect(Box *toolBox)
{
	int selection;
	ClearScreen();
	cout << "[------------------Select a Drawer----------------]" << endl;
	for(int i = 0; i < toolBox->getDrawers(); i++)
		cout << "(" << i+1 << ") : Drawer " << i+1 << " : " << toolBox->getDrawer(i)->getSensors() << " sensors." << endl;
	do{
	cout << ":";
	cin >> selection;
	} while (selection < 0 || selection >toolBox->getDrawers());

		return toolBox->getDrawer(selection-1);
	
}

Tool* toolSelect(Drawer *activeDrawer)
{
	int selection;
	ClearScreen();
	cout << "[-----------Select a Tool------------]" << endl;
	for (int i = 0; i < activeDrawer->getSensors(); i++)
		cout << "(" << i+1 << ") : Sensor " << i+1 << ": " << activeDrawer->getTool(i)->getName() << endl;
	do{
		cout << ":";
		cin >> selection;
	} while (selection < 0 || selection > activeDrawer->getSensors());
	return activeDrawer->getTool(selection-1);
}

void toolMenu(Tool* activeTool)
{
	char select;
	std::string newName;
	cout <<"[Select an option]" << endl;
	cout << "(1) - Set Name" << endl;
	cout << "(2) - Begin Tracking" << endl;
	cout << "(3) - Stop Tracking" << endl;
	cout << "(B) - Back" << endl;
	cout << ":";
	cin >> select;
	switch (select)
	{
		case '1':
			cout << "Changing name for " << activeTool->getName() << "." << endl;
			cout << "Please enter new name: ";
			while(getline(cin,newName))
					if (newName != "")
					{
						break;
					}
			activeTool->setName(newName);
			break;
		case '2':
			if (activeTool->startTracking(currentUser))
				cout << "Now tracking " << activeTool->getName() << "." << endl;
			else
				cout << "Unable to begin tracking for " << activeTool->getName() << "." << endl;
			break;
		case '3':
			if (activeTool->stopTracking(currentUser))
				cout << "No longer tracking " << activeTool->getName() << "." << endl;
			else
				cout << "Unable to stop tracking for " << activeTool->getName() << "." << endl;
			break;
	}

}

void displayAccessList()
{
	std::string input;
	ClearScreen();
	cout << "[WWID : ACCESS LEVEL]" << endl;
	userTree->printUserTree();
}

void accessListMenu()
{
	std::string input;
	int selection;
	ClearScreen();
	cout << "[Access List Management]" << endl;
	displayAccessList();
	cout << "(N) - New User" << endl;
	cout << "(B) - Back to previous menu" << endl;
	cout << "Enter a WWID or selection:" << endl << ":";
	cin >> input;
	if (input == "n" || input == "N")
		newUser();
	else if (input == "b" || input == "B" || input == "q" || input == "Q")
		return;
	else
	{
		selection = atoi(input.c_str());
		if (userTree->getUser(selection) != NULL)
		{
			userMenu(userTree->getUser(selection));
		}
		else
		{
			cout << "Invalid selection." << endl;
			cin >> input;
		}
	}
}

void newUser()
{
	User *newUser = new User();
	int newWWID;
	Level accessLevel;
	ClearScreen();
	do{
		cout << "Enter WWID for new user: ";
		cin >> newWWID;
	}while (newWWID <= 0);
	newUser->setWWID(newWWID);
	newUser->setAccessLevel(selectAccessLevel());
	userTree->insertUser(newUser);
}

Level selectAccessLevel()
{
	Level accessLevel;
	int selection;
	ClearScreen();
	cout << "[Access Level Selection]" << endl;
	cout << "(0) - NONE" << endl;
	cout << "(1) - MT" << endl;
	cout << "(2) - ADMIN" << endl;
	cout << "(3) - GL" << endl;
	cout << "(4) - AM" << endl;
	do{
	cout << ":";
	cin >> selection;
	} while (selection <0 || selection > 4);
	if (selection == 0)
		accessLevel = NONE;
	else if (selection == 1)
		accessLevel = MT;
	else if (selection == 2)
		accessLevel = ADMIN;
	else if (selection == 3)
		accessLevel = GL;
	else if (selection == 4)
		accessLevel = AM;
	else
		accessLevel = NONE;
	return accessLevel;
}

void userMenu(User *toChange)
{
	ClearScreen();
	char selection;
	cout << "[Settings for WWID: " << toChange->getWWID() << "]" << endl;
	cout << "(1) - Change Access Level" << endl;
	//Not going to add a delete user function because to do so would cause crashes if they have a tool checked out, need to rework structures to handle this scenario first
	cout << "(B) - Back" << endl;
	cin >> selection;
	switch (selection)
	{
		case '1':
			toChange->setAccessLevel(selectAccessLevel());
			break;
	}
}

void lockUnlockMenu()
{
	std::string input;
	int boxes;
	Box* boxSet;
	ClearScreen();
	cout << "[------------------Select a Tool Box to Lock/Unlock----------------]" << endl;
	boxes = boxTree->listBoxes();
	cin >> input;
	int selection = atoi(input.c_str());
	if (selection > 0 && selection <= boxes)
		{
			boxSet = boxTree->getBox(selection);
			cout << "Box " << boxSet->getID() << " in bay " << boxSet->getBay() << " is currently";
			if (boxSet->getLocked())
			{
				cout << " locked." << endl;
				cout << "Enter U to unlock: ";
			}
			else
			{
				cout <<" unlocked." << endl;
				cout << "Enter L to lock: ";
			}
			cin >> input;
			if (boxSet->getLocked() && (input == "U" || input == "u"))
				handler->addOutgoing(new Message(SERVER_SENDER_CHAR,SG_UNLOCK_TYPE_CHAR, boxSet->getBoxID(),currentUser->getWWID()));
			else if (!boxSet->getLocked() && (input == "L" || input == "l"))
				handler->addOutgoing(new Message(SERVER_SENDER_CHAR,SG_LOCK_TYPE_CHAR, boxSet->getBoxID(),currentUser->getWWID()));
			else 
				cout << "Invalid selection." << endl;

		}
	else
		cout << "Invalid selection." << endl;	
}

void monitor()
{
	std::string input;

		cout <<"Beginning monitor mode. Enter any key to quit." << endl;
		monitorMessages = 1;
		cin >> input;
		monitorMessages = 0;
}
