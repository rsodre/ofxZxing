#include "Result.h"

namespace ofxZxing {

Result::Result() :
	found(false) {
}

Result::Result(string text, vector<ofVec2f> points) :
	found(true), text(text), points(points), screenScale(1.0f) {
	if(points.size() > 1) {
		screenNormal = points[1] - points[0];
	}
	if(points.size() > 2) {
		center = (points[0] + points[2]) / 2;
	}
	screenSize = screenNormal.length();
}

void Result::drawTextBox(string text, ofVec2f position, ofColor fgColor, ofColor bgColor) {
	ofPushStyle();
	
	int border = 4 / screenScale;
	int x = (int) position.x - border;
	int y = (int) position.y - (4 / screenScale) - (border * 2);
	int w = text.length() * (8 / screenScale) + (border * 2);
	int h = (8 / screenScale) + (border * 2);
	if( screenFlipped )
		x -= w - border;

	ofFill();
	ofSetColor(bgColor);
	ofRect( x, y, w, h );
	
	ofSetColor(fgColor);
	ofDrawBitmapString(text, position);
	
	ofPopStyle();
}

void Result::draw(ofColor fgColor, ofColor bgColor) {
	ofPushMatrix();
	ofScale(screenScale, screenScale);
	
	ofPushStyle();
	
	ofSetColor(ofColor::red);
	ofSetLineWidth(3);
	
#ifdef OF_IPHONE
	
	GLfloat triVertices[points.size()*2];
	
	for(int i = 0; i < points.size(); i++) {
		triVertices[i] = points[i].x;
		triVertices[i+1] = points[i].y;
	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, triVertices);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
	glDisableClientState(GL_VERTEX_ARRAY);
	
#elseif
	
	
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < points.size(); i++) {
		glVertex2f(points[i].x, points[i].y);
	}
	glEnd();
	
#endif	
	for(int i = 0; i < points.size(); i++) {
		drawTextBox(ofToString(i), points[i], fgColor, bgColor);
	}
	
	drawTextBox(text, center, fgColor, bgColor);
	
	ofPopStyle();
	
	ofPopMatrix();
}

bool Result::getFound() const {
	return found;
}

string Result::getText() const {
	return text;
}

vector<ofVec2f>& Result::getPoints() {
	return points;
}

ofVec2f Result::getScreenPosition() const {
	return center;
}

ofVec2f Result::getScreenNormal() const {
	return screenNormal;
}

float Result::getScreenSize() const {
	return screenSize;
}

float Result::getRotation(ofVec2f relativeTo) const {
	return relativeTo.angle(screenNormal);
}

}
