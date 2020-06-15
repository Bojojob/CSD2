#pragma once

#include "ofMain.h"
#include "ofxCv.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    float getMotionX();
    float getMotionY();

    float motionX;
    float motionY;

    ofVideoGrabber grabber;
    cv::Mat grabberGray;
    ofxCv::FlowPyrLK flow;
    ofVec2f p1;
    ofRectangle rect;

    bool printFlow = false;

};
