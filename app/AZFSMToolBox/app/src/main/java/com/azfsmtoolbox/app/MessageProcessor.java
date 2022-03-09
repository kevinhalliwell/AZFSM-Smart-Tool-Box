//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//appFiles/MessageProcessor.java
package com.azfsmtoolbox.app;

import android.content.Context;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.util.Log;


import static com.azfsmtoolbox.app.PCol.Protocol.*;

import java.math.BigInteger;
import java.nio.ByteOrder;
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
	private ToolMessage toProcess;
	private int msgLength;
	//need passed in
	private Integer appWWID;
	private AtomicBoolean appRegistered;
    public String permissions;

	public MessageProcessor(LinkedList outBuf, LinkedList inBuf,AtomicBoolean registered)
	{
		try{
		serverIP = InetAddress.getByName("192.168.1.105");
		out = new DatagramSocket();
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
				toProcess = (ToolMessage) outgoingBuffer.remove();
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
				toProcess = (ToolMessage) incomingBuffer.remove();
				switch (toProcess.getMesType())
				{
					case SA_REGISTER_TYPE_CHAR:
						if (appWWID.equals(toProcess.getWWID())) {
                            permissions = toProcess.getStringData();
                            appRegistered.set(true);
                        }
						break;

				}
			}
		}
	}
	public void registerWWID(Integer appWW)
	{
		appWWID = appWW;
		appRegistered.set(false);
		outgoingBuffer.add(new ToolMessage(AS_REGISTER_TYPE_CHAR,appWW,wifiIpAddress(AZFSMToolBox.getContext())));
	}

    public void unlockBox()
    {
        if(appRegistered.get())
        {
            outgoingBuffer.add(new ToolMessage(AS_UNLOCK_TYPE_CHAR,1,appWWID));
        }
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
    protected String wifiIpAddress(Context context) {
        WifiManager wifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
        int ipAddress = wifiManager.getConnectionInfo().getIpAddress();

        // Convert little-endian to big-endianif needed
        if (ByteOrder.nativeOrder().equals(ByteOrder.LITTLE_ENDIAN)) {
            ipAddress = Integer.reverseBytes(ipAddress);
        }

        byte[] ipByteArray = BigInteger.valueOf(ipAddress).toByteArray();

        String ipAddressString;
        try {
            ipAddressString = InetAddress.getByAddress(ipByteArray).getHostAddress();
        } catch (UnknownHostException ex) {
            Log.e("WIFIIP", "Unable to get host address.");
            ipAddressString = "192.168.1.104";
        }

        return ipAddressString;
    }
}