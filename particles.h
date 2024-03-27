#ifndef H_PARTICLES
#define H_PARTICLES

#include <iostream>
#include <fstream>
#include <GL/freeglut.h>
#include "vec.h"
#include "math.h"
#include "textures.h"
using namespace std;

#define PARTICLE_COUNT 100

vec_t particlePos[PARTICLE_COUNT];
bool particleActive[PARTICLE_COUNT];
float particleSize[PARTICLE_COUNT];
float particleRot[PARTICLE_COUNT];
vec_t particleVel[PARTICLE_COUNT];
int particleTime[PARTICLE_COUNT];

void init_particles() {
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        particleActive[i] = false;
    }
}

void create_particle(float x, float y, float z) {
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        if (!particleActive[i]) {
            particleActive[i] = true;
            createVector(&particlePos[i], x, y, z);
            particleSize[i] = 0.1;
            particleRot[i] = rand() % 360;
            particleTime[i] = 0;
            createVector(&particleVel[i], (rand() % 10 - 8) / 1000.0, (rand() % 10 - 8) / 1000.0, (rand() % 10 - 8) / 1000.0);
            break;
        }
    }
}

void update_particles() {
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        if (particleActive[i]) {
            particleTime[i]++;
            particlePos[i].x += particleVel[i].x;
            particlePos[i].y += particleVel[i].y;
            particlePos[i].z += particleVel[i].z;
            if (particleSize[i] < 1.5) {
                particleSize[i] += 0.2;
            }
            if (particleTime[i] > 30) {
                particleActive[i] = false;
            }
        }
    }
}

void draw_particles() {
    float white[] = {1, 1, 1, 1};
    float black[] = {0, 0, 0, 1};
    glEnable(GL_BLEND);
    glMaterialfv(GL_FRONT, GL_SPECULAR, black);
    glDisable(GL_DEPTH_TEST);
    glColor3f(1, 1, 1);
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        if (particleActive[i]) {
            glBindTexture(GL_TEXTURE_2D, txId[3]);
            // 
            float x = particlePos[i].x;
            float yTOP = particlePos[i].y+particleSize[i]/2;
            float yBOTTOM = particlePos[i].y-particleSize[i]/2;
            float z = particlePos[i].z;
            float part = particleRot[i] * M_PI / 180;
            float halfSize = particleSize[i] / 2;
            glNormal3f(0, 0, 1);
            glBegin(GL_QUADS);
                glTexCoord2f(0, 0); glVertex3f(x - halfSize * cos(part), yBOTTOM, z - halfSize * sin(part));
                glTexCoord2f(1, 0); glVertex3f(x + halfSize * cos(part), yBOTTOM, z + halfSize * sin(part));
                glTexCoord2f(1, 1); glVertex3f(x + halfSize * cos(part), yTOP, z + halfSize * sin(part));
                glTexCoord2f(0, 1); glVertex3f(x - halfSize * cos(part), yTOP, z - halfSize * sin(part));

                part += 90 * M_PI / 180;

                glTexCoord2f(0, 0); glVertex3f(x - halfSize * cos(part), yBOTTOM, z - halfSize * sin(part));
                glTexCoord2f(1, 0); glVertex3f(x + halfSize * cos(part), yBOTTOM, z + halfSize * sin(part));
                glTexCoord2f(1, 1); glVertex3f(x + halfSize * cos(part), yTOP, z + halfSize * sin(part));
                glTexCoord2f(0, 1); glVertex3f(x - halfSize * cos(part), yTOP, z - halfSize * sin(part));
            glEnd();
        }
    }
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
}


#endif