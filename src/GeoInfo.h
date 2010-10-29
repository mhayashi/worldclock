#ifndef _GEO_INFO
#define _GEO_INFO

#include <string>

using std::string;

class GeoInfo
{
public:
	GeoInfo(string _city);

	float lat;
	float lng;
	//string localtime;
	int offset;
	string address;

private:
	bool getLatLng();
	bool getTimeZone();
	bool parseLatLng();
	bool parseTimeZone();

	//bool curl(string url);
	//bool parseXML();

	string slat;
	string slng;
	string city;
	//char wr_buf[MAX_BUF+1];
	//int  wr_index;


	// Write any errors in here
	//static char errorBuffer[CURL_ERROR_SIZE];  

	// Write all expected data in here
	//static string buffer;

};

#endif
