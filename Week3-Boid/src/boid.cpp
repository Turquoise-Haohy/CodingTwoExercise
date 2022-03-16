/*
 *  boid.cpp
 *  boids
 *
 *  Created by Marco Gillies on 05/10/2010.
 *  Copyright 2010 Goldsmiths, University of London. All rights reserved.
 *
 */

#include "boid.h"
#include "ofMain.h"

Boid::Boid()
{
	separationWeight = 1.3f;
	cohesionWeight = 0.9f;
	alignmentWeight = 0.1f;
	
	separationThreshold = 20;
	neighbourhoodSize = 100;
	
	position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));
	velocity = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1));
}

Boid::Boid(ofVec3f &pos, ofVec3f &vel)
{
	separationWeight = 1.3f;
	cohesionWeight = 0.9f;
	alignmentWeight = 0.1f;
	
	separationThreshold = 20;
	neighbourhoodSize = 100;
	
	position = pos;
	velocity = vel;
}

Boid::~Boid()
{
	
}

float Boid::getSeparationWeight()
{
	return separationWeight;
}
float Boid::getCohesionWeight()
{
	return cohesionWeight;
}

float Boid::getAlignmentWeight()
{
	return alignmentWeight;
}


float Boid::getSeparationThreshold()
{
	return separationThreshold;
}

float Boid::getNeighbourhoodSize()
{
	return neighbourhoodSize;
}


void Boid::setSeparationWeight(float f)
{
	separationWeight = f;
}
void Boid::setCohesionWeight(float f)
{
	cohesionWeight = f;
}

void Boid::setAlignmentWeight(float f)
{
	alignmentWeight = f;
}


void Boid::setSeparationThreshold(float f)
{
	separationThreshold = f;
}

void Boid::setNeighbourhoodSize(float f)
{
	neighbourhoodSize = f;
}


ofVec3f Boid::getPosition()
{
	return position;
}

ofVec3f Boid::getVelocity()
{
	return velocity;
}

ofVec3f Boid::separation(std::vector<Boid *> &otherBoids)
{
	// finds the first collision and avoids that
	// should probably find the nearest one
	// can you figure out how to do that?
    ofVec3f sep(0,0,0);
	for (int i = 0; i < otherBoids.size(); i++)
	{
        
		if(position.distance(otherBoids[i]->getPosition()) < separationThreshold)
		{
			//ofVec3f v = position - otherBoids[i]->getPosition();
            sep += position - otherBoids[i]->getPosition();
		}
        
	}
    sep.normalize();
    return sep;
}

ofVec3f Boid::groupSeparation(std::vector<Boid *> &otherGroups)
{
    // finds the first collision and avoids that
    // should probably find the nearest one
    // can you figure out how to do that?
    ofVec3f sep(0,0,0);
    
    for (int i = 0; i < otherGroups.size(); i++){
        
        float d = position.distance(otherGroups[i]->getPosition());
        if (d>0 && d < 100){
            sep += position - otherGroups[i]->getPosition();
        }
        
    }
    sep.normalize();
    return sep;
}

ofVec3f Boid::cohesion(std::vector<Boid *> &otherBoids)
{
	ofVec3f average(0,0,0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
		{
			average += otherBoids[i]->getPosition();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v =  average - position;
	v.normalize();
	return v;
}

ofVec3f Boid::alignment(std::vector<Boid *> &otherBoids)
{
	ofVec3f average(0,0,0);
	int count = 0;
	for (int i = 0; i < otherBoids.size(); i++)
	{
		if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
		{
			average += otherBoids[i]->getVelocity();
			count += 1;
		}
	}
	average /= count;
	ofVec3f v =  average - velocity;
	v.normalize();
	return v;
}

void Boid::update(std::vector<Boid *> &otherBoids,
                  std::vector<Boid *> &otherGroups,
                  ofVec3f &min,
                  ofVec3f &max)
{
	velocity += separationWeight*separation(otherBoids);
	velocity += cohesionWeight*cohesion(otherBoids);
	velocity += alignmentWeight*alignment(otherBoids);
    
    velocity += 1.7*groupSeparation(otherGroups);
    
//    std::cout<<velocity<<std::endl;
    if(velocity.x>=10 || velocity.x<=-10){
        velocity.x *= 0.5;
    }
    if(velocity.y>=10 || velocity.y<=-10){
        velocity.y *= 0.5;
    }
	walls(min, max);
	position += velocity;
}

void Boid::walls(ofVec3f &min, ofVec3f &max)
{
	if (position.x < min.x){
		position.x = min.x;
		velocity.x *= -1;
	} else if (position.x > max.x){
		position.x = max.x;
		velocity.x *= -1;
	}
	
	if (position.y < min.y){
		position.y = min.y;
		velocity.y *= -1;
	} else if (position.y > max.y){
		position.y = max.y;
		velocity.y *= -1;
	}
	
	
}

void Boid::draw()
{
    ofSetColor(125, 80, 125, 255);
	ofDrawRectangle(position.x, position.y, 20 * cos(velocity.y/velocity.x), 20 * sin(velocity.y/velocity.x));
    
}


