#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(250, 250, 250);

	//initializes gui objects
	gui.setup();
	gui.add(liquidness.setup("liquidness", 0.5, 0, 2));
	gui.add(amplitude.setup("amplitude", 0.75, 0, 10));
	gui.add(speedDampen.setup("speedDampen", 7.5, 0, 10));

	//load the 3d model
	model.loadModel("head.3ds");
	model.setPosition(ofGetWidth() * .5, ofGetHeight() * 0.75, 0);

	//load in sounds:
	Audioinput.load("sounds/voice.wav");
	Audioinput.setVolume(0.3);

}

//--------------------------------------------------------------
void ofApp::update() {

	// update the sound playing system:
	ofSoundUpdate();

	//grab the fft, and put in into a "smoothed" array,
	float* val = ofSoundGetSpectrum(nBandsToGet);
	for (int i = 0; i < nBandsToGet; i++) {

		// let the smoothed value sink to zero:
		fftSmoothed[i] *= 0.96f;

		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

	}

	if (fftSmoothed[1] >= 0.145) {
		fftMod = 0.1;
	}
	else {
		fftMod = fftSmoothed[1];
	}

	amplitudeNew = (amplitude - (amplitude * (fftMod * 10)));

	//to prevent glitches
	//if (amplitudeNew <= 0) {
	//	amplitudeNew = 0;
	//}

	//for debugging
	//std::cout << "\nfft: " << fftSmoothed[1];
	//std::cout << "\nfftMod: " << fftMod;
	//std::cout << "\namplitude: " << amplitude;
	//std::cout << "\namplitudeNew: " << amplitudeNew;

}

//--------------------------------------------------------------
void ofApp::draw() {
	
	//rectangle for FFT results
	ofEnableAlphaBlending();
	ofSetColor(100, 100, 100, 100);
	ofDrawRectangle(100, ofGetHeight() - 300, 5 * 128, 200);
	ofDisableAlphaBlending();

	// draw the fft resutls:
	ofSetColor(0, 0, 0, 0);

	float width = (float)(5 * 128) / nBandsToGet;
	for (int i = 0; i < nBandsToGet; i++) {

		ofDrawRectangle(100 + i * width, ofGetHeight() - 100, width, -(fftSmoothed[i] * 200));
	}

	gui.draw();

	drawWithMesh();

}

void ofApp::drawWithMesh() {

	ofEnableDepthTest();

	//colour for face
	ofSetColor(100, 100, 100, 0);

	//get the model attributes we need
	glm::vec3 scale = model.getScale();
	glm::vec3 position = model.getPosition();
	float normalizedScale = model.getNormalizedScale();
	ofVboMesh mesh = model.getMesh(0);
	ofTexture texture;
	ofxAssimpMeshHelper& meshHelper = model.getMeshHelper(0);
	bool bHasTexture = meshHelper.hasTexture();
	if (bHasTexture) {
		texture = model.getTextureForMesh(0);
	}

	ofMaterial material = model.getMaterialForMesh(0);

	ofPushMatrix();

	//translate and scale based on the positioning.
	ofTranslate(position);
	ofRotateDeg(90, 1, 0, 0);
	ofRotateDeg(270, 0, 0, 1);


	ofScale(normalizedScale, normalizedScale, normalizedScale);
	ofScale(scale.x, scale.y, scale.z);

	auto& verts = mesh.getVertices();

	for (unsigned int i = 0; i < verts.size(); i++) {
		verts[i].x += ofSignedNoise(verts[i].x / liquidness, verts[i].y / liquidness, verts[i].z / liquidness, ofGetElapsedTimef() / speedDampen) * amplitudeNew;
		verts[i].y += ofSignedNoise(verts[i].z / liquidness, verts[i].x / liquidness, verts[i].y / liquidness, ofGetElapsedTimef() / speedDampen) * amplitudeNew;
		verts[i].z += ofSignedNoise(verts[i].y / liquidness, verts[i].z / liquidness, verts[i].x / liquidness, ofGetElapsedTimef() / speedDampen) * amplitudeNew;
	}

	//draw the model manually
	if (bHasTexture) texture.bind();
	material.begin();
	mesh.drawWireframe();
	//mesh.drawFaces();
	material.end();
	if (bHasTexture) texture.unbind();

	ofPopMatrix();

	ofDisableDepthTest();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'a') {
		Audioinput.play();

	}

	if (key == 'q') {
		OF_EXIT_APP(0)
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}