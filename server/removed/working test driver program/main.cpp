//test Driver main.cpp

#include "UDPSender.h"
#include "MessageBuffer.h"
#include <string>
#include <iostream>

using namespace std;


//Global Constants
const std::string IPAddress = "192.168.1.101";
const int incPort = 1702;
const std::string boxIP = "192.168.1.100";
const int outPort = 1701;


int main()
{
	MessageBuffer *inBuf = new MessageBuffer();
	Message *curMsg;
	int bytes;
	cout << "Attempting to create new server." << endl;
	UDPServer *newServer = new UDPServer(IPAddress,incPort);
	cout << "Attempting to create new sender." << endl;
	UDPSender *newSender = new UDPSender(boxIP,outPort);
	char message[] = "A";
	cout << "Attempting to send \"Ack\" message to Galileo."<<endl;
	newSender->send(message,1);
	cout << "Attempting to retrieve message from Galileo."<<endl;
	do{
		bytes = newServer->receiveMessage(message,25,5000);
		if (bytes >0)
			{
				cout << "Message received."<< endl;
				inBuf->storeMessage(new Message(message));
				curMsg = inBuf->getFirst();
				cout <<"Decoding message from Toolbox ID: " << curMsg->getBoxID() << endl;
				cout <<"Message Type: ";
				switch (curMsg->getType())
				{
					case MessageType::DRAWEROPENED:
					cout << "Drawer opened." << endl;
					cout << "Drawer number: " << curMsg->getDrawerID() << endl;
					break;
					case MessageType::DRAWERCLOSED:
					cout << "Drawer closed." << endl;
					cout << "Drawer number: " << curMsg->getDrawerID() << endl;
					break;
					case MessageType::TOOLREMOVED:
					cout << "Tool removed." << endl;
					cout << "Drawer number: " << curMsg->getDrawerID() << endl;
					cout << "Sensor number: " << curMsg->getSensorID() << endl;
					break;
					case MessageType::TOOLRETURNED:
					cout << "Tool returned." << endl;
					cout << "Drawer number: " << curMsg->getDrawerID() << endl;
					cout << "Sensor number: " << curMsg->getSensorID() << endl;
					break;
					case MessageType::ACK:
					cout << "Ack." << endl;
					break;
				}

			}
	}while(true);
	return 0;
}