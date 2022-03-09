//AZFSM Smart Toolbox Project
//Copyright 2014 - Terry Ulery and Kevin Halliwell
//common/MessageProtocol.h

#ifndef GalileoMessageProtocolH
#define GalileoMessageProtocolH


#define VERSION 0.2.1
#define MSG_BUFFER_SIZE 48
#define MSG_WAIT_TIME 100
//Message position and size definitions
#define HEADER_POSITION					0
#define HEADER_SIZE						5
#define SENDER_CODE_POSITION 			5
#define SENDER_CODE_SIZE				1
#define TYPE_CODE_POSITION				6
#define TYPE_CODE_SIZE					1
#define BOX_ID_POSITION					7
#define BOX_ID_SIZE						2
#define DRAWER_ID_POSITION				9
#define DRAWER_ID_SIZE					2
#define SENSOR_ID_POSITION				11
#define SENSOR_ID_SIZE					2
#define LOCKED_STATUS_POSITION			13
#define LOCKED_STATUS_SIZE				1
#define PRESENT_STATUS_POSITION			14
#define PRESENT_STATUS_SIZE				1
#define BAY_NUMBER_POSITION				15
#define BAY_NUMBER_SIZE					3
#define WWID_POSITION					18
#define WWID_SIZE						9
#define STRING_POSITION					27
#define STRING_SIZE						20
#define END_CHAR_POSITION				47
//Character definitions
#define BOX_ID_ALL						99
#define DRAWER_ID_ALL					99
#define SENSOR_ID_ALL					99
#define WWID_ALL						999999999
#define NO_BOX_ID						0
#define HEADER_STRING					"AzFSM"
#define APP_SENDER_CHAR					'A'
#define SERVER_SENDER_CHAR				'S'
#define BOX_SENDER_CHAR					'G'


#define ACK_TYPE_CHAR					'A'
#define SG_UNLOCK_TYPE_CHAR				'B'
#define SG_LOCK_TYPE_CHAR				'C'
#define AS_LOCK_TYPE_CHAR				'M'
#define AS_UNLOCK_TYPE_CHAR				'N'
#define GS_LOCK_TYPE_CHAR				'D'
#define GS_UNLOCK_TYPE_CHAR				'E'
#define GS_OPEN_TYPE_CHAR				'O'
#define GS_CLOSED_TYPE_CHAR				'P'
#define GS_REMOVED_TYPE_CHAR			'R'
#define GS_RETURNED_TYPE_CHAR			'S'
#define SA_INFO_TYPE_CHAR				'I'
#define AS_INFO_TYPE_CHAR				'J'
#define AS_REGISTER_TYPE_CHAR			'K'
#define SA_REGISTER_TYPE_CHAR			'L'
#define AS_DEREGISTER_TYPE_CHAR			'Q'
#define INVALID_TYPE_CHAR				'X'
#define UNKNOWN_USER_WWID				0
#define END_CHAR 						'\0'


#endif