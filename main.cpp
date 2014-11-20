#ifdef _WIN32
#include <windows.h> 
#endif
#include <GL/gl.h>
#include "glut.h" 
#include <math.h>
#include <vector>
#include <iostream>

#include "vector3.h"
#include "particle.h"
#include "constraint.h"
#include "cloth.h"

Cloth  cloth(15,15,55,55); 
Sphere sphere(Vector3(7,-5,0), 3); 
Plane  plane(Vector3(0,1,0), -8);

void init(GLvoid)
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.2f, 0.2f, 0.4f, 0.5f);				
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_COLOR_MATERIAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}


void display(void)
{
	cloth.addForce(Vector3(0,-0.1,0)); 
	cloth.timeStep(); 
	cloth.ballCollision(sphere); 
	cloth.planeCollision(plane);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glBegin(GL_POLYGON);
	glColor3f(0.0f,0.8f,1.0f);
	glVertex3f(-200.0f,-100.0f,-100.0f);
	glVertex3f(200.0f,-100.0f,-100.0f);
	glColor3f(0.4f,0.9f,0.3f);	
	glVertex3f(200.0f,100.0f,-100.0f);
	glVertex3f(-200.0f,100.0f,-100.0f);
	glEnd();

	glTranslatef(-5 ,6,-10); 
	glRotatef(45,0,1,0); 

	cloth.draw();

	glPushMatrix(); 
	glTranslatef(sphere.pos.f[0],sphere.pos.f[1],sphere.pos.f[2]); 
	glColor3f(0.9f,1.0f,0.0f);
	glutSolidSphere(sphere.radius-0.1,50,50); 
	glPopMatrix();

	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)  
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();  
	gluPerspective (80,(float)w /(float)h,1.0,100 );
	glMatrixMode(GL_MODELVIEW);  
	glLoadIdentity(); 
}

void mouse(int button, int state, int x, int y) 
{
}

void keyboard( unsigned char key, int x, int y ) 
{
	switch ( key ) {
	case 27:    
		exit ( 0 );
		break;
	case 'w':
		sphere.pos.f[2] -= 0.3;
		break;
	case 's':
		sphere.pos.f[2] += 0.3;
		break;
	case 'q':
		sphere.pos.f[1] -= 0.3;
		break;
	case 'e':
		sphere.pos.f[1] += 0.3;
		break;
	case 'a':
		sphere.pos.f[0] -= 0.3;
		break;
	case 'd':
		sphere.pos.f[0] += 0.3;
		break;
	case 'z':
		plane.dist -= 0.1;
		break;
	case 'x':
		plane.dist += 0.1;
		break;
	default: 
		break;
	}
}

void arrow_keys( int a_keys, int x, int y ) 
{
	switch(a_keys) {
	case GLUT_KEY_UP:
		glutFullScreen();
		break;
	case GLUT_KEY_DOWN: 
		glutReshapeWindow (720, 512 );
		break;
	default:
		break;
	}
}

int main ( int argc, char** argv ) 
{
	glutInit( &argc, argv );

	glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH ); 
	glutInitWindowSize(720, 512 ); 

	glutCreateWindow( "Cloth Simulation W S Q E A D" );
	init();
	glutDisplayFunc(display);  
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutSpecialFunc(arrow_keys);

	glutMainLoop();
}