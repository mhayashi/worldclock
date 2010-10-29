#include "ofMain.h"
#include "City.h"
#include "Utility.h"
#include <iostream>
using std::cout;
using std::endl;

City::City(string _name, Earth &earth) : name(_name) {
	geoinfo = new GeoInfo(name);
	init(geoinfo->lat, geoinfo->lng, earth);
	address = geoinfo->address;
	//localtime = geoinfo->localtime;
	offset = geoinfo->offset;
	initQuadric();
}

void City::draw(void) {

	glEnable(GL_DEPTH_TEST);
	glPushMatrix();
	//glColor4d(1, 1, 1, 0.5);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glTranslatef(x, y, z);
	//cout << name << ": " << x << ", " << y << ", " << z << endl;
	//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	//glRotatef(-lng, 0.0f, 1.0f, 0.0f);
	//glRotatef(90.0f - lat, 1.0f, 0.0f, 0.0f);
	//glRotatef(-lng, 0.0f, 0.0f, 1.0f);
	//drawCircle(30.0f, 32, 2);
	ofPushStyle(); {
		ofEnableAlphaBlending();
		ofSetColor(255, 0, 0, 200);
		gluSphere(q, 2, 64, 32);			// Draw First Sphere
		ofDisableAlphaBlending();
	} ofPopStyle();
	glPopMatrix();
	glDisable(GL_DEPTH_TEST);
}

void City::initQuadric()
{
	q = gluNewQuadric();
	gluQuadricNormals(q, GL_SMOOTH);
	gluQuadricTexture(q, GL_TRUE);
	// Setup sphere mapping
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}



