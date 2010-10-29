#ifndef _UTILITY
#define _UTILITY

#include <string>
#include <curl/curl.h>

using std::string;

// Write any errors in here  
extern char errorBuffer[CURL_ERROR_SIZE];  
// Write all expected data in here  
extern string curlBuffer;

bool curl(string url);
double radian(double angle);
void drawCircle(float radius, int slice, int type);
string replace_all(const string &source, const string &pattern, const string &placement);

#endif
