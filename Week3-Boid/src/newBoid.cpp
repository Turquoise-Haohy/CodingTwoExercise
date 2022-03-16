//
//  newBoid.cpp
//  emptyExample
//
//  Created by Turqoise on 26/02/2022.
//

#include "newBoid.hpp"
#include "ofMain.h"


void newBoid::draw(){
    ofSetColor(255, 255, 255, 255);
    ofDrawCircle(position.x, position.y, 5 * cos(velocity.y/velocity.x));
}
