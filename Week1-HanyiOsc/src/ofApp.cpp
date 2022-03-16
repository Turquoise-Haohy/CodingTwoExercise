#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    
    //Initialize the drawing variables
    for (int i = 0; i < ofGetWidth(); ++i) {
        waveform[i] = 0;
    }
    waveIndex = 0;
    
    // Maximilian audio stuff
    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    myClock.setTempo(120);
    myClock.setTicksPerBeat(4);
    
    // Setup ofSound
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    /////////////// waveform
    ofTranslate(0, ofGetHeight()/2);
    ofSetColor(0, 255, 0);
    ofFill();
    ofDrawLine(0, 0, 1, waveform[1] * ofGetHeight()/20.); //first line
    for(int i = 1; i < (ofGetWidth() - 1); ++i) {
        ofDrawLine(i, waveform[i] * ofGetHeight()/20., i + 1, waveform[i+1] * ofGetHeight()/20.);
    }
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer& input){
    std::size_t inChannels = input.getNumChannels();
    for (size_t i = 0; i < input.getNumFrames(); i++)
    {
        input[i * inChannels + 1] = input[i * inChannels];
        // handle input here
 
        // microSample = input * 2 * myOsc1.sinewave(100);
    }
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output){
    
    std::size_t outChannels = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); ++i){
        
        myClock.ticker();
        
        if (myClock.tick){
            
            myFreq += 50;
        }
        
        
        out1 =  2 * myOsc1.sinewave(100);
        out2 = myOsc2.saw(0.5) * myOsc2.sinewave(44);
        //rain = myOsc3.noise(out2) * 0.02;
        out3 = myOsc4.coswave(44) * myOsc5.coswave(88) * myOsc6.saw(2);
        out4 = 2 * myOsc7.square(myOsc8.saw(10)) * myOsc9.sinewave(0.5);
        
        output[i * outChannels] = out1 + out2 + out3 + out4;
      //  output[i * outChannels] = myOsc1.sinewave(myFreq + (myOsc2.sinewave(0.1)*100)) * 0.5;
        output[i * outChannels + 1] = output[i * outChannels];
        
        //Hold the values so the draw method can draw them
        waveform[waveIndex] =  output[i * outChannels];
        if (waveIndex < (ofGetWidth() - 1)) {
            ++waveIndex;
        } else {
            waveIndex = 0;
        }
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
