#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //sound
    mySound.load("star.mp3");
//    mySound.play();
    fftSmoothed =new float[128];
    for (int i=0; i<128; i++) {
        fftSmoothed[i] = 0;
    }
    
    //image
    Image.load("p0.jpg");
    Texture1.allocate(Image.getWidth(), Image.getHeight(), GL_RGBA, false);
    Texture1.loadData(Image.getPixels());
    Texture1.generateMipmap();
    Texture1.setTextureWrap(GL_REPEAT, GL_REPEAT);
    
    
    //movie
    Movie.load("movie.mov");
    Movie.play();
    
    
    //camera
    camWidth = 320;  // try to grab at this size.
    camHeight = 240;
    //we can now get back a list of devices.
    vector<ofVideoDevice> devices = Camera.listDevices();
    for(int i = 0; i < devices.size(); i++){
        if(devices[i].bAvailable){
//            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    Camera.setDeviceID(0);
    Camera.setDesiredFrameRate(30);
    Camera.initGrabber(camWidth, camHeight);

}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(12,12,12);
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    //Camera
    Camera.update();
    Texture2.allocate(Camera.getWidth(), Camera.getHeight(), GL_RGBA, false);
    Texture2.loadData(Camera.getPixels());
    Texture2.generateMipmap();
    Texture2.setTextureWrap(GL_REPEAT, GL_REPEAT);
    
    //movie
    Movie.update();
    Texture3.allocate(Movie.getWidth(), Movie.getHeight(), GL_RGBA, false);
    Texture3.loadData(Movie.getPixels());
    Texture3.generateMipmap();
    Texture3.setTextureWrap(GL_REPEAT, GL_REPEAT);
    
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
//shader10 铅笔画
//shader11 水面
//shader12 老电视

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofShader shader;
    shader.load("","shader11.frag");
    
    shader.begin();
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    shader.setUniform2f("u_mouse",ofGetMouseX(), ofGetMouseY());
    
    shader.setUniform4f("u_sound",fftSmoothed[0],fftSmoothed[1],fftSmoothed[2],fftSmoothed[3]);
    
    shader.setUniformTexture("u_texture1", Texture1, 1);
    
    shader.setUniformTexture("u_video", Texture2, 1);
    
    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    shader.end();
    
    
    //video
    Camera.draw(20, 20);
    
    //movie
//    Movie.draw(400, 20);
    
    //image
//    Texture1.draw(20,400);
    
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
