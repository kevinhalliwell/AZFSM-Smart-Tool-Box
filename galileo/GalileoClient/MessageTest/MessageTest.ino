#include <MessageBuffer.h>
#include <MessageProtocol.h>
#include <Messages.h>

MessageBuffer *outBuffer = new MessageBuffer();
Message *temp;

void setup() {
  // put your setup code here, to run once:
char msgBuffer[] = "AA";
char msgBuffer2[] = "BB";
char msgBuffer3[] = "CC";
char msgBuffer4[] = "OD01";
char msgBuffer5[] = "PE02";
char msgBuffer6[] = "RF0300";
char msgBuffer7[] = "SG0401";
Message* msg1 = new Message(msgBuffer);
Message* msg2 = new Message(msgBuffer2);
Message* msg3 = new Message(msgBuffer3);
Message* msg4 = new Message(msgBuffer4);
Message* msg5 = new Message(msgBuffer5);
Message* msg6 = new Message(msgBuffer6);
Message* msg7 = new Message(msgBuffer7);
outBuffer->storeMessage(msg1);
outBuffer->storeMessage(msg2);
outBuffer->storeMessage(msg3);
outBuffer->storeMessage(msg4);
outBuffer->storeMessage(msg5);
outBuffer->storeMessage(msg6);
outBuffer->storeMessage(msg7);
MessageType test1 = (MessageType)'A';
Message* amsg1 = new Message(test1,'A',02,03);
Message* amsg2 = new Message((MessageType)'O','B',02);
Message* amsg3 = new Message((MessageType)'R','C',03,04);
outBuffer->storeMessage(amsg1);
outBuffer->storeMessage(amsg2);
outBuffer->storeMessage(amsg3);
Serial.begin(9600);
}

void loop() {
  temp = outBuffer->getFirst();
  if (temp != NULL)
  {
    Serial.println("Message in queue.");
    char outBuf[20];
    temp->toChar(outBuf);
    Serial.println(outBuf);
    char type = (char) temp->getType();
    Serial.print("Message type: ");
    boolean drawerID = false;
    boolean sensorID = false;
    switch (type)
    {
      case 'A':
           Serial.println("Ack.");
           break;
      case 'B':
           Serial.println("Unlock box.");
           break;
      case 'C':
            Serial.println("Lock box.");
            break;
      case 'O':
            Serial.println("Drawer opened.");
            drawerID = true;
            break;
      case 'P':
            Serial.println("Drawer closed.");
            drawerID = true;
            break;
      case 'R':
            Serial.println("Tool removed.");
            drawerID = true;
            sensorID = true;
            break;
      case 'S':
            Serial.println("Tool replaced.");
            drawerID = true;
            sensorID = true;
            break;
    }
    Serial.print("Box ID: ");
    Serial.println(temp->getBoxID());
    if (drawerID)
    {
      Serial.print("Drawer ID: ");
      Serial.println(temp->getDrawerID());
    }
    if (sensorID)
    {
      Serial.print("Sensor ID: ");
      Serial.println(temp->getSensorID());
    }    
           
  }
  
}
