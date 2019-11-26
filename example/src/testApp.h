#pragma once

#include "ofMain.h"
#include "ofxZxing.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);

	ofxZxing::Result result;
	ofImage logo;
	ofVideoGrabber cam;
	ofVideoPlayer player;
	float lastFound;
	bool isVideo;
};
