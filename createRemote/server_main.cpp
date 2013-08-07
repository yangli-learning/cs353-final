#include "ServerSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string.h>
using namespace std;
/**
 * CSC353 Final Project
 * Yang Li & Janet Guo
 * 
 * A TCP server that read command from input prompt and send 
 * to a client program
 * Note: this simple server only connects to one client at a time
 *
 * Adapted from Simple Client Server by Rob Tougher
 * http://tldp.org/LDP/LG/issue74/tougher.html
 */

void printUsage(){
  cout << "Please enter commands and press ENTER\n"<<endl;
  cout << "Allowed commands:"<<endl;
  cout << "\tCLOSE\tclose client connection"<<endl;
  cout << "\tFW <speed>\tdrive forward at given speed"<<endl;
  cout << "\tSTOP\tstop driving"<<endl;
  cout << 
  "\tTRAN <distance> <speed>\ttranslate this distance at this speed"<<endl;
  cout << "\tLT <speed>\tturn left at this speed "<<endl;
  cout << "\tRT <speed>\tturn right at this speed"<<endl;
  cout << "\tLR <angle>\trotate left by this angle "<<endl;
  cout << "\tRR <angle>\trotate right by this angle"<<endl;
}

int main (){
  cout << "server running...." << endl;
  try{                                  
    ServerSocket server ( 30000 );      // Create main server socket
    while ( true ){                     // server runs forever
      ServerSocket new_sock;            // bind user socket to port and listen
      server.accept ( new_sock );
      printUsage();
      try{
	while ( true ){
	  char command[256];	        //user input
	  string reply;	                //command from client
	  cout << "> ";  
	  cin.getline(command,256);
	  if (strlen(command) == 0)     //re-prompt user if input is empty
	    continue;
	  new_sock << string(command);  //send command to create
	  new_sock >> reply;	        //read confirmation
	  cout << reply <<endl;
	}
      }catch ( SocketException& ) {}
    }
  }
  catch ( SocketException& e ){
    cout << "Exception was caught:" << e.description() << endl << "Exiting.";
  } 
  return 0;
}
