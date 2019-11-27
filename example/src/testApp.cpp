#include "testApp.h"

namespace ofxZxing {
	void drawTextBox(string text, ofVec2f position, ofColor fgColor = ofColor::white, ofColor bgColor = ofColor::black);
}
using namespace ofxZxing;

void testApp::setup() {
	ofSetVerticalSync(true);
	cam.listDevices();
	//cam.setDeviceID(1);
	cam.initGrabber(1920, 1080);
	logo.loadImage("of.png");
	player.load("teste.avi");
	isVideo = false;
}

void testApp::update() {
	bool newFrame = false;
	if(isVideo)
	{
		player.update();
		newFrame = player.isFrameNew();
	}
	else
	{
		cam.update();
		newFrame = cam.isFrameNew();
	}
	
	if(newFrame)
	{
		ofxZxing::Result curResult = ofxZxing::decode(isVideo?player.getPixels():cam.getPixels(), true);
		float curTime = ofGetElapsedTimef();
		if(curResult.getFound())	// only update if we found something, avoid flickering
		{
			result = curResult;
			lastFound = curTime;
		}
		else if(curTime - lastFound > 1)	// if we haven't found anything after a second
		{
			result = curResult; // then update anyway
		}
	}
}

void testApp::draw() {
	ofSetColor(255);
	
	if(isVideo)
		player.draw(0, 0);
	else
		cam.draw(0, 0);
	
	if(result.getFound())
	{
		float rotation = result.getRotation();
		ofVec2f position = result.getScreenPosition();
		float size = result.getScreenSize() / logo.getWidth();
		
		ofPushMatrix();
		ofTranslate(position);
		ofRotate(rotation);
		ofScale(size, size, size);
		logo.draw(-logo.getWidth() / 2, -logo.getHeight() / 2);
		ofPopMatrix();
		
//		drawTextBox(result.getText(), ofVec2f(10,10));

		result.draw();		
	}
}

void testApp::keyPressed(int key)
{
	switch(key)
	{
		case ' ':
		{
			isVideo = !isVideo;
			if (isVideo && !player.isPlaying())
				player.play();
			break;
		}
	}
}
