//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//server/Menu.cpp

void Menu::mainMenu()
{
	char input;
	setHeader("Main Menu");
	setMenuOption('1',"Display Toolbox Inventory",MT,displayBoxes());
	setMenuOption('2',"Toolbox Configuration",ADMIN,boxConfigMenu());
	setMenuOption('S',"User Settings",NONE,userSettingsMenu());
	setMenuOption('Q',"Quit",NONE,exitMenu());
	getMenuInput();
}

void Menu::userSettingsMenu()
{
	setHeader("User Settings");
	setMenuOption('1',"Set WWID",NONE,setWWIDMenu());
	setMenuOption('2',"Display Access List",ADMIN,displayWWIDList());
	setMenuOption('3',"Manage Access List",ADMIN,WWIDMenu());
	setMenuOption('B',"Back to Main Menu",NONE,menuReturn());
	getMenuInput();
}

void Menu::boxConfigMenu()
{
	char input;
	setHeader("Select a Toolbox");
	boxes = boxTree->listBoxes();
	
	getInput(input);
	selection = atoi(input.c_str());
	if (selection > 0 && selection <= boxes)
	{
		boxSet = boxTree->getBox(selection);
		boxMenu(boxSet);
	}	

}