#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "vector3.h"

#define DAMPING 0.02f
#define TIME_STEPSIZE2 0.5f*0.5f

class Particle
{
private:
	bool movable; 

	float mass; 
	Vector3 pos; 
	Vector3 old_pos; 
	Vector3 acceleration; 
	Vector3 normal; 

public:
	Particle(Vector3 pos) : pos(pos), old_pos(pos),
	acceleration(Vector3(0,0,0)), 
	mass(1), 
	movable(true), 
    normal(Vector3(0,1,0)){}
	Particle(){ }

	void addForce(const Vector3& f);
	void timeStep();
	Vector3& getPos();
	void resetAcceleration();
	void offsetPos(const Vector3& v);
	void makeUnmovable();
	Vector3& getNormal(); 
	void resetNormal();

};

#endif