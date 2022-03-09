package com.azfsmtoolbox.app;

//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//appFiles/ToolMessage.java

import static com.azfsmtoolbox.app.PCol.Protocol.*;
import java.text.NumberFormat;


public class ToolMessage
{
	private char senderType;
	private char mesType;
	private int boxID;
	private int drawerID;
	private int sensorID;
	private boolean locked;
	private boolean present; 
	private int bayNumber;
	private int aWWID;
	private String stringData;

	// Ack message constructor
	public ToolMessage(char inMesType, String inStringData)
	{
		senderType = APP_SENDER_CHAR;
		mesType = inMesType;
		stringData = inStringData;
		boxID = 0;
		drawerID = 0;
		sensorID = 0;
		locked = false;
		present = false;
		bayNumber = 0;
		aWWID = 0;

	}
	//lock/unlock request constructor
	public ToolMessage(char inMesType, int inBoxID, int inWWID)
	{
		senderType = APP_SENDER_CHAR;
		mesType = inMesType;
		boxID = inBoxID;
		aWWID = inWWID;
		drawerID = 0;
		sensorID = 0;
		locked = false;
		present = false;
		bayNumber = 0;
		stringData = "\0";

	}
	//info request constructor
	public ToolMessage(char inMesType, int inBoxID, int inDrawerID, int inSensorID, int inWWID)
	{
		senderType = APP_SENDER_CHAR;
		mesType = inMesType;
		boxID = inBoxID;
		drawerID = inDrawerID;
		sensorID = inSensorID;
		aWWID = inWWID;
		locked = false;
		present = false;
		bayNumber = 0;
		stringData = "\0";

	}
	//app register 
	public ToolMessage(char inMesType, int inWWID, String inStringData)
	{
		senderType = APP_SENDER_CHAR;
		aWWID = inWWID;
        String filler = "\0";
        if (inStringData.length() < STRING_SIZE)
        {
            for (int i = 0; i < STRING_SIZE - inStringData.length();i++)
            {
                filler = filler + filler;
            }
        }
            inStringData = inStringData + filler;
		stringData = inStringData;
		mesType = inMesType;
		boxID = 0;
		drawerID = 0;
		sensorID = 0;
		locked = false;
		present = false;
		bayNumber = 0;
	}
	//Constructing a message from incoming string
	public ToolMessage (String inData)
	{
		String headerTest = inData.substring(HEADER_POSITION,HEADER_SIZE);
		if (headerTest.equals(HEADER_STRING))
		{
			senderType = inData.charAt(SENDER_CODE_POSITION);
			mesType = inData.charAt(TYPE_CODE_POSITION);
			boxID = 0;
			for (int i = BOX_ID_SIZE-1; i >= 0; i--)
			{
				boxID = boxID + (int) Math.pow(10,i) * Character.getNumericValue(inData.charAt(BOX_ID_POSITION + (BOX_ID_SIZE-1-i)));
			}
			drawerID = 0;
			for (int i = DRAWER_ID_SIZE-1; i >= 0; i--)
			{
				drawerID = drawerID + (int) Math.pow(10,i) * Character.getNumericValue(inData.charAt(DRAWER_ID_POSITION + (DRAWER_ID_SIZE-1-i)));
			}
			sensorID = 0;
			for (int i = SENSOR_ID_SIZE-1; i>= 0; i--)
			{
				sensorID = sensorID + (int) Math.pow(10,i) * Character.getNumericValue(inData.charAt(SENSOR_ID_POSITION + (SENSOR_ID_SIZE-1-i)));
			}
			aWWID = 0;
			for (int i = WWID_SIZE-1; i>= 0; i--)
			{
				aWWID = aWWID + (int) Math.pow(10,i) * Character.getNumericValue(inData.charAt(WWID_POSITION + (WWID_SIZE-1-i)));
			}
			bayNumber = 0;
			for (int i = BAY_NUMBER_SIZE-1; i>= 0; i--)
			{
				bayNumber = bayNumber + (int) Math.pow(10,i) * Character.getNumericValue(inData.charAt(BAY_NUMBER_POSITION + (BAY_NUMBER_SIZE-1-i)));
			}

			if (inData.charAt(LOCKED_STATUS_POSITION) == '1')
				locked = true;
			else
				locked = false;
			if (inData.charAt(PRESENT_STATUS_POSITION) == '1')
				present = true;
			else
				present = false;
			int stringLength = inData.length() - STRING_POSITION;
			if (stringLength > 0)
				stringData = inData.substring(STRING_POSITION);
		}
		else
		{
			senderType = INVALID_TYPE_CHAR;
			mesType = INVALID_TYPE_CHAR;
			boxID = 0;
			drawerID = 0;
			sensorID = 0;
			aWWID = 0;
			bayNumber = 0;
			locked = false;
			present = false;
			stringData = "\0";
		}
	}
	public String toString()
	{
		String newMessage = HEADER_STRING;
		newMessage = newMessage + senderType;
		newMessage = newMessage + mesType;
		NumberFormat format=NumberFormat.getInstance();
		format.setMaximumIntegerDigits(BOX_ID_SIZE);
		format.setMinimumIntegerDigits(BOX_ID_SIZE);
		newMessage = newMessage + format.format(boxID);
		format.setMaximumIntegerDigits(DRAWER_ID_SIZE);
		format.setMinimumIntegerDigits(DRAWER_ID_SIZE);
		newMessage = newMessage + format.format(drawerID);
		format.setMaximumIntegerDigits(SENSOR_ID_SIZE);
		format.setMinimumIntegerDigits(SENSOR_ID_SIZE);
		newMessage = newMessage + format.format(sensorID);
		if (locked)
			newMessage = newMessage + 1;
		else
			newMessage = newMessage + 0;
		if (present)
			newMessage = newMessage + 1;
		else
			newMessage = newMessage + 0;
		format.setMaximumIntegerDigits(BAY_NUMBER_SIZE);
		format.setMinimumIntegerDigits(BAY_NUMBER_SIZE);
		newMessage =newMessage + format.format(bayNumber);
		format.setMaximumIntegerDigits(WWID_SIZE);
		format.setMinimumIntegerDigits(WWID_SIZE);
		newMessage = newMessage + format.format(aWWID).replaceAll(",", "");
		if (stringData.length() > STRING_SIZE)
			newMessage = newMessage + stringData;
		else
			newMessage = newMessage + stringData;
		return newMessage;

	}
	public char getSenderType()
	{
		return senderType;
	}
	public char getMesType()
	{
		return mesType;
	}
	public int getBoxID()
	{
		return boxID;
	}
	public int getDrawerID()
	{
		return drawerID;
	}
	public int sensorID()
	{
		return sensorID;
	}
	public boolean getLocked()
	{
		return locked;
	}
	public boolean getPresent()
	{
		return present;
	}
	public int getBayNumber()
	{
		return bayNumber;
	}
	public int getWWID()
	{
		return aWWID;
	}
	public String getStringData()
	{
		return stringData;
	}
}