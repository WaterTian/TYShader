#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //sound
    mySound.load("star.mp3");
    mySound.play();
    fftSmoothed =new float[128];
    for (int i=0; i<128; i++) {
        fftSmoothed[i] = 0;
    }
    
    //textrue
    ofImage img;
    img.load("p0.jpg");
    Texture1.allocate(img.getWidth(), img.getHeight(), GL_RGBA, false);
    Texture1.loadData(img.getPixels());
    Texture1.generateMipmap();
    Texture1.setTextureWrap(GL_REPEAT, GL_REPEAT);
    
    
    //video
    camWidth = 320;  // try to grab at this size.
    camHeight = 240;
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
//            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    vidGrabber.setDeviceID(0);
    vidGrabber.setDesiredFrameRate(30);
    vidGrabber.initGrabber(camWidth, camHeight);

}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(12,12,12);
    
    //video
    vidGrabber.update();
    if(vidGrabber.isFrameNew()){
        videoTexture = vidGrabber.getTexture();
    }
    
    //sound
    float * val = ofSoundGetSpectrum(128);	// request 128 values for fft
    for (int i = 0;i < 128; i++){
        fftSmoothed[i] *= 0.96f;
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
    }

}
//shader1 水墨
//shader2，3，4 ，5 cell
//shader7 油画
//shader8 sea
//shader9 星空


//--------------------------------------------------------------
void ofApp::draw(){
    
    ofShader shader;
    shader.load("","shader10.frag");
    
    shader.begin();
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    shader.setUniform2f("u_mouse",ofGetMouseX(), ofGetMouseY());
    
    shader.setUniform4f("u_sound",fftSmoothed[0],fftSmoothed[1],fftSmoothed[2],fftSmoothed[3]);
    
    shader.setUniformTexture("u_video", videoTexture, 1);
    
    shader.setUniformTexture("u_texture1", Texture1, 1);
    
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    shader.end();
    
    
    //video
//    vidGrabber.draw(20, 20);
//    videoTexture.draw(20 + camWidth, 20, camWidth, camHeight);
    
    //sound
    ofSetColor(255,255,255,200);
    for (int i = 0;i < 128; i++){
        ofDrawRectangle(i*6+20,20,4,fftSmoothed[i]*20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
