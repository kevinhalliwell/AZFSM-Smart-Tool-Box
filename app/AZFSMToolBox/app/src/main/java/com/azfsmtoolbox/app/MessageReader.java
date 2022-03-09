//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//appFiles/MessageReader.java
package com.azfsmtoolbox.app;

import static com.azfsmtoolbox.app.PCol.Protocol.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.net.*;
import java.util.LinkedList;

public class MessageReader implements Runnable
{
	private AtomicBoolean readMessages;
	private int incomingPort = 1701;
	private DatagramSocket inc;
	private byte[] message = new byte[1500];
	private DatagramPacket pack;
	private String messageString;
	private LinkedList incomingBuffer;

	public MessageReader(LinkedList incoming)
	{
		try {
		inc = new DatagramSocket(incomingPort);
		} catch (SocketException e){};
		pack = new DatagramPacket(message,message.length);
		incomingBuffer = incoming;
		readMessages = new AtomicBoolean(true);
	}
	public void run()
	{
		while (readMessages.get())
		{
			try{
			inc.receive(pack);
			} catch (Exception e){};
			messageString = new String(message,0,MSG_BUFFER_SIZE);
			incomingBuffer.add(new ToolMessage(messageString));
		}
	}
	public void stopReading()
	{
		readMessages.set(false);
	}
	public void startReading()
	{
		readMessages.set(true);
	}

}