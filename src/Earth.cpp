#include "ofMain.h"
#include "Earth.h"
#include <highgui.h>
#include <cv.h>
#include <iostream>
using std::cout;
using std::endl;

Earth::Earth(GLfloat _radius)
{
	// 'GLfloat Earth::radius' is a static data member; it can only be initialized at its definition
	radius = _radius;
}

bool Earth::init()
{
	//initQuadric();
	return loadTextures();
}

bool Earth::loadTextures()
{
	ofImage image[maxTexture];
	if (image[0].loadImage("earth.jpg")) {
		glGenTextures(maxTexture, &texture[0]);

		for (int i = 0; i < maxTexture; ++i) {
			// Create Linear Filtered Texture
			glBindTexture(GL_TEXTURE_2D, texture[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, image[i].width, image[i].height, 0, GL_RGB, GL_UNSIGNED_BYTE, image[i].getPixels());
			image[i].clear();
		}
		return true;
	}
	cout << "earth init error" << endl;
	return false;
}

void Earth::draw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	ofPushStyle();
	ofSetColor(0, 255, 0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);	// Select Texture
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	gluSphere(q, radius, 64, 32);			// Draw First Sphere
	glDisable(GL_TEXTURE_GEN_S);				// Disable Sphere Mapping
	glDisable(GL_TEXTURE_GEN_T);				// Disable Sphere Mapping
	ofPopStyle();
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}

void Earth::initQuadric()
{
	q = gluNewQuadric();
	gluQuadricNormals(q, GL_SMOOTH);
	gluQuadricTexture(q, GL_TRUE);
	// Setup sphere mapping
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}

