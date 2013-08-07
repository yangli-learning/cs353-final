#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include <iostream>
#include <string.h>
/**
 * CSC353 Final Project
 * Janet Guo & Yang Li
 * 
 * Set up openFrameworks window
 */
int main( ){
  ofAppGlutWindow window;               //setup the GL window 
  ofSetupOpenGL(&window, 800,400, OF_WINDOW); 
  ofSetFrameRate(30);                 
  cout << "Set frame rate to "<<ofGetFrameRate()<< " frames/src"<<endl;
  testApp *app = new testApp();
  ofRunApp(app);                        //this kicks off the running of my app
                                        // can be OF_WINDOW or OF_FULLSCREEN
                                        // pass in width and height too
  return 0;	
	
}
