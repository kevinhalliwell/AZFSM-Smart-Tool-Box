#include <MessageBuffer.h>
#include <MessageProtocol.h>
#include <Messages.h>

#include <Ethernet.h>
#include <SPI.h>
#include <EthernetUdp.h>
#include <common.h>
#include <Drawer.h>
#include <Tool.h>
#include <ToolServer.h>

Drawer *drawer;
ToolServer *toolServer;
EthernetUDP *Udp;
byte mac[] = {  
  0x98, 0x4F, 0xEE, 0x00, 0x6D, 0x6F};
IPAddress ip(192,168,1,100);
IPAddress serverip(192,168,1,105);
const unsigned int serverPort = 1702;
const int boxID = 1;
const int red = 11;
const int green = 10;
int timer = 0;
int lockTimer;
bool countingDown = false;



void setup() {
pinMode(red, OUTPUT);     
pinMode(green, OUTPUT);
drawerSetup();
if (SERIAL_DEBUG)
	Serial.begin(9600);

Ethernet.begin(mac,ip);
Udp = new EthernetUDP();
	if(Udp->begin(PORT))
		Serial.println("Port accepted.");
toolServer = new ToolServer(Udp,serverip,serverPort,boxID);
    Serial.print("Setup: boxID: ");
    Serial.println(boxID);
drawer->setServer(toolServer);
lockBox();
}

void loop() {
        if (timer == MESSAGE_CHECK_MS)
           messageCheck();
        if (timer == MSG_SEND_MS)
            messageSend();
        if (timer == UPDATE_STATUS_MS)
	    statusUpdate();
        if (timer == COUNTDOWN_MS)
        {
          timer = 0;
          countDown();
        }
timer = timer + UPDATE_DELAY_MS;
delay(UPDATE_DELAY_MS);

}


void drawerSetup()
{
	Tool *toSetup;
	drawer = new Drawer();
	drawer->setDrawerNumber(0);
	drawer->setToolSensors(4);
	drawer->setOpenSensorPin(5);
	drawer->setOpenSensorAdjust(1000);
        drawer->setNoLightAdjust(1);	
	for (int i = 0; i < 4;i++)
	{
		toSetup = drawer->getTool(i);
		toSetup->setPin(i);
		toSetup->setSensorAdjust(1000);
		toSetup->setNoLightAdjust(6);
	}
}

void messageCheck()
{
  toolServer->checkForMessage();
}

void messageSend()
{
  toolServer->sendOut();
  toolServer->processInBuffer();
}

void statusUpdate()
{
  //Update this to work with however many drawers are set up in configuration.
  drawer->updateStatus();
  if (toolServer->lockReceived())
  {
    if (lockBox())
      toolServer->setLockReceived(false);
  }
  else if (toolServer->unlockReceived())
  {
    Serial.println("Unlocking box.");
    unlockBox();
    toolServer->setUnlockReceived(false);
  }
}

void countDown()
{
   if (countingDown)
  {
     if (!drawer->isOpen() && lockTimer > 0)
     {
      lockTimer = lockTimer - 1;
      Serial.print("lockTimer: ");
      Serial.println(lockTimer);
     }
     if (lockTimer <= 0)
         lockBox();
  }
}

boolean lockBox()
{
  Serial.println("Locking box.");
  if (!drawer->isOpen())
    {
      digitalWrite(green,LOW);
      digitalWrite(red,HIGH);
      countingDown = false;
      toolServer->notifyLocked();
      return true;
    }
    else
      return false;
    
}

void unlockBox()
{
  lockTimer = BOX_RELOCK_COUNTER_MS/1000;
  countingDown = true;
  Serial.print("Red low, Green high. Lock timer: ");
  Serial.println(lockTimer);
  digitalWrite(red,LOW);
  digitalWrite(green,HIGH);
  toolServer->notifyUnlocked();
}


