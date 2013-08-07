/*
 * Create.h
 *
 *  Created on: Sep 21, 2008
 *      Author: tekdas
 */
#ifndef CREATE_H_
#define CREATE_H_
/**
 * Create class controls the iRobot Create
 * robots according to the specifications
 * given in Create Open Interface
 */

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <SerialStream.h>

using namespace LibSerial ;

class Create{

public:
        
        static bool verbose;
  	enum Mode { OFF, PASSIVE, SAFE, FULL };
  	//
  	//@param: mode: the starting mode of create
  	//
  	Create( Mode mode = PASSIVE, const std::string &serialDevice = "/dev/ttyUSB0", int baudRate = 57600 );
  	void initialize( Mode mode );
  	~Create();

  	int command( std::vector<char> &input );
  	int setMode( Mode mode_ );
  	Mode getMode(){ return mode; };//Mode getter

  	int demoStop();
  	int demoCover();
  	int demoCoverAndDock();
  	int demoSpotCover();
  	int demoMouse();
  	int demoDriveFigureEight();
  	int demoWimp();
  	int demoHome();
  	int demoTag();
  	int demoPachelbel();
  	int demoBanjo();

  	//
  	//Drive Functions
  	//
  	//drive on a circle
  	int drive( int speed = 200, int radius = 200);
  	//drive Straight
  	int driveStraight( int speed = 200){ return drive( speed, 0x8000); };
  	//turn in place clockwise
  	int driveTurnInPlaceClockwise( int speed = 200 ){ return drive( speed, 0x0000); };
  	//turn in place counter-clockwise
  	int driveTurnInPlaceCounterclockwise( int speed = 200 ){ return drive( speed, 0x0001); };
  	//drive direct with specified left and right wheel velocity
  	int driveDirect( int rightVel = 200, int leftVel = 200 );
  	//stops create's motors
  	int driveStop(){ return driveDirect( 0, 0 ); };
	//
	//sensor reading functions:
  	//
  	//reads the sensor value specified by packetID into character vector output
	int sensors( char packetID, std::vector<char> &output );
	int queryList( std::vector<char> packetID, std::vector<char> &output );
	bool sensorsWheelDropCaster();
	bool sensorsWheelDropLeft();
	bool sensorsWheelDropRight();
	bool sensorsWheelDrop();
	bool sensorsBumpLeft();
	bool sensorsBumpRight();
	bool sensorsBump();
	bool sensorsWall();
	bool sensorsCliffLeft();
	bool sensorsCliffFrontLeft();
	bool sensorsCliffFrontRight();
	bool sensorsCliffRight();
	bool sensorsCliff(){ return sensorsCliffLeft() || sensorsCliffFrontLeft() ||
		sensorsCliffFrontRight() || sensorsCliffRight(); };
	bool sensorsVirtualWall();
	int sensorsIR();
	int sensorsDistance();
	int sensorsAngle();
	double sensorsBatteryCharge();
	int sensorsWallSignal();
	int sensorsCliffLeftSignal();
	int sensorsCliffFrontLeftSignal();
	int sensorsCliffFrontRightSignal();
	int sensorsCliffRightSignal();
	//
	//Wait commands
	//
	int waitTime( int time );
	int waitDistance( int distance );
	int waitAngle( int angle );
	int waitEvent( int event );
	//
	//High level commands
	//
	int translate( int distance, int speed = 200 );
	int translate2( int distance, int speed = 200 );
	int rotate( int angle, int speed = 200 );

private:

	int openPort( );
	int writePort( std::vector<char> &input );
	int writeReadPort( std::vector<char> &input, std::vector<char> &output, int numOfBytes );
	int demoCode( int demoID );
	char intToBytes(short int integer, int n );
	short int bytesToInt( char highByte, char lowByte );
  	bool sensorBoolReturn( char packetID );
  	char sensorCharReturn( char packetID );
  	int sensorIntReturn( char packetID );

  	SerialStream serialPort;
  	std::string serialDevice;
  	Mode mode;
  	int baudRate;
  	bool bStream;
};
#endif /*CREATE_H_*/
