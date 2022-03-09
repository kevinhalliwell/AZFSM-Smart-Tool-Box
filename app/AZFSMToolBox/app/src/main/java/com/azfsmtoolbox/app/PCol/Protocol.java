package com.azfsmtoolbox.app.PCol;

public final class Protocol
{

	private Protocol()
	{
		
	}
public static final int MSG_BUFFER_SIZE 			=		48;
public static final int MSG_WAIT_TIME  			=		100;
//Message position and size definitions
public static final int HEADER_POSITION 			=		0;
public static final int HEADER_SIZE				=		5;
public static final int SENDER_CODE_POSITION 		=		5;
public static final int SENDER_CODE_SIZE			=		1;
public static final int TYPE_CODE_POSITION		=		6;
public static final int TYPE_CODE_SIZE			=		1;
public static final int BOX_ID_POSITION			=		7;
public static final int BOX_ID_SIZE				=		2;
public static final int DRAWER_ID_POSITION		=		9;
public static final int DRAWER_ID_SIZE			=		2;
public static final int SENSOR_ID_POSITION		=		11;
public static final int SENSOR_ID_SIZE			=		2;
public static final int LOCKED_STATUS_POSITION	=		13;
public static final int LOCKED_STATUS_SIZE		=		1;
public static final int PRESENT_STATUS_POSITION	=		14;
public static final int PRESENT_STATUS_SIZE		=		1;
public static final int BAY_NUMBER_POSITION		=		15;
public static final int BAY_NUMBER_SIZE			=		3;
public static final int WWID_POSITION				=		18;
public static final int WWID_SIZE					=		9;
public static final int STRING_POSITION			=		27;
public static final int STRING_SIZE				=		20;
public static final int END_CHAR_POSITION			=		47;
//Character definitions
public static final int BOX_ID_ALL				=		99;
public static final int DRAWER_ID_ALL				=		99;
public static final int SENSOR_ID_ALL				=		99;
public static final int WWID_ALL					=		999999999;
public static final int NO_BOX_ID					=		0;
public static final String HEADER_STRING			=		"AzFSM";
public static final char APP_SENDER_CHAR			=		'A';
public static final char SERVER_SENDER_CHAR		=		'S';
public static final char BOX_SENDER_CHAR			=		'G';


public static final char ACK_TYPE_CHAR			=		'A';
public static final char SG_UNLOCK_TYPE_CHAR		=		'B';
public static final char SG_LOCK_TYPE_CHAR		=		'C';
public static final char AS_LOCK_TYPE_CHAR		=		'M';
public static final char AS_UNLOCK_TYPE_CHAR		=		'N';
public static final char GS_LOCK_TYPE_CHAR		=		'D';
public static final char GS_UNLOCK_TYPE_CHAR		=		'E';
public static final char GS_OPEN_TYPE_CHAR		=		'O';
public static final char GS_CLOSED_TYPE_CHAR		=		'P';
public static final char GS_REMOVED_TYPE_CHAR		=		'R';
public static final char GS_RETURNED_TYPE_CHAR	=		'S';
public static final char SA_INFO_TYPE_CHAR		=		'I';
public static final char AS_INFO_TYPE_CHAR		=		'J';
public static final char AS_REGISTER_TYPE_CHAR 	=		'K';
public static final char SA_REGISTER_TYPE_CHAR	=		'L';
public static final char AS_DEREGISTER_TYPE_CHAR	=		'Q';
public static final char INVALID_TYPE_CHAR		=		'X';
public static final int UNKNOWN_USER_WWID			=		0;
public static final char END_CHAR 				=		'\0';

}