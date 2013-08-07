#include "testApp.h"
#include <iostream>

/*
 * CSC353 Final Project
 * Janet Guo & Yang Li
 *
 * class definition for openFrameworks app
 */

//--------------------------------------------------------------
void testApp::setup(){
//----Video set-up ---------------------------------------------
  // try to grab at this size.
  cameraWidth = 400;
  cameraHeight = 300;
  // setup video grabber:
  video.setVerbose(true);
  video.initGrabber(cameraWidth,cameraHeight);
  // get the width and height
  width = video.width;
  height = video.height;

//----Initalize global variables --------------------------
    one.pos = ofxVec2f(0,0); // initalize color one's position
    two.pos = ofxVec2f(0,0); // initalize color two's position
    one.ID = 1;
    two.ID = 2;
    one.bri = 0; // 0 brightness = black
    two.bri = 0;
    one.radius = 0;
    ang = 0;
    dist = 0;
    noise = 55; // color threshold (may need calibration every time)
    mainBody = 0; // default: first blob is the large blob, aka robot body
    antenna = 1;
    colorImg.allocate(width,height);
    colorImgHSV.allocate(width,height);

    hueImg.allocate(width,height);
    satImg.allocate(width,height);
    briImg.allocate(width,height);

    grayChosen.allocate(width, height);
    grayTwoChosen.allocate(width, height);

    colorTrackedPixelsOne = new unsigned char [width * height];
    colorTrackedPixelsTwo = new unsigned char [width * height];

    trackedTextureOne.allocate(width, height, GL_LUMINANCE);

    target = ofxVec2f(100,100);
    vel = ofxVec2f(0,1);

//----Server setup----------------------------------------
    TCP.setup(30000);    //setup the server to listen on 30000
}

//--------------------------------------------------------------
void testApp::update(){
  video.grabFrame();
  colorImg.setFromPixels(video.getPixels(), width, height);

  colorImgHSV = colorImg;
  colorImgHSV.convertRgbToHsv();

  colorImgHSV.convertToGrayscalePlanarImages(hueImg, satImg, briImg);
  hueImg.flagImageChanged();
  satImg.flagImageChanged();
  briImg.flagImageChanged();

  unsigned char * briPixels = briImg.getPixels();
  int nPixels = width * height;
  for (int i = 0; i < nPixels; i++){
    if (briPixels[i] >= one.bri && briPixels[i]<= one.bri + noise){  
      colorTrackedPixelsOne[i] = 255;
   } else {
      colorTrackedPixelsOne[i] = 0;
    }
  }
  grayChosen.setFromPixels(colorTrackedPixelsOne, width, height);
  findColorOne.findContours(grayChosen, 10,nPixels/3, 2, false, true);
  trackedTextureOne.loadData(colorTrackedPixelsOne, width, height,
			     GL_LUMINANCE);

  //if contours are detected, identify contours
  if(findColorOne.blobs.size() > 0) {

    // if second contour's area is >, than make it the mainBody
    if (findColorOne.blobs[1].area>findColorOne.blobs[0].area){ 
      mainBody = 1;
      antenna = 0;
    } else{
      mainBody = 0;
      antenna = 1;
    }
    one.pos = ofxVec2f(findColorOne.blobs[mainBody].centroid.x,findColorOne.blobs[mainBody].centroid.y);
    one.area = findColorOne.blobs[mainBody].area;
    one.radius = (int)(findColorOne.blobs[mainBody].boundingRect.width*.5);
    two.pos = ofxVec2f(findColorOne.blobs[antenna].centroid.x,findColorOne.blobs[antenna].centroid.y);  
    two.area = findColorOne.blobs[antenna].area;
    vel.set(two.pos.x-one.pos.x,two.pos.y-one.pos.y);
    velToTarget.set(target.x-one.pos.x,target.y-one.pos.y);

    //update angle
    int oldAng = ang;
    ang = (int) vel.angle(velToTarget);
    if ((oldAng-ang > 0 && oldAng-ang < ANG_MARGIN)
	|| (oldAng-ang < 0 && oldAng-ang > -ANG_MARGIN)){
      ang = oldAng;
    }

    //update distance from target
    int oldDist = dist;
    dist = (int)one.pos.distance(target);
    if ((oldDist-dist>0 && oldDist-dist < DIST_MARGIN)
	|| (oldDist-dist<0 && oldDist-dist > -DIST_MARGIN)){
      dist = oldDist;
    }
    //create commands
    char command[256]; //initalize command string

#if MODE==0	//reactive mode	
    if ( dist > one.radius){
      if(ang < -ANG_ERR){
	sprintf( command, "LT 100");
      } else if(ang > ANG_ERR) {
	sprintf( command, "RT 100");
      }else{
	sprintf(command, "FW %i", 100);
      }
    }else{
      sprintf(command,"STOP");
    }
#else //non-reactive mode	
    if ( dist > one.radius){
	  if(ang < -ANG_ERR){
	    sprintf( command, "LT %i TRAN %i 200",  -ang, dist);
	  } else if (ang > ANG_ERR) {
	    sprintf( command, "RT %i TRAN %i 200", ang, dist);
	  }else {
	    sprintf(command, "TRAN %i", dist);
	  }
    }
#endif
    //send commands to all clients
    for(int i = 0; i < TCP.getNumClients(); i++){
      cout << command <<endl;
      TCP.send(i, string(command));
      if (TCP.receive(i).length()>1){
		cout<<TCP.receive(i)<<endl;
      }
    }
  }
}

//--------------------------------------------------------------
void testApp::draw(){
  ofBackground(100,100,100);  //background color
  video.draw(0,0);      	  //draw video
  trackedTextureOne.draw(cameraWidth, 0); //draw tracker

  findColorOne.draw();    	  //draw contour over video

  glPushMatrix();                        
  glTranslatef(cameraWidth,0,0);   
  findColorOne.draw();    	  //draw contour over tracker           
  glPopMatrix();                   
  
  ofSetColor(255,0,0);       
  ofCircle(target.x,target.y,5);  //draw target
  ofSetColor(0,255,0);   			
  ofCircle(one.pos.x,one.pos.y,5);     	//draw mainBody blob center
  ofSetColor(0, 0, 255);
  ofCircle(two.pos.x, two.pos.y, 5);	//draw antenna blob center
  
  ofSetColor(50,50,255);
  glBegin(GL_LINES);	//draw line between center and target and antenna
  glVertex2f(target.x, target.y);
  glVertex2f(one.pos.x, one.pos.y); 
  glVertex2f(one.pos.x, one.pos.y); 
  glVertex2f(two.pos.x, two.pos.y);
  glEnd();
  
  ofSetColor(0xffffff);    		//font color    
  if(findColorOne.blobs.size() > 0) {        
    char tempStr1[255];
    sprintf(tempStr1, 
 "x1 : %f\ny1 : %f\ncolorID01 : %i\nblob_area: %f\nangle: %i\ndistance: %i", 
	    one.pos.x, one.pos.y, one.ID,
	    one.area, ang, dist);
    ofDrawBitmapString(tempStr1, 20, cameraHeight+20);
  }
  
}


//--------------------------------------------------------------
// close client connection when ESC is pressed
void testApp::keyPressed  (int key){ 
  if (key==27){
	cout << "close client connection"<<endl;
	for(int i = 0; i < TCP.getNumClients(); i++){ 
	  TCP.send(i,"stop");
	  TCP.send(i, "close" );  
	}
  }
}


//--------------------------------------------------------------
// confine target within the vedio frame
void testApp::mousePressed(int x, int y, int button){  
  if(button == 0) {
    target.set( MIN(x,cameraWidth-1), MIN(y,cameraHeight-1));
  }

}

