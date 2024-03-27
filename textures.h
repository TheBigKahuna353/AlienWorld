#ifndef H_TEXTURES
#define H_TEXTURES

#include <iostream>
#include <cmath>
#include <GL/freeglut.h>
#include "loadBMP.h"
#include "loadTGA.h"


GLuint txId[5];   //Texture ids



void loadTexture()				
{
	glGenTextures(5, txId); 	// Create 2 texture ids

	glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
	loadBMP("/csse/users/jwi179/Documents/COSC363/assignment/textures/kloppenheim_02_2k.bmp", true);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture
	loadTGA("/csse/users/jwi179/Documents/COSC363/assignment/textures/grass.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture
	loadBMP("/csse/users/jwi179/Documents/COSC363/assignment/textures/metal.bmp", false);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, txId[3]);  //Use this texture
	loadTGA("/csse/users/jwi179/Documents/COSC363/assignment/textures/explosion.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
}

#endif