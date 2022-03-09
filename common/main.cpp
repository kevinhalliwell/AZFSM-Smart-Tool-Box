#include "Messages.h"
#include <iostream>


using namespace std;

int main()
{
	Message *newMes1 = new Message('S','A',"ACKSTRING");
	Message *newMes2 = new Message('A','B',1,11412302);
	Message *newMes3 = new Message('G','O',1,3,true,11412302);
	Message *newMes4 = new Message('G','R',1,2,1,true,11412302);
	Message *newMes5 = new Message('I','S',1,99,99,true,true,202,11412302,"Lista 1");
	cout << "Messages created." << endl;

	char mesBuffer[48];
	newMes1->toChar(mesBuffer);
	cout << mesBuffer << endl;
	Message *newMex1 = new Message(mesBuffer);
	newMex1->toChar(mesBuffer);
	cout << mesBuffer << endl;
	newMes2->toChar(mesBuffer);
	cout << mesBuffer << endl;
	Message *newMex2 = new Message(mesBuffer);
	newMex2->toChar(mesBuffer);
	cout << mesBuffer << endl;
	newMes3->toChar(mesBuffer);
	cout << mesBuffer << endl;
	Message *newMex3 = new Message(mesBuffer);
	newMex3->toChar(mesBuffer);
	cout << mesBuffer << endl;
	newMes4->toChar(mesBuffer);
	cout << mesBuffer << endl;
	Message *newMex4 = new Message(mesBuffer);
	newMex4->toChar(mesBuffer);
	cout << mesBuffer << endl;
	newMes5->toChar(mesBuffer);
	cout << mesBuffer << endl;
	Message *newMex5 = new Message(mesBuffer);
	newMex5->toChar(mesBuffer);
	cout << mesBuffer << endl;


	return 0;
}