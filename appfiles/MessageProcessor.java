//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//appFiles/MessageProcessor.java

import static PCol.Protocol.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.net.*;
import java.util.LinkedList;

public class MessageProcessor implements Runnable
{
	private AtomicBoolean processMessages;
	private int serverPort = 1702;
	private InetAddress serverIP;
	private InetAddress localIP;
	private LinkedList outgoingBuffer;
	private LinkedList incomingBuffer;
	private DatagramPacket pack;
	private DatagramSocket out;
	private byte[] message;
	private String msgString;
	private Message toProcess;
	private int msgLength;
	//need passed in
	private Integer appWWID;
	private AtomicBoolean appRegistered;

	public MessageProcessor(LinkedList outBuf, LinkedList inBuf,AtomicBoolean registered)
	{
		try{
		serverIP = InetAddress.getByName("192.168.1.101");
		out = new DatagramSocket();
		localIP = out.getLocalAddress();
		}catch(Exception e){};
		outgoingBuffer = outBuf;
		incomingBuffer = inBuf;
		processMessages = new AtomicBoolean(true);
		appRegistered = registered;
	}
	public void run()
	{
		while (processMessages.get())
		{
			if (outgoingBuffer.size() > 0)
			{
				toProcess = (Message) outgoingBuffer.getFirst();
				msgString = toProcess.toString();
				msgLength = msgString.length();
				message = msgString.getBytes();
				pack = new DatagramPacket(message,msgLength,serverIP,serverPort);
				try{
				out.send(pack);
				} catch(Exception e){};
			}
			if (incomingBuffer.size() > 0)
			{
				toProcess = (Message) incomingBuffer.getFirst();
				switch (toProcess.getSenderType())
				{
					case SA_REGISTER_TYPE_CHAR:
						if (appWWID.equals(toProcess.getWWID()))
							appRegistered.set(true);
						break;

				}
			}
		}
	}
	public void registerWWID(Integer appWW)
	{
		appWWID = appWW;
		appRegistered.set(false);
		outgoingBuffer.add(new Message(AS_REGISTER_TYPE_CHAR,appWW,localIP.toString()));
	}
	public void stopProcessing()
	{
		processMessages.set(false);
	}
	public void startProcessing()
	{
		processMessages.set(true);
	}
	public String getIPString()
	{
		return localIP.toString();
	}
}