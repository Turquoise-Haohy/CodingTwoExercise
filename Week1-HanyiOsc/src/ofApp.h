#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{
    
public:
    void setup() override;
    void update() override;
    void draw() override;
    
    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y ) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void mouseEntered(int x, int y) override;
    void mouseExited(int x, int y) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    
    // For drawing
    float waveform[4096]; //make this bigger, just in case
    int waveIndex;
    
    ofSoundStream soundStream;
    
    /* ofxMaxi*/
    void audioIn(ofSoundBuffer& input) override; 
    void audioOut(ofSoundBuffer& output) override;
    maxiOsc myOsc1;
    maxiOsc myOsc2;
    maxiOsc myOsc3;
    maxiOsc myOsc4;
    maxiOsc myOsc5;
    maxiOsc myOsc6;
    maxiOsc myOsc7;
    maxiOsc myOsc8;
    maxiOsc myOsc9;
 
    maxiClock myClock;
    float myFreq = 0;
    
    float out1;
    float out2;
    float rain;
    float out3;
    float out4;
    
};
