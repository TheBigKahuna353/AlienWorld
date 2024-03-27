//  ========================================================================
//  COSC363: Computer Graphics (2024); CSSE  University of Canterbury.
//
//  FILE NAME: Yard.cpp
//  See Lab03.pdf for details.
//  ========================================================================
 
#include <iostream>
#include <cmath> 
#include <GL/freeglut.h>
#include "loadTGA.h"
#include "loadBMP.h"
#include "vec.h"
#include "objects.h"
#include "textures.h"
#include "particles.h"

using namespace std;


float angle=0, look_x, look_z=-100., eye_x=0, eye_z=0;  //Camera parameters
float eye_y = 0;

int timeToCreateMissle = 10;

float takeoffVel = 0;
float takeoffAcc = 0.05;

void timer(int value) {
	update_aliens();
	if (takeOff) {
		if (spaceShipPos.y < 5) {
			spaceShipPos.y += 0.1;
		} else {
			if (spaceShipPos.z < 120) {
				spaceShipPos.z += takeoffVel;
				takeoffVel += takeoffAcc;
				spaceShipPos.y += 0.1;
			}
		}
		
	}
	timeToCreateMissle--;
	if (timeToCreateMissle == 0) {
		timeToCreateMissle = 10;
		// random turret
		int turretIndex = rand() % 6;
		float x = 15 * cos(turretIndex * 30 * M_PI / 180);
		float z = 15 * sin(turretIndex * 30 * M_PI / 180);
		create_missle(x, 2, z-40);
	}
	spaceShipRot += 1;
	if (spaceShipRot > 360) {
		spaceShipRot = 0;
	}
	glutPostRedisplay();
	glutTimerFunc(50, timer, 0);
}

//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
void special(int key, int x, int y)
{
	if(key == GLUT_KEY_LEFT) angle -= 0.1;  //Change direction
	else if(key == GLUT_KEY_RIGHT) angle += 0.1;
	else if(key == GLUT_KEY_DOWN)
	{  //Move backward
		eye_x -= 0.1*sin(angle);
		eye_z += 0.1*cos(angle);
	}
	else if(key == GLUT_KEY_UP)
	{ //Move forward
		eye_x += 0.1*sin(angle);
		eye_z -= 0.1*cos(angle);
	}

	look_x = eye_x + 100*sin(angle);
	look_z = eye_z - 100*cos(angle);

	if (key == GLUT_KEY_SHIFT_L) {
		eye_y -= 0.1;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == ' ') {
		takeOff = !takeOff;
	}
}

//--------------------------------------------------------------------------------

void initialise()
{ 
	float white[4]  = {1.0, 1.0, 1.0, 1.0};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);


	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);    //Default, only for LIGHT0
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);   //Default, only for LIGHT0

	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);    //Default, only for LIGHT0
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);   //Default, only for LIGHT0

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 10.0);


	loadTexture();	
	glEnable(GL_TEXTURE_2D);
	glClearColor(1., 1., 1., 1.);    //Background colour 	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_NORMALIZE);

	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 50);

	glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(60., 1.0, 10.0, 1000.0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	init_objs();
}

//--------------------------------------------------------------------------------

void skydome() {
	int radius = 100;
	int slices = 100;
	int stacks = 100;

	glColor3f(1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, txId[0]);
	// glDisable(GL_TEXTURE_2D);
	// glColor3f(0, 0, 0);
	GLUquadricObj *qobj = gluNewQuadric();
	gluQuadricTexture(qobj, GL_TRUE);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	gluQuadricOrientation(qobj, GLU_INSIDE);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		gluSphere(qobj, radius, slices, stacks);
	glPopMatrix();
	gluDeleteQuadric(qobj);
	// glEnable(GL_TEXTURE_2D);


}
//--------------------------------------------------------------------------------

void floor() {

	float white[4] = {1, 1, 1, 1};
	float black[4] = {0, 0, 0, 1};
	glNormal3f(0.0, 1.0, 0.0);		//Normal vector of the floor
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	glColor3f(0.8, 0.8, 0.8);
	int size = 100;
	// glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, txId[1]);
	glBegin(GL_QUADS);
		for (int i = -size; i < size; i++) {
			for (int j = -size; j < size; j++) {
				glNormal3f(0, 1, 0);
				glTexCoord2f(0, 0);
				glVertex3f(i, -1, j);
				glTexCoord2f(0, 1);
				glVertex3f(i, -1, j+1);
				glTexCoord2f(1, 1);
				glVertex3f(i+1, -1, j+1);
				glTexCoord2f(1, 0);
				glVertex3f(i+1, -1, j);
			}
		}
	glEnd();
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
}



//--------------------------------------------------------------------------------



void display() 
{
	float light[] = {0.0f, 20.0f, 40.0f, 1.0f};  //Light's position (directly above the origin)
	float spotPosn[]={19.0, 7.0, -16.0, 1.0};
	float spotdir[]={aliensPos[0].x-19, aliensPos[0].y-7, aliensPos[0].z+16};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();
	gluPerspective(45., 1., 1., 300.);

	glMatrixMode(GL_MODELVIEW);								
	glLoadIdentity();
	// eye is look from, look is look at, up is up
	gluLookAt(eye_x, eye_y, eye_z,  look_x, 0, look_z,   0, 1, 0);	
	glLightfv(GL_LIGHT0, GL_POSITION, light);	//Set light position

	// float spotPosn[]={0,2,0,1};
	glLightfv(GL_LIGHT1, GL_POSITION, spotPosn);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
	
	floor();
	skydome();

	spaceship();

	update_particles();

	draw_particles();


	// alien();
	// place 6 turrets around the spaceship in a semi circle
	for (int i = 0; i < 6; i++) {
		float x = 15 * cos(i * 30 * M_PI / 180);
		float z = 15 * sin(i * 30 * M_PI / 180);
		turret(x, z-40);
		shadow(x, z-40);
	}

	// lightpost
	lightPost();


	draw_aliens();

	update_missles();

	// draw missles
	draw_missles();


	glutSwapBuffers();									
}

//--------------------------------------------------------------------------------

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA| GLUT_DEPTH);
   glutInitWindowSize (900, 900); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Assingment 1");
   initialise();

   glutDisplayFunc(display); 
   glutSpecialFunc(special);
   glutKeyboardFunc(keyboard);
   glutTimerFunc(50, timer, 0);
   glutMainLoop();
   return 0;
}
