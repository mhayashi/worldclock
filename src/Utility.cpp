#include <iostream>
#include <curl/curl.h>
#import <GLUT/GLUT.h>
#include "Utility.h"

using std::cout;
using std::endl;

char errorBuffer[CURL_ERROR_SIZE];  

string curlBuffer = "";
  
// This is the writer call back function used by curl  
static int writer(char *data, size_t size, size_t nmemb, string *buffer)  
{
	// What we will return  
	int result = 0;  
  
	// Is there anything in the buffer?  
	if (buffer != NULL)  
	{  
		// Append the data to the buffer  
		buffer->append(data, size * nmemb);  
  
		// How much did we write?  
		result = size * nmemb;  
	}  
  
	return result;  
}  

bool curl(string url)
{
	cout << "Retrieving " << url << endl;

	curlBuffer = "";

	// Our curl objects  
	CURL *curl;  
	CURLcode result;  
  
	// Create our curl handle  
	curl = curl_easy_init();  

	if (curl) {
		// Now set up all of the curl options  
		curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);  
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);  
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);  
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);  
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &curlBuffer);  
  
		// Attempt to retrieve the remote page  
		result = curl_easy_perform(curl);  
  
		// Always cleanup  
		curl_easy_cleanup(curl);  
  
		// Did we succeed?  
		if (result == CURLE_OK)	{
			cout << curlBuffer << endl;
			return true;
		} else {
			cout << "Error: [" << result << "] - " << errorBuffer;
			return false;
		}
	}  
}  


double radian(double angle)
{
	return angle / 180.0 * M_PI;
}


void drawCircle(float radius, int slice, int type = 0)
{
	static const float PI_OVER_180 = 0.0174532925;
	static float angle, step, startAngle;

	step = 360.0 / slice;

	switch(type) {
	case 0:
		glBegin(GL_TRIANGLE_FAN);
		break;
	case 1:
		glBegin(GL_LINES);
		break;
	case 2:
		glBegin(GL_LINE_STRIP);
		break;
	}

	for (angle = 0; angle <= 360.0; angle += step) {
		startAngle = angle * PI_OVER_180;
		glVertex2f(radius * cos(startAngle), radius * sin(startAngle));
	}
	glEnd();
}

string replace_all(const string &source, const string &pattern, const string &placement)
{
    string result;
    string::size_type pos_before = 0;
    string::size_type pos = 0;
    string::size_type len = pattern.size();
    while ((pos = source.find(pattern, pos)) != string::npos) {
        result.append(source, pos_before, pos - pos_before);
        result.append(placement);
        pos += len;
        pos_before = pos;
    }
    result.append(source, pos_before, source.size() - pos_before);
    return result;
}
