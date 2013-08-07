#include "include/Create.h"
#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

/**
 * CSC353 Final Project
 * Yang Li & Janet Guo
 * 
 * A TCP client that receives commands from server, and controls basic
 * motion of Create based on received commands 
 *
 * Adapted from Simple Client Server by Rob Tougher
 * http://tldp.org/LDP/LG/issue74/tougher.html
 */

#define PORT 30000          // server process port number
#define IP "localhost"      // default server IP address
#define INIT_SPEED 200      // default speed

//#define TEST_MODE           // uncomment this line to compile in 
                            //test model (do not connect to Create) 

using namespace std;

#if !defined(TEST_MODE)
Create create(Create::FULL);// create robot object
#endif

/** stop the motors */
int stop(){
  cout << "Stop."<<endl;
#if !defined(TEST_MODE)
  create.driveStop();
#endif
  return 0;
}

/** rotate left in place for this angle */
int leftRotate(int angle){
  if (angle > 0){
    cout << "Turn left by "<<angle <<" degrees."<<endl;
#if !defined(TEST_MODE)
    create.rotate(angle,100);
    create.driveStop();
#endif
  }else{
    cout << "Angle should be positive."<<endl;
  }
  return 0;
}

/** rotate right in place for this angle */
int rightRotate(int angle){
  if (angle > 0){
    cout << "Turn right by "<<angle <<" degrees."<<endl;
#if !defined(TEST_MODE)
    create.rotate(-angle,-100);
    create.driveStop();
#endif
  }else{
    cout << "Angle should be positive."<<endl;
  }
  return 0;
}

/** turn left in place at this speed */
int leftTurn(int speed){
  cout << "Turn to the right at speed "<<speed <<endl;
#if !defined(TEST_MODE)
  create.driveDirect(speed,-speed);
#endif
  return 0;
}

/** turn right in place at this speed */
int rightTurn(int speed){
  cout << "Turn to the left at speed "<<speed <<endl;
#if !defined(TEST_MODE)
  create.driveDirect(-speed,speed);
#endif
  return 0;
} 

/** back up from obstacles, eg. move backwards, turn right... */
int backup(int speed=INIT_SPEED){
  cout << "back up half second"<<endl;
#if !defined(TEST_MODE)
  cout << create.sensorsDistance()<<endl;
  create.driveDirect(-speed,-speed);
  create.waitTime(5);
#endif
  leftTurn(90);
  stop();
}

/** move forward by turning on both motors at same speed*/
int forward(int speed){
  if (speed>=-500 && speed <= 500){
    cout << "Drive forward at "<<speed<<" mm/s."<<endl;
#if !defined(TEST_MODE)
    return create.driveDirect(speed,speed);
#else
    return 0;
#endif
  }
  cout << "Speed out of range!"<<endl;
  return 0;
}

/** translate forward at this speed for this distance */
int translate(int distance, int speed){
  cout << "Translate "<< distance << "mm at speed "<<speed<<" mm/s."<<endl;
#if !defined(TEST_MODE)
  if (create.translate2(distance,speed)==EXIT_FAILURE){
    backup();
    return 1;
  } 
#endif
  return 0;
}

/** main function **/
int main(int argc, char *argv[]){  
  //get IP address from command line arguments
  //uses default address if no argument is provided			 
  string addr;
  if (argc>1){
    addr=string(argv[1]);
  }else{
    addr=IP;
  }
  bool disconnect = false;      
  try{
    ClientSocket client_socket( addr, PORT );//create socket that connects 
                                             //to server
      
      while ( ! disconnect )	{
	string reply;	
	try {
	  client_socket >> reply;            //fetch command from socket
	}
	catch ( SocketException& e) {
	  cout << "Exception was caught:" << e.description() << "\n";
	  continue;
	}
	cout << "\nWe received this response from the server:\n\"";
	cout << reply << "\"" << endl ;;    //display command to console


	istringstream iss (reply,istringstream::in);
	string word;

	while (iss >> word){	          //read command word by word
	  if (word == "close" || word == "CLOSE"){
	    stop();
	    cout << "close client connection..." << endl;
	    disconnect = true;
	    break;	  
	  }
	  if (word == "fw" || word == "FW"){
	    if (iss >> word){
	      forward(atoi(word.c_str()) );
	    }
	  }else if (word == "tran" ||word=="TRAN"){	    
	    if (iss >>word){
	      string word2;
	      if (iss >>word2){
		translate(atoi(word.c_str()),atoi(word2.c_str()));
	      }else{
		client_socket << "Invalid command";
		break;
	      }
	    }	
	  }else if (word == "lt" ||word=="LT"){
	    if (iss >>word){
	      leftTurn(atoi(word.c_str()) );
	    }	
	  }else if (word == "rt" ||word=="RT"){
	    if (iss >>word){
	      rightTurn(atoi(word.c_str()) );
	    }	
	  }else if (word == "lr" ||word=="LR"){
	    if (iss >>word){
	      leftRotate(atoi(word.c_str()) );
	    }	
	  }else if (word == "rr" ||word=="RR"){
	    if (iss >>word){
	      rightRotate(atoi(word.c_str()) );
	    }	
	  }else if (word == "stop" || word=="STOP"){
	    stop();	  
	  }else{
	    client_socket << "Invalid command";
	    break;
	  }
	 
	}
	if (!disconnect){
	  client_socket << "receive confirmed";
	}
      }
    }
  catch ( SocketException& e ) {
    cout << "Exception was caught:" << e.description() << endl;
  }
  
  return 0;
}

