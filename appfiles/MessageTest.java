//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//appFiles/MessageTest.java

import static PCol.Protocol.*;

public class MessageTest
{
	public static void main(String[] args)
	{
		Message msg1 = new Message(ACK_TYPE_CHAR,"Acknowledged.");
		Message msg1x = new Message(msg1.toString());
		Message msg2 = new Message(AS_UNLOCK_TYPE_CHAR,1,11412302);
		Message msg2x = new Message(msg2.toString());
		Message msg3 = new Message(AS_INFO_TYPE_CHAR,99,98,97,11412302);
		Message msg3x = new Message(msg3.toString());
		Message msg4 = new Message(AS_REGISTER_TYPE_CHAR,11412302,"192.168.1.102");
		Message msg4x = new Message(msg4.toString());
		System.out.println("Message 1:\t\t" + msg1.toString());
		System.out.println("Message 1x:\t\t" + msg1x.toString());
		System.out.println("Message 2:\t\t" + msg2.toString());
		System.out.println("Message 2x:\t\t" + msg2x.toString());
		System.out.println("Message 3:\t\t" + msg3.toString());
		System.out.println("Message 3x:\t\t" + msg3x.toString());
		System.out.println("Message 4:\t\t" + msg4.toString());
		System.out.println("Message 4x:\t\t" + msg4x.toString());
		
	}
}

