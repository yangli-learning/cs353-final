#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxVectorMath.h"
#include "ofxOpenCv.h"
#include "ofxNetwork.h"
#include <string.h>
/*
 * CSC353 Final Project
 * Janet Guo & Yang Li
 * 
 * class header for openFrameworks app:
 *
 * Finds location and orientation of Create by tracking black blobs, 
 * displays video and set target position by mouseclick
 * Implements a TCP server and send motion commands to client program on Create
 */

//rotate only if angle between velocity vector and target vector is 
//larger than this value (in degrees)
#define ANG_ERR 20  
   
//update angle only if its change since last frame is larger than 
//this value (in degrees)
#define ANG_MARGIN 3

//update distance only if its change since last frame is larger than 
//this value (in pixels)
#define DIST_MARGIN 15

//0 if reactive motion (send instant commands e.g. drive or stop at every
// frame), 1 if non-reactive (translate or rotate by a fixed amount)
#define MODE 0

// note: tracking colors using HSB instead of RGB because its easier

// color class
class color{
 public:
  float hue, sat, bri, area;
  int ID, radius; // blob ID
  ofxVec2f pos;
};
// openframework app class
// must contain setup(), update(), and draw()
class testApp : public ofBaseApp{
 public:
  void setup();
  void update();
  void draw();
  
  void keyPressed  (int key); 
  void mousePressed(int x, int y, int button); 
  
  ofVideoGrabber video; // calls the class ofVideoGrabber which
                        // grabs video from webcam
  int cameraHeight;     // video height
  int cameraWidth;      // video width
  
  int width;            // window width
  int height;           // window height
  
  int noise;            // threshold allowed color variation
  ofxCvColorImage colorImg;       //Main color image which is gonna get wrapped
  ofxCvColorImage colorImgHSV;    //the image doing the wrapping
  
  ofxCvGrayscaleImage hueImg;     //Hue map
  ofxCvGrayscaleImage satImg;     //Saturation map
  ofxCvGrayscaleImage briImg;     //Brightness map
		
  
  ofxCvGrayscaleImage grayChosen; //grayscale image for finding contour 
  ofxCvGrayscaleImage grayTwoChosen; //second grayscale image 

  color one;            //color one we're tracking
  color two;            //color two we're tracking
        
  int mainBody;	        // index of larger blob among tracked blobs
  int antenna;	        // index of smaller blob 
        
  unsigned char * colorTrackedPixelsOne;  //pixel array of raw images
  unsigned char * colorTrackedPixelsTwo;  //pixel array of raw images
  ofTexture trackedTextureOne;            //color texture to draw

  ofxCvContourFinder  findColorOne;   //contour finder

  ofxVec2f target;      //target position
  ofxVec2f velToTarget; //final velocity vector (from current pos to target)
  ofxVec2f vel;         //current velocity vector
  int ang; 		//angle between the velToTarget and vel  
  int dist;		//distance between target and mainBody

  ofxTCPServer TCP;     //TCP server 
};

#endif
