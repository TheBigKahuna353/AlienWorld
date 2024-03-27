#if !defined(H_OBJ)
#define H_OBJ

#include <iostream>
#include <fstream>
#include <GL/freeglut.h>
#include "vec.h"
#include "math.h"
#include "textures.h"
#include "particles.h"
using namespace std;

// GLOBALS
vec_t spaceShipPos;
bool takeOff = false;
float spaceShipRot = 0;

vec_t aliensPos[4];
float alien_rotations[4] = {90, -90, -90, 90};

GLUquadricObj *qobj = gluNewQuadric();

#define MISSLE_COUNT 15


vec_t misslePos[MISSLE_COUNT];
bool missleActive[MISSLE_COUNT];
float missleVel[MISSLE_COUNT];

vec_t pos;
vec_t rot;


void init_objs() {
    createVector(&spaceShipPos, 0, 0, -40);

    createVector(&aliensPos[0], 5, 0, -30);
    createVector(&aliensPos[1], -5, 0, -30);
    createVector(&aliensPos[2], -5, 0, -40);
    createVector(&aliensPos[3], 5, 0, -40);

    for (int i = 0; i < MISSLE_COUNT; i++) {
        missleActive[i] = false;
    }

    createVector(&pos, 20, 7, -15);
    
}

void update_aliens() {
    if (aliensPos[0].x < 30) {
        for (int i = 0; i < 4; i++) {
            if (aliensPos[i].x > 0) {
                aliensPos[i].x += 0.1;
            } else {
                aliensPos[i].x -= 0.1;
            
            }
        }
    }
}

void alien() {
	glPushMatrix();
		// body
		glPushMatrix();
			glTranslatef(0, -0.3, -0);
			glScalef(0.5, 0.75, 0.5);
			glutSolidSphere(1, 20, 20);
		glPopMatrix();
		// head
		glPushMatrix();
			glTranslatef(0, 0.5, 0);
			glScalef(0.25, 0.25, 0.25);
			glutSolidSphere(1, 20, 20);
		glPopMatrix();
		// arms
		glPushMatrix();
			glTranslatef(0.5, 0.2, 0);
			glRotatef(0, 0, 1, 0);
			glScalef(0.5, 0.1, 0.1);
			glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-0.5, 0.2, 0);
			glRotatef(0, 0, 1, 0);
			glScalef(0.5, 0.1, 0.1);
			glutSolidCube(1);
		glPopMatrix();
		// lower body
		glPushMatrix();
			glTranslatef(0, -0.75, -0.5);
			glRotatef(90, 1, 0, 0);
			glScalef(0.3, 0.6, 0.3);
			glutSolidSphere(1, 20, 20);
		glPopMatrix();
	glPopMatrix();
}

void draw_aliens() {
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
            glColor3f(0.8, 0.2, 0.2);
            glTranslatef(aliensPos[i].x, aliensPos[i].y, aliensPos[i].z);
            glRotatef(alien_rotations[i], 0, 1, 0);
            alien();
        glPopMatrix();
    }
}


void spaceship() {
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
		glTranslatef(spaceShipPos.x, spaceShipPos.y, spaceShipPos.z);
		//  bottom Body
		glColor3f(0.3, 0.3, 0.3);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			gluCylinder(qobj, 2, 6, 2, 20, 20);
			gluQuadricDrawStyle(qobj, GLU_FILL);
		glPopMatrix();

		//  top Body
		glPushMatrix();
			glTranslatef(0, 2, 0);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(qobj, 6, 1, 1, 20, 20);
			gluQuadricDrawStyle(qobj, GLU_FILL);
		glPopMatrix();
        // bottom
        glPushMatrix();
            glTranslatef(0, 0, 0);
            glRotatef(90, 1, 0, 0);
            gluDisk(qobj, 0, 2, 20, 20);
        glPopMatrix();
		// landing gear
		glPushMatrix();
			glColor3f(0.7, 0.7, 0.7);
			glPushMatrix();
				glTranslatef(0, 0, 2);
				glPushMatrix();
					glRotatef(45, 1, 0, 0);
					gluCylinder(qobj, 0.1, 0.1, 1.5, 20, 20);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, -1, 1);
					glScalef(0.5, 0.5, 0.8);
					glutSolidCube(1);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0, 0, -2);
				glPushMatrix();
					glRotatef(180, 0, 1, 0);
					glRotatef(45, 1, 0, 0);
					gluCylinder(qobj, 0.1, 0.1, 1.5, 20, 20);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(0, -1, -1);
					glScalef(0.5, 0.5, 0.8);
					glutSolidCube(1);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(2, 0, 0);
				glPushMatrix();
					glRotatef(90, 0, 1, 0);
					glRotatef(45, 1, 0, 0);
					gluCylinder(qobj, 0.1, 0.1, 1.5, 20, 20);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(1, -1, 0);
					glScalef(0.8, 0.5, 0.5);
					glutSolidCube(1);
				glPopMatrix();
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-2, 0, 0);
				glPushMatrix();
					glRotatef(270, 0, 1, 0);
					glRotatef(45, 1, 0, 0);
					gluCylinder(qobj, 0.1, 0.1, 1.5, 20, 20);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(-1, -1, 0);
					glScalef(0.8, 0.5, 0.5);
					glutSolidCube(1);
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();
		// alien in cockpit
		glPushMatrix();
			glTranslatef(0, 2.9, 0);
            glColor3f(0.8, 0.2, 0.2);
			alien();
		glPopMatrix();
		// cockpit
		glPushMatrix();
			glEnable(GL_BLEND);
			glColor4f(0, 0, 0, 0.5);
			glTranslatef(0, 2.75, 0);
			glutSolidSphere(1, 20, 20);
		glPopMatrix();
		glDisable(GL_BLEND);
        // light
        for (int i = 0; i < 6; i++) {
            glPushMatrix();
                glRotatef(60*i+spaceShipRot, 0, 1, 0);
                glTranslatef(0, 1, 3);
                glColor3f(1, 1, 0);
                glutSolidSphere(0.5, 20, 20);
            glPopMatrix();
        }
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}

void create_missle(float x, float y, float z) {
    for (int i = 0; i < 6; i++) {
        if (!missleActive[i]) {
            createVector(&misslePos[i], x, y, z);
            missleVel[i] = 1;
            missleActive[i] = true;
            break;
        }
    }
}

void update_missles() {
    for (int i = 0; i < 6; i++) {
        if (missleActive[i]) {
            vec_t direction;
            subtractVector(&spaceShipPos, &misslePos[i], &direction);
            normalizeVector(&direction);
            scaleVector(&direction, missleVel[i], &direction);
            addVector(&misslePos[i], &direction, &misslePos[i]);
            float dist = distance(&misslePos[i], &spaceShipPos);
            if (dist < 2) {
                missleActive[i] = false;
                for (int j = 0; j < 3; j++) {
                    create_particle(misslePos[i].x, misslePos[i].y, misslePos[i].z);
                }
            }
        }
    }
}

void draw_missles() {
    for (int i = 0; i < 6; i++) {
        if (missleActive[i]) {
            glPushMatrix();
                glTranslatef(misslePos[i].x, misslePos[i].y, misslePos[i].z);
                vec_t direction;
                lookAt(&misslePos[i], &spaceShipPos, &direction);
                glRotatef(direction.y, 0, 1, 0);
                glRotatef(-direction.z, 0, 0, 1);
                glColor3f(0.8, 0.8, 0.8);
                glScalef(0.5, 0.1, 0.1);
                glutSolidCube(1);
            glPopMatrix();
        }
    }
}

void lightPost() {
    glBindTexture(GL_TEXTURE_2D, txId[2]);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    lookAt(&pos, &aliensPos[0], &rot);
    // post
    glPushMatrix();
        glTranslatef(20, 0, -15);
        glPushMatrix();
            glTranslatef(0, 3, -0);
            glScalef(0.5, 8, 0.5);
            glutSolidCube(1);
        glPopMatrix();
        // light
        glPushMatrix();
            glTranslatef(0, 7, 0);
            glRotatef(rot.y+90, 0, 1, 0);
            glRotatef(rot.z, 1, 0, 0);
            glTranslatef(0, 0, -0.75);
            gluCylinder(qobj, 0.4, 0.4, 1.5, 20, 20);
        glPopMatrix();
    glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void turret(float x, float z) {
	vec_t pos;
	createVector(&pos, x, 1, z);
	vec_t lookAtPos;
	createVector(&lookAtPos, spaceShipPos.x, spaceShipPos.y, spaceShipPos.z);

	vec_t direction;
	lookAt(&pos, &lookAtPos, &direction);
	// glColor3f(0.8, 0.8, 0.8);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, txId[2]);
	// body
	glPushMatrix();
		glTranslatef(pos.x, 0, pos.z);
		glScalef(0.2, 2, 0.2);
		glutSolidCube(1);
	glPopMatrix();
	// mount
	glPushMatrix();
		glTranslatef(pos.x, 1, pos.z);
		
		glRotatef(direction.y, 0, 1, 0);
		glRotatef(-direction.z, 0, 0, 1);
		glScalef(1, 0.5, 0.5);
		glTranslatef(0, 0, 1);
		glutSolidCube(1);
		glTranslatef(0, 0, -2);
		glutSolidCube(1);
		glTranslatef(0, 0, 1);
		glScalef(0.5, 0.5, 1);
		glutSolidCube(1);
	glPopMatrix();
	// look as sphere
	glPushMatrix();
		glColor3f(0.8, 0.8, 0.8);
		glTranslatef(lookAtPos.x, lookAtPos.y, lookAtPos.z);
		glutSolidSphere(0.1, 20, 20);
	glPopMatrix();
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}



void shadow(float x, float z) {
	// Light source position = (lx, ly, lz)
    float lx = 0.0;
    float ly = 20.0;
    float lz = 40.0;
	float shadowMat[16] = {ly, 0, 0, 0, -lx, 0, -lz, -1, 0, 0, ly, 0, 0, 0, 0, ly};
	// Draw shadow
	glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
	glPushMatrix();
        glTranslatef(0, -0.99, 0);
		glMultMatrixf(shadowMat);
		/* Transformations */
		glColor4f(0, 0, 0, 1.0);
        glTranslatef(0, 0, -3.5);
        turret(x, z);
	glPopMatrix();
	glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
}

#endif