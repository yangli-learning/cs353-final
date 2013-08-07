/*
 * protocol.h
 *
 *  Created on: Sep 21, 2008
 *      Author: tekdas
 *  iRobot Create serial port interface protocol
 */

#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#define VELOCITY_MAX 500
#define VELOCITY_MIN -500
#define RADIUS_MAX 2000
#define RADIUS_MIN -2000
#define ANGLE_MAX 32767
#define ANGLE_MIN -32767
#define DISTANCE_MAX 32767
#define DISTANCE_MIN -32767
#define TIME_MAX 255
#define TIME_MIN 0
//Start command
//[128]
#define START 128
//Baud command
//[129][Baud Code]
#define BAUD 129
//#define BAUD300 0
//#define BAUD600 1
//#define BAUD1200 2
//#define BAUD2400 3
//#define BAUD4800 4
//#define BAUD9600 5
//#define BAUD14400 6
//#define BAUD19200 7
//#define BAUD28800 8
//#define BAUD38400 9
//#define BAUD57600 10
//#define BAUD115200 11
//Mode commands
//[Mode]
#define SAFE_MODE 131
#define FULL_MODE 132
#define PASSIVE_MODE 128
//Demo commands
//[136][Demo Code]
#define DEMO 136
#define DEMO_ABORT 255
#define DEMO_COVER 0
#define DEMO_COVER_AND_DOCK 1
#define DEMO_SPOT_COVER 2
#define DEMO_MOUSE 3
#define DEMO_DRIVE_FIGURE_EIGHT 4
#define DEMO_WIMP 5
#define DEMO_HOME 6
#define DEMO_TAG 7
#define DEMO_PACHELBEL 8
#define DEMO_BANJO 9
//Actuator commands
//Drive
//[137][Velocity High Byte][Velocity Low Byte]
//[Radius High Byte][Radius High Byte]
#define DRIVE 137
//Special Cases
#define STRAIGHT1 128
#define STRAIGHT2 0
#define CLOCKWISE1 255
#define CLOCKWISE2 255
#define COUNTER_CLOCKWISE1 0
#define COUNTER_CLOCKWISE2 1
//Drive Direct
//[145][Right Velocity High Byte][Right Velocity Low Byte]
//[Left Velocity High Byte][Left Velocity High Byte]
#define DRIVE_DIRECT 145
//LEDs
//[139][LED Bits][Power Color][Power Intensity]
#define LED 139
#define ADVANCE 8
#define PLAY 2
#define GREEN 0
#define RED 255
#define ORANGE 127
//Input commands
#define SENSORS 142
#define QUERY_LIST 149
#define PACKETID_00 0 //26 bytes 7 - 26
#define PACKETID_01 1 //10 bytes 7 - 16
#define PACKETID_02 2 //6 bytes 17 - 20
#define PACKETID_03 3 //10 bytes 21 - 26
#define PACKETID_04 4 //14 bytes 27 - 34
#define PACKETID_05 5 //12 bytes 35 - 42
#define PACKETID_06 6 //52 bytes 7 - 42
#define PACKETID_BUMBS_AND_WHEEL_DROPS 7 //Bumps and Wheel Drops
#define PACKETID_WALL 8 //Wall
#define PACKETID_CLIFF_LEFT 9 //Cliff Left
#define PACKETID_CLIFF_FRONT_LEFT 10 //Cliff Front Left
#define PACKETID_CLIFF_FRONT_RIGHT 11 //Cliff Front Right
#define PACKETID_CLIFF_RIGHT 12 //Cliff Right
#define PACKETID_VIRTUAL_WALL 13 //Virtual Wall
#define PACKETID_OVERCURRENTS 14 //Overcurrents
#define PACKETID_15 15 //Unused
#define PACKETID_16 16 //Unused
#define PACKETID_IR 17 //IR Byte
#define PACKETID_BUTTONS 18 //Buttons
#define PACKETID_DISTANCE 19 //Distance
#define PACKETID_ANGLE 20 //Angle
#define PACKETID_CHARGING_STATE 21 //Charging State
#define PACKETID_VOLTAGE 22 //Voltage
#define PACKETID_CURRENT 23 //Current
#define PACKETID_BATTERY_TEMPERATURE 24 //Battery Temperature
#define PACKETID_BATTERY_CHARGE 25 //Battery Charge
#define MAX_BATTERY_CHARGE 2700
#define PACKETID_BATTERY_CAPACITY 26 //Battery Capacity
#define PACKETID_WALL_SIGNAL 27 //Wall Signal
#define PACKETID_CLIFF_LEFT_SIGNAL 28 //Cliff Left Signal
#define PACKETID_CLIFF_FRONT_LEFT_SIGNAL 29 //Cliff Front Left Signal
#define PACKETID_CLIFF_FRONT_RIGHT_SIGNAL 30 //Cliff Front Right Signal
#define PACKETID_CLIFF_RIGHT_SIGNAL 31 //Cliff Right Signal
#define PACKETID_USER_DIGITAL_OUTPUTS 32 //User Digital Inputs
#define PACKETID_USER_ANALOG_OUTPUTS 33 //User Analog Input
#define PACKETID_CHARGING_SOURCE 34 //Charging Sources
#define PACKETID_OI_MODE 35 //OI Mode
#define PACKETID_SONG_NUMBER 36 //Song Number
#define PACKETID_SONG_PLAYING 37 //Song Playing
#define PACKETID_NUMBER_OF_STREAM 38 //Number of Stream
#define PACKETID_VELOCITY 39 //Velocity
#define PACKETID_RADIUS 40 //Radius
#define PACKETID_RIGHT_VELOCITY 41 //Right Velocity
#define PACKETID_LEFT_VELOCITY 42 //Left Velocity
//Wait commands
#define WAIT_TIME 155
#define WAIT_DISTANCE 156
#define WAIT_ANGLE 157
#define WAIT_EVENT 158
//Event types
#define EVENT_WHEEL_DROP 1
#define EVENT_WHEEL_DROP_NOT 255
#define EVENT_FRONT_WHEEL_DROP 2
#define EVENT_FRONT_WHEEL_DROP_NOT 254
#define EVENT_LEFT_WHEEL_DROP 3
#define EVENT_LEFT_WHEEL_DROP_NOT 253
#define EVENT_RIGHT_WHEEL_DROP 4
#define EVENT_RIGHT_WHEEL_DROP_NOT 252
#define EVENT_BUMP 5
#define EVENT_BUMP_NOT 251
#define EVENT_LEFT_BUMP 6
#define EVENT_LEFT_BUMP_NOT 250
#define EVENT_RIGHT_BUMP 7
#define EVENT_RIGHT_BUMP_NOT 249
#define	EVENT_VIRTUAL_WALL 8
#define	EVENT_VIRTUAL_WALL_NOT 248
#define EVENT_WALL 9
#define EVENT_WALL_NOT 247
#define EVENT_CLIFF 10
#define EVENT_CLIFF_NOT 246
#define EVENT_LEFT_CLIFF 11
#define EVENT_LEFT_CLIFF_NOT 245
#define EVENT_FRONT_LEFT_CLIFF 12
#define EVENT_FRONT_LEFT_CLIFF_NOT 244
#define EVENT_FRONT_RIGHT_CLIFF 13
#define EVENT_FRONT_RIGHT_CLIFF_NOT 243
#define EVENT_RIGHT_CLIFF 14
#define EVENT_RIGHT_CLIFF_NOT 242
#define EVENT_HOME_BASE 15
#define EVENT_HOME_BASE_NOT 241
#define EVENT_ADVANCE_BUTTON 16
#define EVENT_ADVANCE_BUTTON_NOT 240
#define EVENT_PLAY_BUTTON 17
#define EVENT_PLAY_BUTTON_NOT 239
#define EVENT_DIGITAL_INPUT_0 18
#define EVENT_DIGITAL_INPUT_0_NOT 238
#define EVENT_DIGITAL_INPUT_1 19
#define EVENT_DIGITAL_INPUT_1_NOT 237
#define EVENT_DIGITAL_INPUT_2 20
#define EVENT_DIGITAL_INPUT_2_NOT 236
#define EVENT_DIGITAL_INPUT_3 21
#define EVENT_DIGITAL_INPUT_3_NOT 235
#define EVENT_OI_MODE 22
#define EVENT_OI_MODE_NOT 234
#define EVENT_NONE 0
//stream commands
#define STREAM 148

#endif /* PROTOCOL_H_ */
