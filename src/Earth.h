#ifndef _EARTH
#define _EARTH

#import <GLUT/GLUT.h>

class Earth
{
public:
	Earth(GLfloat _radius);
	bool init();
	void initQuadric();
	void draw();

	int mode;
	const static int maxMode = 1;
	GLfloat radius;

private:
	bool loadTextures();

	const static int maxTexture = 1;
	GLuint texture[maxTexture];
	GLUquadricObj *q;					// Quadratic For Drawing A Sphere
};

#endif
