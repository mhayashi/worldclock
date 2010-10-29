#ifndef _CITY
#define _CITY

#include "MyPoint.h"
#include "GeoInfo.h"

class City : public MyPoint
{
public:
	City(string city, Earth &earth);
	void draw(void);
	string address;
	int offset;

private:
	void initQuadric();
	
	string name;
	GeoInfo* geoinfo;
	GLUquadricObj *q;					// Quadratic For Drawing A Sphere
};

#endif
