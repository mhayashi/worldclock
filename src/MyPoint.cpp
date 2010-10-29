#include "MyPoint.h"
#include "Utility.h"

MyPoint::MyPoint() {
	// nothing
}

MyPoint::MyPoint(double _latitude, double _longitude, Earth &earth) {
	init(_latitude, _longitude, earth);
}

void MyPoint::init(double _latitude, double _longitude, Earth &earth) {
	lat = _latitude;
	lng = _longitude;
	latitude = _latitude + 90.0;
	longitude = _longitude + 180.0;
	longitude *= -1;
	x = earth.radius * sin(radian(longitude)) * sin(radian(latitude));
	y = earth.radius * cos(radian(longitude)) * sin(radian(latitude));
	z = earth.radius * cos(radian(latitude));
}

void MyPoint::draw(void) {
	glPushMatrix();
	glColor3d(1, 1, 1);
	glPointSize(1.0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex3d(x, y, z);
	glEnd();
	glPopMatrix();
}
