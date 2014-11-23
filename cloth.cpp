#include <windows.h> 
#include "cloth.h"
#include <stdio.h>
#include <vector>
#include <string>
#include "particle.h"
#include "vector3.h"
#include "constraint.h"
#include <GL/gl.h>

Cloth::Cloth(float width, float height, int num_particles_width, int num_particles_height) 
	: num_particles_width(num_particles_width), num_particles_height(num_particles_height) {
	particles.resize(num_particles_width*num_particles_height); 

	for(int x=0; x<num_particles_width; x++) {
		for(int y=0; y<num_particles_height; y++) {
			Vector3 pos = Vector3(width * (x/(float)num_particles_width),
							0,
							height * (y/(float)num_particles_height));
			particles[y*num_particles_width+x]= Particle(pos); 
		}
	}

	/*
	(x,y)   *--* (x+1,y)
			|  |
			|  |
	(x,y+1) *--* (x+1,y+1)
	*/

#define TOP_LEFT		x,y
#define TOP_RIGHT		x+1,y
#define BOTTOM_LEFT		x,y+1
#define BOTTOM_RIGHT	x+1,y+1

	for(int x=0; x<num_particles_width; x++) {
		for(int y=0; y<num_particles_height; y++) {
			if (x < num_particles_width-1) 
				makeConstraint(getParticle(TOP_LEFT),getParticle(TOP_RIGHT)); // (x,y) --- (x+1,y)
			
			if (y < num_particles_height-1) 
				makeConstraint(getParticle(TOP_LEFT),getParticle(BOTTOM_LEFT)); // (x,y) --- (x,y+1)
			
			if (x < num_particles_width-1 && y < num_particles_height-1) {
				makeConstraint(getParticle(TOP_RIGHT),getParticle(BOTTOM_RIGHT)); // (x+1,y) --- (x,y+1)
				makeConstraint(getParticle(BOTTOM_LEFT),getParticle(BOTTOM_RIGHT)); // (x,y+1) --- (x+1,y+1)
			}
		}
	}

#undef TOP_LEFT
#undef TOP_RIGHT
#undef BOTTOM_LEFT
#undef BOTTOM_RIGHT

	for(int i=0;i<num_particles_width; i++)
		getParticle(i ,0)->makeUnmovable(); 

}

Particle* Cloth::getParticle(int x, int y) {return &particles[y*num_particles_width + x];}
void Cloth::makeConstraint(Particle *p1, Particle *p2) {constraints.push_back(Constraint(p1,p2));}

void Cloth::calcTriangleNormal(Particle *p1,Particle *p2,Particle *p3) {
	Vector3 pos1 = p1->getPos();
	Vector3 pos2 = p2->getPos();
	Vector3 pos3 = p3->getPos();

	Vector3 v1 = pos2-pos1;
	Vector3 v2 = pos3-pos1;

	Vector3 norm = v1.cross(v2);

	p1->getNormal() = norm;
	p2->getNormal() = norm;
	p3->getNormal() = norm;
}

void Cloth::drawTriangle(Particle *p1, Particle *p2, Particle *p3, const Vector3& color) {
	glColor3fv( (GLfloat*) &color );

	glNormal3fv((GLfloat *) &(p1->getNormal().normalized() ));
	glVertex3fv((GLfloat *) &(p1->getPos() ));

	glNormal3fv((GLfloat *) &(p2->getNormal().normalized() ));
	glVertex3fv((GLfloat *) &(p2->getPos() ));

	glNormal3fv((GLfloat *) &(p3->getNormal().normalized() ));
	glVertex3fv((GLfloat *) &(p3->getPos() ));
}

void Cloth::draw() {
	parts particle;
	for(particle = particles.begin(); particle != particles.end(); particle++) {
		(*particle).resetNormal();
	}

	for(int x = 0; x<num_particles_width-1; x++) {
		for(int y=0; y<num_particles_height-1; y++) {
			calcTriangleNormal(getParticle(x+1,y),getParticle(x,y),getParticle(x,y+1));
			calcTriangleNormal(getParticle(x+1,y+1),getParticle(x+1,y),getParticle(x,y+1));
		}
	}

	glBegin(GL_TRIANGLES);
	for(int x = 0; x<num_particles_width-1; x++) {
		for(int y=0; y<num_particles_height-1; y++) {
			Vector3 color(0,0,0);
			if (x%2) 
				color = Vector3(0.0f,0.0f,0.0f);
			else
				color = Vector3(0.9f,0.9f,0.9f);

			drawTriangle(getParticle(x+1,y),getParticle(x,y),getParticle(x,y+1),color);
			drawTriangle(getParticle(x+1,y+1),getParticle(x+1,y),getParticle(x,y+1),color);
		}
	}
	glEnd();
}

void Cloth::timeStep() {
	parts particle;
	for(particle = particles.begin(); particle != particles.end(); particle++) {
		(*particle).timeStep(); 
	}

	constr constraint;
	for(int i=0; i<CONSTRAINT_ITERATIONS; i++) {
		for(constraint = constraints.begin(); constraint != constraints.end(); constraint++ ) {
			(*constraint).satisfyConstraint(); 
		}
	}
}

void Cloth::addForce(const Vector3& direction)
{
	parts particle;
	for(particle = particles.begin(); particle != particles.end(); particle++) {
		(*particle).addForce(direction); 
	}

}

void Cloth::ballCollision(const Sphere& sphere)
{
	parts particle;
	for(particle = particles.begin(); particle != particles.end(); particle++) {
		Vector3 v = (*particle).getPos()-sphere.pos;
		float l = v.length();
		if ( v.length() < sphere.radius) {
			(*particle).offsetPos(v.normalized()*(sphere.radius-l)); 
		}
	}
}

void Cloth::planeCollision(const Plane& plane) 
{
	parts particle;
	for(particle = particles.begin(); particle != particles.end(); particle++) {
		float l = (*particle).getPos().dot(plane.normal.normalized());
		if ( l < plane.dist) {
			(*particle).offsetPos(plane.normal.normalized()*(plane.dist-l)); 
		}
	}
}