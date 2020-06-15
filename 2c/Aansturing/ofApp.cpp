#include "ofApp.h"

using namespace cv;
using namespace ofxCv;

void ofApp::setup(){
	grabber.setup(640,480);
}

void ofApp::update(){
	//get new frame
	grabber.update();
	if(grabber.isFrameNew()){
		flow.calcOpticalFlow(grabber);

		if (printFlow == true) {
			//ofxCv function that detects motion
			float motionX = flow.getMotion()[0][0];
			float motionY = flow.getMotion()[0][1];

			if (motionX >= 1) {
				std::cout << "\n Horizontal motion: " << motionX;
			}
			if (motionY >= 1) {
				std::cout << "\n Vertical motion: " << motionY;
			}
		}


	}
}

void ofApp::draw(){
	//draws rectangles at keypoint positions
	grabber.draw(0,0);
	flow.draw();
	if(ofGetMousePressed()){
		ofNoFill();
		ofDrawRectangle(rect);
	}
}

void ofApp::mouseDragged(int x, int y, int button)
	//reset keypoints in designated area
	ofVec2f p2(x,y);
	rect.set(p1,p2.x-p1.x,p2.y-p1.y);
}

void ofApp::mousePressed(int x, int y, int button){
	//reset keypoints
	p1.set(x,y);

	//If this is turned on, the detected motion gets printed
	printFlow = !printFlow;
}

void ofApp::mouseReleased(int x, int y, int button){
	//If the mouse isn't pressed, get keypoint data
	ofVec2f p2(x,y);
	rect.set(p1,p2.x-p1.x,p2.y-p1.y);
	vector<KeyPoint> keypoints;
	vector<KeyPoint> keypointsInside;
	vector<cv::Point2f> featuresToTrack;
    copyGray(grabber, grabberGray);
	FAST(grabberGray,keypoints,2);
	for(int i=0;i<keypoints.size();i++){
		if(rect.inside(toOf(keypoints[i].pt))){
			keypointsInside.push_back(keypoints[i]);
		}
	}
	KeyPointsFilter::retainBest(keypointsInside,30);
	KeyPoint::convert(keypointsInside,featuresToTrack);
	flow.setFeaturesToTrack(featuresToTrack);

}
