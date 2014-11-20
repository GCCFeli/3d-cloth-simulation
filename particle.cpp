#include "vector3.h"
#include "particle.h"

void Particle::addForce(const Vector3& f)
{
	acceleration += f / mass;
}

void Particle::timeStep()
{
	if(movable)
	{
		Vector3 temp = pos;
		pos = pos + (pos-old_pos)*(1.0f - DAMPING) + acceleration * TIME_STEPSIZE2 * .5f;
		old_pos = temp;
		resetAcceleration(); 
	}
}

Vector3& Particle::getPos() {return pos;}

void Particle::resetAcceleration() {acceleration = Vector3(0,0,0);}

void Particle::offsetPos(const Vector3& v) { if(movable) pos += v;}

void Particle::makeUnmovable() {movable = false;}

Vector3& Particle::getNormal() { return normal;} 

void Particle::resetNormal() {normal = Vector3(0,0,0);}