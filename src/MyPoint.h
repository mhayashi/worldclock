#ifndef _MY_POINT
#define _MY_POINT

#include "Earth.h"

class MyPoint
{
public:
	MyPoint(double _latitude, double _longitude, Earth &earth);
	void draw(void);

	double x;
	double y;
	double z;

	float lat;
	float lng;
	
protected:
	MyPoint();
	void init(double _latitude, double _longitude, Earth &earth);
	
	float latitude;
	float longitude;
};

#endif
