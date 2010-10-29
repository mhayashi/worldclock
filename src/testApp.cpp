#include <iostream>
#include "time.h"
#include "testApp.h"
#include "City.h"
#include "GeoInfo.h"
#include "Utility.h"
#include "glc.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);

	ofBackground(0, 0, 0);
	
	//ofEnableAlphaBlending();
	ofEnableSmoothing();
	
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClearDepth(1.0f);				// Depth buffer setup

	//glDepthFunc(GL_LESS);
	//glEnable(GL_DEPTH_TEST);
	//glShadeModel(GL_SMOOTH);		// Enable smooth shading

	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really nice perspective calculations

	setupQuesoGlc();
	
	// load font with extended parameters:
	// font name, size, anti-aliased, full character set
	//inputFont.loadFont("verdana.ttf", 60, true, true);
	//displayFont.loadFont("Osaka.ttf", 15, true, true);
	input = "";
	
	earth = new Earth(200.0f);
	earth->init();
	earth->initQuadric();

	rotX = 0.0f;
	rotY = 0.0f;
	rotZ = 0.0f;
	speedX = 0.0f;
	speedY = 0.0f;
	speedZ = 0.0f;
	eyeX = 0.0f;
	eyeY = 0.0f;
	eyeZ = -1.0f;
	showXYZ  = false;
	current = 0;
	error = "Error!";
	
	for (int j = 0; j < maxLongitude; ++j) {
		for (int i = 0; i < maxLatitude; ++i) {
			points[maxLatitude * j + i] = new MyPoint(double(i) * maxLatitude - 180.0,
													  double(j) * (360.0 / maxLongitude),
													  *earth);
		}
	}

	string _cities[] = {"tokyo"};
	for (int i = 0; i < 1; ++i) {
		cities.push_back(City(_cities[i], *earth));
	}
}

// Set up and initialize GLC
void testApp::setupQuesoGlc()
{
	ofSetVerticalSync(true);
	//ofSetFrameRate(60);
	
	//ofEnableAlphaBlending();
	//ofEnableSmoothing();
	
	//ofBackground(0, 0, 0);
	
	ctx = glcGenContext();
	glcContext(ctx);
	
	// glcAppendCatalog(ofToDataPath("font").c_str());
	
	glcAppendCatalog("/System/Library/Fonts");
	
	font = glcGenFontID();
	glcNewFontFromFamily(font, "Hiragino Mincho ProN");
	glcFontFace(font, "W6");
	glcFont(font);
	
	glcRenderStyle(GLC_TEXTURE);
    glcEnable(GLC_GL_OBJECTS);
    glcEnable(GLC_MIPMAP);
	glcEnable(GLC_HINTING_QSO);
	glcStringType(GLC_UTF8_QSO);

}

//--------------------------------------------------------------
void testApp::update()
{
	//ofBackground(0, 0, 0);
	speedX = (cities[current].lat - rotX)/50; 
	speedY = (cities[current].lng - rotY)/50; 
	rotX += speedX;
	rotY += speedY;
	rotZ += speedZ;
	//if (rotX == cities[cities.size()-1].lat) speedX = 0;
	//if (rotY == cities[cities.size()-1].lng) speedY = 0;
	if (rotZ >= 360.0f) rotZ = 0.0f;
}


//--------------------------------------------------------------
void testApp::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslatef((GLfloat)(ofGetWidth() / 2), (GLfloat)(ofGetHeight() / 2), 0.0f);
	gluLookAt(eyeX*100, eyeY*100, eyeZ*100, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	//glRotatef(cities[cities.size()-1].lat, 1.0f, 0.0f, 0.0f);		// Rotate On The X Axis
	//glRotatef(-cities[cities.size()-1].lng, 0.0f, 1.0f, 0.0f);		// Rotate On The Y Axis
	glRotatef(rotX, 1.0f, 0.0f, 0.0f);		// Rotate On The X Axis
	glRotatef(-rotY, 0.0f, 1.0f, 0.0f);		// Rotate On The Y Axis
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);		// Rotate On The X Axis
	
	//glRotatef(rotX, 1.0f, 0.0f, 0.0f);		// Rotate On The X Axis
	//glRotatef(rotY, 0.0f, 1.0f, 0.0f);		// Rotate On The Y Axis

	earth->draw();

	for (int j = 0; j < maxLongitude; ++j) {
		for (int i = 0; i < maxLatitude; ++i) {
			points[j * maxLatitude + i]->draw();
		}
	}

	for (int i = 0; i < cities.size(); ++i) {
		cities[i].draw();
	}

	if (showXYZ) drawXYZ();
	glPopMatrix();

	drawString();
	displayFPS();
}


void testApp::drawString()
{
	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix(); {
	
		glTranslatef(ofGetWidth()/2, ofGetHeight()/2 + 10, 0);

		//glRotatef(60, 1, 0, 0);
	
		static float rot = 0;
		glRotatef(-rot, 0, 1, 0);
		if (rot > 360) rot = 0;
		rot += 0.2;

		ofPushStyle(); {
			ofEnableAlphaBlending();
			ofSetColor(255, 255, 255, 127);

			glPushMatrix(); {
				glTranslatef(30, -50, 0);
				glScalef(32, -32, 1);
				char *c;
				sprintf(c, "#%02d", current+1);
				glcRenderString(c);
			} glPopMatrix();

			glPushMatrix(); {
				glTranslatef(30, 0, 0);
				glScalef(32, -32, 1);
				glcRenderString(cities[current].address.c_str());
			} glPopMatrix();
	
			glPushMatrix(); {
				glTranslatef(30, 50, 0);
				glScalef(32, -32, 1);

				time_t rawtime;
				time(&rawtime);
				tm *ptm = gmtime(&rawtime);
				
				time_t localtime = mktime(ptm);
				localtime += cities[current].offset * 3600;
				char *str = ctime(&localtime);
				glcRenderString(str);
			} glPopMatrix();

			ofDisableAlphaBlending();
		} ofPopStyle();

		// draw input string
		glPushMatrix();
		glTranslatef(30, 100, 0);
		glScalef(32, -32, 1);
		//glColor3f(0.f, 1.f, 0.f);
		ofPushStyle();
		ofSetColor(0, 255, 0);
		if (showError) {
			glcRenderString(error.c_str());
		} else {
			glcRenderString(input.c_str());
		}		
		ofPopStyle();
		glPopMatrix();

	} glPopMatrix();
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
	int len = input.length();
	switch(key) {
/*	case ' ':
		input += "%20";
		break;
	case 'x':
		showXYZ = (showXYZ) ? false : true;
		break;
	case 'q':
		eyeZ += 0.005f;
		break;
	case 'w':
		eyeZ -= 0.005f;
		break;
*/
	case OF_KEY_LEFT:
		if (--current < 0) current = cities.size() - 1;
		break;
	case OF_KEY_RIGHT:
		if (++current >= cities.size()) current = 0;
		break;
	case OF_KEY_UP:
		eyeZ -= 0.001f;
		break;
	case OF_KEY_DOWN:
		eyeZ += 0.001f;
		break;
	case OF_KEY_PAGE_UP:
		//eyeY += 0.005f;
		break;
	case OF_KEY_PAGE_DOWN:
		//eyeY -= 0.005f;
		break;
	case OF_KEY_BACKSPACE:
		if (len) input.erase(len-1);
		break;
	case OF_KEY_RETURN:
		input = replace_all(input, " ", "%20");
		try {
			cities.push_back(City(input, *earth));
			input.erase(0);
			current = cities.size() - 1;
		} catch (runtime_error e) {
			cout << e.what() << endl;
			input.erase(0);
			showError = true;
		}
		break;
	default:
		showError = false;
		input += key;
		break;
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::resized(int w, int h)
{
/*	if (h == 0) h = 1;			// prevent a divide by zero by
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();*/
}

GLvoid testApp::displayFPS()
{
	static long lastTime = glutGet(GLUT_ELAPSED_TIME);
	static long loops = 0;
	static GLfloat fps = 0;
	int newTime = glutGet(GLUT_ELAPSED_TIME);
	
	if ((newTime - lastTime) > 100)
	{
		float newFPS = (float)loops / float(newTime - lastTime) * 1000.0f;
		fps = (fps + newFPS) / 2.0f;
		
		char title[80];
		sprintf(title, "GLUT Demo - %.2f", fps);
		
		glutSetWindowTitle(title);
		
		lastTime = newTime;
		loops = 0;
	}
	
	loops++;
}

void testApp::drawXYZ()
{
	glBegin(GL_LINES);

	glColor3d(0, 1, 0);		// x
	glVertex2d(-300, 0);
	glVertex2d(300, 0);

	glColor3d(1, 0, 0);		// y
	glVertex2d(0, 0);
	glVertex2d(0, 300);

	glColor3d(0, 0, 1);		// z
	glVertex3d(0, 0, -300);
	glVertex3d(0, 0,  300);
	glEnd();
}

