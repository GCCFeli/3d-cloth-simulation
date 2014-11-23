#ifndef __CONSTRAINT_H__
#define __CONSTRAINT_H__

#include "particle.h"
#include "vector3.h"

class Constraint {
private:
	float rest_distance; 

public:
	Particle *p1, *p2; 

	Constraint(Particle *p1, Particle *p2) :  p1(p1),p2(p2)
	{
		rest_distance = (p1->getPos()-p2->getPos()).length();
	}

	void satisfyConstraint()
	{
		Vector3 delta = p2->getPos() - p1->getPos(); 
		float deltalendth = delta.length(); 
		float diff = (deltalendth - rest_distance) / deltalendth; 
		
		delta *= 0.5f * diff;

		p1->offsetPos( delta); 
		p2->offsetPos(-delta); 
	}
};

#endif