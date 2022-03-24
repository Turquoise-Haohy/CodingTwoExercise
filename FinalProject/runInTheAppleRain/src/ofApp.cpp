#include "ofApp.h"

// This small music interaction piece is to describe a scene in the animation, the night is short, Walk on girl, by Masaaki Yuasa.
// In the story, the protagonist is always running forwards🏃‍♀️ and the world would change🔊 as she moving on. and in one of the scene, two boxes of apples🍎 crashed on the high floor, then the apples are falling down like the rain☔️. I wanted to presented this elements in my output...

//--------------------------------------------------------------
void ofApp::setup(){
    
   // gui.setup();
   // gui.add(experience.setup("Experience",false));
    //ofSetBackgroundColor(255);
    
    //parameters for the variation boxes, which would move forward as the camera move.
    maxBoxes = 100;
    spaceRange = 450;
    length = 500;
    velocity = 1.0;
    
    cam.setDistance(70);
    
    // particle setting for the apples, which eould be triggered by the 'space' key
    maxParticles = 30;
    ofSetSphereResolution(6);
    
    //light setting
    ofEnableDepthTest();
    ofSetBackgroundColor(0);
    light.setPosition(0, 500, 500);
    light.lookAt(ofVec3f(0,0,0));
    light.enable();
    
    //starting setting  for the box
    for (int j = 0; j < maxBoxes; j++) {
        size = ofRandom(30, 200);
        ofBoxPrimitive newBox;
        newBox.set(size);
        newBox.setPosition(ofRandom(-spaceRange,spaceRange),
                           ofRandom(-spaceRange,-100),
                           ofRandom(-length,0));
        for(int side=0; side<6;side++){
            newBox.setSideColor(side, ofColor::fromHsb(ofRandom(255), 125, 255, 200));
        }
        boxes.push_back(newBox);
    }
    
    //load the background music
    bach.load("bach.mp3");
    bach.setVolume(0.6f);
    bach.play();

    

}

//--------------------------------------------------------------
void ofApp::update(){
    
   // if (experience){
    // erase the old boxes while generating new ones
    if(boxes.size() > maxBoxes){
        boxes.erase(boxes.begin());
    }
    
    boxes[ofRandom(boxes.size())].setPosition(ofRandom(-spaceRange,spaceRange),
                                              ofRandom(-spaceRange,-100),
                                              ofRandom(-length, -(length - 500)));
    //cout << velocity << endl;
    
    //give a defalut movement to the camera
    cam.move(0, 0, -1.0);
    length += 1.;
    
    //speed of background music effected by the move speed
    bach.setSpeed(0.5 + velocity * 0.5);
    
    //erase old apples
    if(particles.size() > maxParticles){
        particles.erase(particles.begin());
    }
    
    for(int i = 0; i<particles.size(); i++){
        particles[i].update();
    }
  //  }
    
   
    


}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetBackgroundColorHex(0xe0caeb);
    //gui.draw();
    //float time = ofGetSystemTimeMillis()/1000.0;
    //draw the hints
    ofSetColor(80, 240, 240);
    ofDrawRectRounded(25, 25, 150, 30, 10);
    ofDrawRectRounded(25, 60, 150, 30, 10);
    ofDrawBitmapString("W: Move forward", 35, 43);
    ofDrawBitmapString("Space: apples!", 35, 78);
    
    //draw the boxes and apples
    cam.begin();
    ofPushMatrix();
    //ofRotateDeg(time);
    for(int i = 0; i<boxes.size(); i++){
        boxes[i].draw();
    }
    ofPopMatrix();
    for(int i=0; i<particles.size(); i++){
        particles[i].draw();
    }
    cam.end();
    
    //draw the circle with varition rectangles and colors reactive to the music

    int circleLength = 800;
    // draw the fft resutls:
    ofSetColor(255);
    int barWidth = 60;
    float width = (float)(10*128) / nBandsToGet;
    nBandsToGet =512;
    
    float * val = ofSoundGetSpectrum(nBandsToGet);
    
    
    
    for (int i = 0;i < nBandsToGet; i++){
        // (we use negative height here, because we want to flip them
        // because the top corner is 0,0)
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2 - 400);
        ofRotateDeg(360.0/nBandsToGet * i);
        
        drawColor.setHsb(255/nBandsToGet * i, 180, 255, 160);
        ofSetColor(drawColor);
        ofDrawRectangle(150, -barWidth,-200, val[i] * circleLength*2, width*2);
        //ofDrawRectangle(200+i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
        
        ofPopMatrix();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //touch F for fullscreen
    switch(key){
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
            
    //use 'w', 'a', 'd' for moving forward, left and right
    //use 'q' for moving upward and 'z' for moving downward
        case 'a':
            cam.move(-5.0, 0, 0);
            break;
            
        case 'w':
            if (velocity <= 3.0){
                velocity += 0.02;
                } else{
                    velocity = 3.0;
                }
                cam.move(0, 0, -10.0 * velocity);
                length += 10 * velocity;
            break;
            
        case 'd':
            cam.move(5, 0, 0);
            break;
            
        case 'q':
            cam.move(0, 5, 0);
            break;
            
        case 'z':
            cam.move(0, -5, 0);
            break;
            
    // touching space for apples
            
        case ' ':
            int numParticles = 100;
            for(int i = 0; i < numParticles; i++){
                particle newParticle(ofRandom(-spaceRange*2,spaceRange*2), ofRandom(200,spaceRange*2), -length);
                particles.push_back(newParticle);
            }
            break;
            
      
        
    }
    

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'w'){
        velocity = 1.0;
        }

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



//particle class for apples

particle::particle(int startX, int startY, int startZ){
    
    position = glm::vec3(startX, startY, startZ);
    force = glm::vec3(0.01, -0.01, 0.02);
    direction = glm::vec3(ofRandom(-5.0, 5.0), ofRandom(-3.0, 5.0), ofRandom(-5.0, 5.0));
    size = 20;
    //color.setHsb(hue, 255, 255);
    ofDisableArbTex();
    ofLoadImage(mTex,"apple-skin.jpg");
}

particle::~particle(){
    
}

void particle::update(){
    position += direction ;
    direction += force;
    if(size>1){
        size -= 0.01;
    }
}

void particle::draw(){
    
    mTex.bind();
    ofDrawSphere(position, size);
    mTex.unbind();
    
    ofDrawCylinder(position.x, position.y + 20,position.z, 1, 5);
    ofSetColor(255);
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
