#ifndef __Cloth_h
#define __Cloth_h

#include <vector>
#include <string>
#include "particle.h"
#include "vector3.h"
#include "constraint.h"

#define CONSTRAINT_ITERATIONS 15 

class Plane {
public:
	Vector3 normal;
	float dist;

public:
	Plane(Vector3 v, float d) {
		normal = v;
		dist = d;
	}
};

class Sphere {
public:
	Vector3 pos;
	float radius;

public:
	Sphere(Vector3 p, float r) {
		pos = p;
		radius = r;
	}
};

class Cloth {
private:

	typedef std::vector<Particle>::iterator parts;
	typedef std::vector<Constraint>::iterator constr; 
	int num_particles_width; 
	int num_particles_height; 
	std::vector<Particle> particles; 
	std::vector<Constraint> constraints; 

	Particle* getParticle(int x, int y);
	void makeConstraint(Particle *p1, Particle *p2);
	void calcTriangleNormal(Particle *p1,Particle *p2,Particle *p3);
	void drawTriangle(Particle *p1, Particle *p2, Particle *p3, const Vector3& color);

public:

	Cloth(float width, float height, int num_particles_width, int num_particles_height);
	void draw();
	void timeStep();
	void addForce(const Vector3& direction);
	void ballCollision(const Sphere& sphere);
	void planeCollision(const Plane& plane);
};

#endif