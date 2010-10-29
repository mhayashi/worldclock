#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxDirList.h"
#include "ofxVectorMath.h"
#include "ofxNetwork.h"
#include "ofxOsc.h"
#include "ofxThread.h"
#include "ofxXmlSettings.h"
#include "ofx3DModelLoader.h"

#include "City.h"
#include "Earth.h"

class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);

	// we don't actually use these
	// just checking to see if they
	// all work in the same place :)

	ofxCvGrayscaleImage cvGray;
	ofxDirList dirList;
	ofxVec2f p;
	ofxTCPClient client;
	ofxTCPServer server;
	ofxOscSender osc_sender;
	ofxThread thread;
	ofxXmlSettings settings;
	ofx3DModelLoader modelLoader;

private:
	void setupQuesoGlc();
	GLvoid displayFPS();
	void initQuadric();
	void drawString();
	void drawXYZ();
	
	Earth *earth;

	const static int maxCities = 3;
	vector<City> cities;
	
	const static int maxLatitude = 36;
	const static int maxLongitude = 36;
	MyPoint *points[maxLatitude * maxLongitude];

	GLfloat rotX;
	GLfloat rotY;
	GLfloat rotZ;
	GLfloat speedX;
	GLfloat speedY;
	GLfloat speedZ;
	GLfloat eyeX;
	GLfloat eyeY;
	GLfloat eyeZ;

	bool showXYZ;
	bool showError;

	ofTrueTypeFont inputFont;
	ofTrueTypeFont displayFont;

	string input;
	string error;

	int current;
	
	GLint ctx;
	GLint font;
};

#endif
