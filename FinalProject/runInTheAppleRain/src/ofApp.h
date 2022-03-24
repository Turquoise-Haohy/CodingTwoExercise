#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class particle {
    
public:
    ofColor color;
    float size;
    glm::vec3 force, position, direction;
    
    void update();
    void draw();
    
    particle(int x, int y, int z);
    ~particle();
    
    ofTexture mTex;
    
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofEasyCam cam;
    vector<ofBoxPrimitive> boxes;
    ofLight light;
    int maxBoxes;
    int spaceRange;
    int length;
    float velocity;
    int size;
 
    
    ofSoundPlayer bach;
    
    vector<particle> particles;
    int maxParticles;
    
//    ofxPanel gui;
//    ofxToggle experience;
//    ofxButton upButton;
    
    float nBandsToGet;

    ofColor drawColor;


		
};
