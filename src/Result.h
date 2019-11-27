#pragma once

#include "ofMain.h"

namespace ofxZxing {

class Result {
public:
	Result();
	Result(string text, vector<ofVec2f> points);

	void draw();
	
	bool getFound() const;
	string getText() const;
	vector<ofVec2f>& getPoints();
	
	ofVec2f getScreenPosition() const;
	ofVec2f getScreenNormal() const;
	float getScreenSize() const;
	float getRotation(ofVec2f relativeTo = ofVec2f(0, -1)) const;
	
	void setScreenScale(float scale) {
		screenScale = scale;
	}
	
	/*
	// these would be nice:
	ofVec3f getRealPosition(float physicalSize) const;
	ofVec3f getRealNormal(float physicalSize) const;
	*/
	
protected:
	void drawTextBox(string text, ofVec2f position, ofColor fgColor = ofColor::white, ofColor bgColor = ofColor::red);

	bool found;
	string text;
	vector<ofVec2f> points;
	ofVec2f center;
	ofVec2f screenNormal;
	float screenSize;
	float screenScale;
};

}
