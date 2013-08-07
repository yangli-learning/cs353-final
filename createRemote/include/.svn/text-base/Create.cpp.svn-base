/*
 * Create.cpp
 *
 *  Created on: Sep 21, 2008
 *      Author: tekdas
 */

#include <iostream>
#include <string>
#include "Create.h"
#include "protocol.h"
#include "time.h"

bool Create::verbose = false;
/**
 * Constructor
 * @param mode the starting mode of Create
 * @param serialDevice the string name of serial port device, e.g. /dev/ttyUSB0
 * @param baudRate an integer representing the baudRate of the serial communication
 */
Create::Create(Mode mode, const std::string &serialDevice, int baudRate) {

	this->serialDevice = serialDevice;
	this->baudRate = baudRate;
	openPort();
	initialize(mode);
}

/*
 * Initialize the Create
 * @param mode the starting mode of Create
 */
void Create::initialize(Mode mode) {

	/*
	 * When create is activated first it starts with
	 * Off mode. Once it receives the Start command,
	 * you can enter into any one of the four operating
	 * modes
	 */

	std::vector<char> input;
	input.push_back(START);
	if ( writePort(input) == EXIT_FAILURE ){
		std::cerr<<"Create could not be started!"<<std::endl;
		exit(1);
	}

	setMode(mode);
}

/**
 * Destructor
 */
Create::~Create() {
}

/**
 * Sets the mode of create
 * @param mode_ the mode for the create
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::setMode(Mode mode_) {

	std::vector<char> input;

	switch (mode_) {

	/**
	 * When the OI is in Passive mode, you can request
	 * and receive sensor data using any of the sensors
	 * commands, but you cannot change the current
	 * command parameters for the actuators (motors,
	 * speaker, lights, low side drivers, digital outputs)
	 * to something else. To change how one of the
	 * actuators operates, you must switch from Passive
	 * mode to Full mode or Safe mode.
	 */
	case PASSIVE:
		input.push_back(PASSIVE_MODE);
		break;
	/**
	 * Safe mode gives you full control of Create, with
	 * the exception of detection of a cliff, detection
	 * of wheel drop or charger plugin
	 */
	case SAFE:
		input.push_back(SAFE_MODE);
		break;
	/**
	 * Full mode gives you complete control over Create,
	 * all of its actuators, and all of the safety-related
	 * conditions that are restricted when the OI is in
	 * Safe mode
	 */
	case FULL:
		input.push_back(FULL_MODE);
		break;
	default:
		break;

	}

	mode = mode_;
	return writePort(input);
}

/*
 * General command function which sends the given characters to port
 * @param input an array of characters where each byte represents a byte
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::command(std::vector<char> &input) {

	return writePort(input);
}
/*
 * Stop Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoStop() {

	return demoCode(DEMO_ABORT);
}

/**
 * Cover Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoCover() {

	return demoCode(DEMO_COVER);
}
/*
 * Cover and Dock Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoCoverAndDock() {

	return demoCode(DEMO_COVER_AND_DOCK);
}

/**
 * Spot Cover Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoSpotCover() {

	return demoCode(DEMO_SPOT_COVER);
}

/**
 * Mouse Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoMouse() {

	return demoCode(DEMO_MOUSE);
}

/**
 * Drive Figure Eight Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoDriveFigureEight() {

	return demoCode(DEMO_DRIVE_FIGURE_EIGHT);
}

/**
 * Wimp Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoWimp() {

	return demoCode(DEMO_WIMP);
}
/**
 * Home Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoHome() {

	return demoCode(DEMO_HOME);
}

/**
 * Tag Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoTag() {

	return demoCode(DEMO_TAG);
}

/**
 * Pachelbel Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoPachelbel() {

	return demoCode(DEMO_PACHELBEL);
}

/**
 * Banjo Demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoBanjo() {

	return demoCode(DEMO_BANJO);
}

/**
 * This command controls the Create's drive wheels.
 * @param speed an integer value which specifies the average
 * 	speed of the drive wheels in millimeters per second (mm/s)
 * 	Range: -500-500
 * @param radius an integer value which specifies the
 * 	radius in millimeters at which Create will turn. (higher radius
 * 	makes movement straight) Range: -2000-2000
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::drive(int speed, int radius) {

	std::vector<char> input;

	if (speed < VELOCITY_MIN)
		speed = VELOCITY_MIN;
	else if (speed > VELOCITY_MAX)
		speed = VELOCITY_MAX;

	if (radius < RADIUS_MIN)
		radius = RADIUS_MIN;
	else if (radius > RADIUS_MAX)
		radius = RADIUS_MAX;

	input.push_back(DRIVE);
	input.push_back(intToBytes((short int) speed, 1));
	input.push_back(intToBytes((short int) speed, 0));
	input.push_back(intToBytes((short int) radius, 1));
	input.push_back(intToBytes((short int) radius, 0));

	return writePort(input);
}

/**
 * Return the n-th least significant byte of given value
 * @param val is a given short integer value
 * @param n is the requested least significant byte
 * @return a byte which is the n-th least significant byte
 * 	of val
 */
char Create::intToBytes(short int val, int n) {
	return (val >> (8 * n)) & 255;
}

/**
 * This command lets you control the forward and backward
 * motion of Create’s drive wheels independently.
 * @params rightVel an integer value which specifies the
 * 	speed of right wheel. Range: -500-500
 * @params leftVel an integer value which specifies the
 * 	speed of left wheel. Range: -500-500
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::driveDirect(int rightVel, int leftVel) {

	std::vector<char> input;

	if (rightVel < VELOCITY_MIN)
		rightVel = VELOCITY_MIN;
	else if (rightVel > VELOCITY_MAX)
		rightVel = VELOCITY_MAX;
	if (leftVel < VELOCITY_MIN)
		leftVel = VELOCITY_MIN;
	else if (leftVel > VELOCITY_MAX)
		leftVel = VELOCITY_MAX;

	input.push_back(DRIVE_DIRECT);
	input.push_back(intToBytes((short int) rightVel, 1));
	input.push_back(intToBytes((short int) rightVel, 0));
	input.push_back(intToBytes((short int) leftVel, 1));
	input.push_back(intToBytes((short int) leftVel, 0));

	return writePort(input);
}

/**
 * This command lets you ask for a list of sensor packets.
 * The robot returns the packets in the order you specify.
 * @param packetID an array of requested packet IDs (see
 * Create OI for available packets)
 * @return output a vector of sensory data returned from Create
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::queryList(std::vector<char> packetID, std::vector<char> &output) {

	std::vector<char> input;

	input.push_back(QUERY_LIST);
	input.push_back((char) packetID.size());

	for (unsigned int i = 0; i < packetID.size(); i++) {

		input.push_back(packetID[i]);
	}

	return writeReadPort(input, output, packetID.size());
}

/**
 * Sends input comment to create and create
 * outputs the packet given by packetID
 * @param packetID an byte of requested packet ID (see
 * Create OI for available packets)
 * @return output a vector of sensory data returned from Create
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::sensors(char packetID, std::vector<char> &output) {

	std::vector<char> input;

	if (verbose)
		std::cout << "Create::sensors packetID:" << (int) packetID << std::endl;

	if (packetID < 0)
		return -1;
	else if (packetID > 42)
		return -1;

	input.push_back(SENSORS);
	input.push_back(packetID);

	switch (packetID) {
	case PACKETID_00:
		writeReadPort(input, output, 26);
		break;
	case PACKETID_01:
		writeReadPort(input, output, 10);
		break;
	case PACKETID_02:
		writeReadPort(input, output, 6);
		break;
	case PACKETID_03:
		writeReadPort(input, output, 10);
		break;
	case PACKETID_04:
		writeReadPort(input, output, 14);
		break;
	case PACKETID_05:
		writeReadPort(input, output, 12);
		break;
	case PACKETID_06:
		writeReadPort(input, output, 52);
		break;
	case PACKETID_BUMBS_AND_WHEEL_DROPS:
	case PACKETID_WALL:
	case PACKETID_CLIFF_LEFT:
	case PACKETID_CLIFF_FRONT_LEFT:
	case PACKETID_CLIFF_FRONT_RIGHT:
	case PACKETID_CLIFF_RIGHT:
	case PACKETID_VIRTUAL_WALL:
	case PACKETID_OVERCURRENTS:
	case PACKETID_15:
	case PACKETID_16:
	case PACKETID_IR:
	case PACKETID_BUTTONS:
		writeReadPort(input, output, 1);
		break;
	case PACKETID_DISTANCE:
	case PACKETID_ANGLE:
		writeReadPort(input, output, 2);
		break;
	case PACKETID_CHARGING_STATE:
		writeReadPort(input, output, 1);
		break;
	case PACKETID_VOLTAGE:
	case PACKETID_CURRENT:
		writeReadPort(input, output, 2);
		break;
	case PACKETID_BATTERY_TEMPERATURE:
		writeReadPort(input, output, 1);
		break;
	case PACKETID_BATTERY_CHARGE:
	case PACKETID_BATTERY_CAPACITY:
	case PACKETID_WALL_SIGNAL:
	case PACKETID_CLIFF_LEFT_SIGNAL:
	case PACKETID_CLIFF_FRONT_LEFT_SIGNAL:
	case PACKETID_CLIFF_FRONT_RIGHT_SIGNAL:
	case PACKETID_CLIFF_RIGHT_SIGNAL:
		writeReadPort(input, output, 2);
		break;
	case PACKETID_USER_DIGITAL_OUTPUTS:
		writeReadPort(input, output, 1);
		break;
	case PACKETID_USER_ANALOG_OUTPUTS:
		writeReadPort(input, output, 2);
		break;
	case PACKETID_CHARGING_SOURCE:
	case PACKETID_OI_MODE:
	case PACKETID_SONG_NUMBER:
	case PACKETID_SONG_PLAYING:
	case PACKETID_NUMBER_OF_STREAM:
		writeReadPort(input, output, 1);
		break;
	case PACKETID_VELOCITY:
	case PACKETID_RADIUS:
	case PACKETID_RIGHT_VELOCITY:
	case PACKETID_LEFT_VELOCITY:
		writeReadPort(input, output, 2);
		break;
	default:
		break;
	}
	return 0;

}

/**
 * Caster wheel drop sensor.
 * @return false = wheel raised, true = wheel drop
 */
bool Create::sensorsWheelDropCaster() {

	std::vector<char> output;
	sensors(PACKETID_BUMBS_AND_WHEEL_DROPS, output);
	return output[0] & 0x10;
}

/**
 * Left wheel drop sensor.
 * @return false = wheel raised, true = wheel drop
 */
bool Create::sensorsWheelDropLeft() {

	std::vector<char> output;
	sensors(PACKETID_BUMBS_AND_WHEEL_DROPS, output);
	return output[0] & 0x08;
}

/**
 * Right wheel drop sensor.
 * @return false = wheel raised, true = wheel drop
 */
bool Create::sensorsWheelDropRight() {

	std::vector<char> output;
	sensors(PACKETID_BUMBS_AND_WHEEL_DROPS, output);
	return output[0] & 0x04;
}

/**
 * Any wheel drop sensors.
 * @return false = wheel raised, true = wheel drop
 */
bool Create::sensorsWheelDrop() {

	std::vector<char> output;
	sensors(PACKETID_BUMBS_AND_WHEEL_DROPS, output);
	return output[0] & 0x0C;
}

/**
 * Left bump sensor.
 * @return false = no bump, true = bump
 */
bool Create::sensorsBumpLeft() {

	std::vector<char> output;
	sensors(PACKETID_BUMBS_AND_WHEEL_DROPS, output);
	return output[0] & 0x02;
}

/**
 * Right bump sensor.
 * @return false = no bump, true = bump
 */
bool Create::sensorsBumpRight() {

	std::vector<char> output;
	sensors(PACKETID_BUMBS_AND_WHEEL_DROPS, output);
	return output[0] & 0x01;
}

/**
 * Any bump sensors.
 * @return false = no bump, true = bump
 */
bool Create::sensorsBump() {

	std::vector<char> output;
	sensors(PACKETID_BUMBS_AND_WHEEL_DROPS, output);
	return output[0] & 0x03;
}

/**
 * wall sensor.
 * @return false = no wall, true = wall seen
 */
bool Create::sensorsWall() {

	return sensorBoolReturn(PACKETID_WALL);
}

/**
 * Left cliff sensor.
 * @return false = no cliff, true = cliff
 */
bool Create::sensorsCliffLeft() {

	return sensorBoolReturn(PACKETID_CLIFF_LEFT);
}

/**
 * Front left cliff sensor.
 * @return false = no cliff, true = cliff
 */
bool Create::sensorsCliffFrontLeft() {

	return sensorBoolReturn(PACKETID_CLIFF_FRONT_LEFT);
}

/**
 * Front right cliff sensor.
 * @return false = no cliff, true = cliff
 */
bool Create::sensorsCliffFrontRight() {

	return sensorBoolReturn(PACKETID_CLIFF_FRONT_RIGHT);
}

/**
 * Right cliff sensor.
 * @return false = no cliff, true = cliff
 */
bool Create::sensorsCliffRight() {

	return sensorBoolReturn(PACKETID_CLIFF_RIGHT);
}

/**
 * Virtual wall sensor.
 * @return false = no virtual wall, true = virtual wall detected
 */
bool Create::sensorsVirtualWall() {

	return sensorBoolReturn(PACKETID_VIRTUAL_WALL);
}

/**
 * IR sensor.
 * @return an integer value identifies the IR byte currently
 * 	being received. Range 0-255
by iRobot Create.
 */
int Create::sensorsIR() {

	return (unsigned char) sensorCharReturn(PACKETID_IR);

}
/**
 * Odometry encoder
 * @return an integer value which is the distance
 * 	that Create has traveled in millimeters since the
 * 	distance it was last requested is sent
 * 	This is the same as the sum of the distance
 * 	traveled by both wheels divided by two. Positive
 *	values indicate	travel in the forward direction;
 *	negative values indicate travel in the reverse direction
 */
int Create::sensorsDistance() {

	return sensorIntReturn(PACKETID_DISTANCE);
}

/**
 * Odometry encoder
 * @return an integer value which is the angle in degrees
 * 	that iRobot Create has turned since the angle was last
 * 	requested is sent. Counter-clockwise angles are
 * 	positive and clockwise angles are negative
 */
int Create::sensorsAngle() {

	return sensorIntReturn(PACKETID_ANGLE);
}

/**
 * Battery sensor
 * @return a double which is the current percent of charge
 * 	of Create’s battery
 */
double Create::sensorsBatteryCharge() {

	return (double) sensorIntReturn(PACKETID_BATTERY_CHARGE)
			/ (double) MAX_BATTERY_CHARGE;
}

/**
 * Wall sensor signal strength
 * @return an integer value which is the strength of
 * the wall sensor’s signal. Range: 0-4095
 */
int Create::sensorsWallSignal() {

	return sensorIntReturn(PACKETID_WALL_SIGNAL);
}

/**
 * Left cliff sensor signal strength
 * @return an integer value which is the strength of
 * the left cliff sensor’s signal. Range: 0-4095
 */
int Create::sensorsCliffLeftSignal() {

	return sensorIntReturn(PACKETID_CLIFF_LEFT_SIGNAL);
}

/**
 * Front left cliff sensor signal strength
 * @return an integer value which is the strength of
 * the front left cliff sensor’s signal. Range: 0-4095
 */
int Create::sensorsCliffFrontLeftSignal() {

	return sensorIntReturn(PACKETID_CLIFF_FRONT_LEFT_SIGNAL);
}

/**
 * Front right cliff sensor signal strength
 * @return an integer value which is the strength of
 * the front right cliff sensor’s signal. Range: 0-4095
 */
int Create::sensorsCliffFrontRightSignal() {

	return sensorIntReturn(PACKETID_CLIFF_FRONT_RIGHT_SIGNAL);
}

/**
 * Right cliff sensor signal strength
 * @return an integer value which is the strength of
 * the right cliff sensor’s signal. Range: 0-4095
 */
int Create::sensorsCliffRightSignal() {

	return sensorIntReturn(PACKETID_CLIFF_RIGHT_SIGNAL);
}

/**
 * Auxiliary function for sensor reading with boolean value
 * @param packetID is the sensor reading indicated with packet ID
 * @return true/false
 */
bool Create::sensorBoolReturn(char packetID) {

	std::vector<char> output;
	sensors(packetID, output);

	return (bool) output[0];

}

/**
 * Auxiliary function for sensor reading with char value
 * @param packetID is the sensor reading indicated with packet ID
 * @return char value
 */
char Create::sensorCharReturn(char packetID) {

	std::vector<char> output;
	sensors(packetID, output);

	return (int) output[0];

}

/**
 * Auxiliary function for sensor reading with integer value
 * @param packetID is the sensor reading indicated with packet ID
 * @return integer value
 */
int Create::sensorIntReturn(char packetID) {

	std::vector<char> output;
	sensors(packetID, output);

	return bytesToInt(output[0], output[1]);

}

/**
 * Auxiliary function for demo commands
 * @param demoID is the ID of the requested demo
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::demoCode(int demoID) {

	std::vector<char> input;

	input.push_back(DEMO);
	input.push_back(demoID);

	return writePort(input);

}

/**
 * Merges two bytes and set it to an integer
 * @param high byte of the requested integer value
 * @param low byte of the requested integer value
 * @return a short value constructed by merging two bytes
 */
short int Create::bytesToInt(char highByte, char lowByte) {

	short int ret;
	char source[2];

	source[0] = lowByte;
	source[1] = highByte;
	memcpy(&ret, &source, 2);

	return ret;
}

/**
 * This command causes Create to wait for
 * the specified time. During this time,
 * Create’s state does not change, nor
 * does it react to any inputs, serial or
 * otherwise.
 * @param time an integer value specifies time
 * 	to wait in tenths of a second with a resolution
 * 	of 15 ms. Range: 0-255
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::waitTime(int time) {

	std::vector<char> input;

	if (time < TIME_MIN)
		time = TIME_MIN;
	else if (time > TIME_MAX)
		time = TIME_MAX;

	input.push_back(WAIT_TIME);
	input.push_back((unsigned char) time);

	return writePort(input);
}

/**
 * This command causes iRobot Create to wait until
 * it has traveled the specified distance in mm.
 * When Create travels forward, the distance is
 * incremented. When Create travels backward, the
 * distance is decremented. If the wheels are
 * passively rotated in either direction, the
 * distance is incremented. Until Create travels
 * the specified distance, its state does not
 * change, nor does it react to any inputs,
 * serial or otherwise.
 * @param distance an integer specifies the distance
 * 	Range: -32767 -32768
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::waitDistance(int distance) {

	std::vector<char> input;

	if (distance < DISTANCE_MIN)
		distance = DISTANCE_MIN;
	else if (distance > DISTANCE_MAX)
		distance = DISTANCE_MAX;

	input.push_back(WAIT_DISTANCE);
	input.push_back(intToBytes((short int) distance, 1));
	input.push_back(intToBytes((short int) distance, 0));

	return writePort(input);
}

/**
 * This command causes Create to wait until
 * it has rotated through specified angle in
 * degrees. When Create turns counterclockwise,
 * the angle is incremented. When Create turns
 * clockwise, the angle is decremented. Until
 * Create turns through the specified angle,
 * its state does not change, nor does it
 * react to any inputs, serial or otherwise.
 * @param angle an integer specifies the angle
 * 	Range: -32767 -32768
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::waitAngle(int angle) {

	std::vector<char> input;

	if (angle < ANGLE_MIN)
		angle = ANGLE_MIN;
	else if (angle > ANGLE_MAX)
		angle = ANGLE_MAX;

	input.push_back(WAIT_ANGLE);
	input.push_back((short int) intToBytes(angle, 1));
	input.push_back((short int) intToBytes(angle, 0));

	return writePort(input);
}

/**
 * This command causes Create to wait until it detects
 * the specified event. Until the specified event is
 * detected, Create’s state does not change, nor does
 * it react to any inputs, serial or otherwise.
 * @param event an integer specifies the even id
 * 	see Create OI for event IDs
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::waitEvent(int event) {

	std::vector<char> input;

	if (event < EVENT_WHEEL_DROP)
		event = EVENT_NONE;
	else if (event > EVENT_OI_MODE && event < EVENT_OI_MODE_NOT)
		event = EVENT_NONE;
	else if (event > EVENT_WHEEL_DROP_NOT)
		event = EVENT_NONE;

	input.push_back(WAIT_EVENT);
	input.push_back((unsigned char) event);

	return writePort(input);
}

/**
 * A high level function which rotates Create for
 * a given distance with given speed. The signs of
 * parameters should be same
 * @param distance an integer value in mm.
 * 	Range: -32768 – 32767
 * @param speed an integer value. Range -500-500
 */
int Create::translate(int distance, int speed) {

	if (distance*speed < 0) return EXIT_FAILURE; //sign test

	std::vector<char> input;

	if (speed < VELOCITY_MIN)
		speed = VELOCITY_MIN;
	else if (speed > VELOCITY_MAX)
		speed = VELOCITY_MAX;

	input.push_back(DRIVE_DIRECT);
	input.push_back(intToBytes((short int) speed, 1));
	input.push_back(intToBytes((short int) speed, 0));
	input.push_back(intToBytes((short int) speed, 1));
	input.push_back(intToBytes((short int) speed, 0));

	if (distance < DISTANCE_MIN)
		distance = DISTANCE_MIN;
	else if (distance > DISTANCE_MAX)
		distance = DISTANCE_MAX;

	input.push_back(WAIT_DISTANCE);
	input.push_back(intToBytes((short int) distance, 1));
	input.push_back(intToBytes((short int) distance, 0));

	input.push_back(DRIVE_DIRECT);
	input.push_back(0);
	input.push_back(0);
	input.push_back(0);
	input.push_back(0);

	return writePort(input);
}

int Create::translate2(int distance, int speed) {

	if (distance*speed < 0) return EXIT_FAILURE; //sign test

	bool bump = false;
	int currDistance = 0;
	sensorsDistance();
	driveDirect(speed, speed);

	int sign = distance<0?-1:1;

	while(sign*currDistance < sign*distance){
		currDistance += sensorsDistance();
		std::cout<<"currDistance: "<<currDistance<<std::endl;
		if(sensorsBump()){
			bump = true;
			break;
		}
	}
	driveStop();
	if (bump){
		translate(-currDistance, -speed);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

/**
 * A high level function which rotates Create for
 * a given angle and with given speed. The signs of
 * parameters should be same
 * @param angle an integer value in degrees.
 * 	Range: -32768 – 32767
 * @param speed an integer value. Range -500-500
 */
int Create::rotate(int angle, int speed) {

	if (angle*speed < 0) return EXIT_FAILURE; //sign test
	std::vector<char> input;

	if (speed < VELOCITY_MIN)
		speed = VELOCITY_MIN;
	else if (speed > VELOCITY_MAX)
		speed = VELOCITY_MAX;

	input.push_back(DRIVE_DIRECT);
	input.push_back(intToBytes((short int) speed, 1));
	input.push_back(intToBytes((short int) speed, 0));
	input.push_back(intToBytes((short int) -speed, 1));
	input.push_back(intToBytes((short int) -speed, 0));

	if (angle < ANGLE_MIN)
		angle = ANGLE_MIN;
	else if (angle > ANGLE_MAX)
		angle = ANGLE_MAX;

	input.push_back(WAIT_ANGLE);
	input.push_back(intToBytes((short int) angle, 1));
	input.push_back(intToBytes((short int) angle, 0));

	input.push_back(DRIVE_DIRECT);
	input.push_back(0);
	input.push_back(0);
	input.push_back(0);
	input.push_back(0);

	return writePort(input);
}

/**
 * Opens a serial port with given serial device and baud rate
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::openPort( ) {
	//
	// Open the serial port.
	//
	serialPort.Open(serialDevice.c_str());
	if (!serialPort.good()) {
		std::cerr << "Error: Could not open serial port " << serialDevice.c_str()
				<< std::endl;
		exit(1);
	}
	//
	// Set the baud rate of the serial port.
	//
	switch (baudRate) {
	case 300:
		serialPort.SetBaudRate(SerialStreamBuf::BAUD_300);
		break;
	case 600:
		serialPort.SetBaudRate(SerialStreamBuf::BAUD_600);
		break;
	case 1200:
		serialPort.SetBaudRate(SerialStreamBuf::BAUD_1200);
		break;
	case 2400:
		serialPort.SetBaudRate(SerialStreamBuf::BAUD_2400);
		break;
	case 4800:
		serialPort.SetBaudRate(SerialStreamBuf::BAUD_4800);
		break;
	case 9600:
		serialPort.SetBaudRate(SerialStreamBuf::BAUD_9600);
		break;
	case 19200:
		serialPort.SetBaudRate(SerialStreamBuf::BAUD_19200);
		break;
	case 38400:
		serialPort.SetBaudRate(SerialStreamBuf::BAUD_38400);
		break;
	case 57600:
		serialPort.SetBaudRate(SerialStreamBuf::BAUD_57600);
		break;
	case 115200:
		serialPort.SetBaudRate(SerialStreamBuf::BAUD_115200);
		break;
	default:
		std::cerr << "Error: The baud rate is not valid." << std::endl;
		exit(1);
	}

	if (!serialPort.good()) {
		std::cerr << "Error: Could not set the baud rate." << std::endl;
		exit(1);
	}
	//
	// Set the number of data bits.
	//
	serialPort.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
	if (!serialPort.good()) {
		std::cerr << "Error: Could not set the character size." << std::endl;
		exit(1);
	}
	//
	// Disable parity.
	//
	serialPort.SetParity(SerialStreamBuf::PARITY_NONE);
	if (!serialPort.good()) {
		std::cerr << "Error: Could not disable the parity." << std::endl;
		exit(1);
	}
	//
	// Set the number of stop bits.
	//
	serialPort.SetNumOfStopBits(1);
	if (!serialPort.good()) {
		std::cerr << "Error: Could not set the number of stop bits."
				<< std::endl;
		exit(1);
	}
	//
	// Turn on hardware flow control.
	//
	serialPort.SetFlowControl(SerialStreamBuf::FLOW_CONTROL_NONE);
	if (!serialPort.good()) {
		std::cerr << "Error: Could not use hardware flow control." << std::endl;
		exit(1);
	}
	return EXIT_SUCCESS;
}

/**
 * Writes an array of characters to serial port
 * @param input an array of input characters
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */

int Create::writePort(std::vector<char> &input) {

	//openPort();
	//
	// Write the character array to serial port
	//
	if (verbose)
		std::cerr << "Writing command to serial port." << std::endl;
	for (unsigned int i = 0; i < input.size(); i++) {
		char next_byte = input[i];
		if (verbose)
			std::cerr << std::hex << (int) next_byte << " ";
		serialPort.write(&next_byte, 1);

	}

	if (verbose)
		std::cerr << std::endl;
	if (verbose)
		std::cerr << "Done." << std::endl;
	serialPort.flush();
	//serialPort.Close();
	return EXIT_SUCCESS;
}

/**
 * Writes command (requested packetID command) and reads an array of
 * characters from serial port
 * @param input an array of characters as command
 * @param numOfBytes an integer value which represents the number of bytes
 * 	read from serial port
 * @return output an array of output characters
 * @return EXIT_FAILURE or EXIT_SUCCESS
 */
int Create::writeReadPort(std::vector<char> &input, std::vector<char> &output,
		int numOfBytes) {

	//openPort();
	//
	// Write the character array to serial port
	//
	if (verbose)
		std::cerr << "Writing command to serial port." << std::endl;
	for (unsigned int i = 0; i < input.size(); i++) {
		char next_byte = input[i];
		if (verbose)
			std::cerr << std::hex << (int) next_byte << " ";
		serialPort.write(&next_byte, 1);

	}
	if (verbose)
		std::cerr << std::endl;
	if (verbose)
		std::cerr << "Done." << std::endl;

	//
	// Keep reading data from serial port and print it to the screen.
	//
	if (verbose)
		std::cerr << "Reading command from serial port." << std::endl;
	for (int i = 0; i < numOfBytes; i++) {
		char next_byte;
		serialPort.get(next_byte);
		output.push_back(next_byte);
		if (verbose)
			std::cerr << std::hex << (int) next_byte << " ";
	}
	if (verbose)
		std::cerr << std::endl;
	if (verbose)
		std::cerr << "Done." << std::endl;
    serialPort.flush();
	//serialPort.Close();
	return EXIT_SUCCESS;
}
