#include <tinyxml.h>
#include <string>  
#include <iostream>  
#include <stdexcept>

#include "GeoInfo.h"
#include "Utility.h"

//using std::string;
using std::cout;
using std::endl;
using std::runtime_error;


GeoInfo::GeoInfo(string _city):city(_city)
{
	getLatLng();
	getTimeZone();
}

bool GeoInfo::getLatLng()
{
	string url("http://maps.google.com/maps/api/geocode/xml?sensor=false&address=");
	url += city;
	if (!curl(url)) { throw runtime_error("Cannot download lat & lng"); }
	if (!parseLatLng()) { throw runtime_error("Cannot parse lat & lng"); }

	return true;
}

bool GeoInfo::parseLatLng()
{
	TiXmlDocument doc;
	const char* pReturn = doc.Parse(curlBuffer.c_str());
	if (!pReturn) return false;

	TiXmlNode *result = doc.FirstChild("GeocodeResponse")->FirstChild("result");
	if (!result) return false;

	address = result->FirstChildElement("formatted_address")->GetText();
	if (address == "") return false;

	TiXmlNode *location = result->FirstChild("geometry")->FirstChild("location");
	if (!location) return false;
	slat = location->FirstChildElement("lat")->GetText();
	slng = location->FirstChildElement("lng")->GetText();
	
	lat = atof(slat.c_str());
	lng = atof(slng.c_str());
	
	cout << "lat: " << lat << ", lng: "<< lng << endl;
	return true;
}

bool GeoInfo::getTimeZone()
{
	string url("http://www.earthtools.org/timezone/");
	url = url + slat + "/" + slng;
	if (!curl(url)) { return false; }
	if (!parseTimeZone()) { return false; }

	return true;
}

bool GeoInfo::parseTimeZone()
{
	TiXmlDocument doc;
	const char* pReturn = doc.Parse(curlBuffer.c_str());

	TiXmlNode *timezone = doc.FirstChild("timezone");
	//localtime = timezone->FirstChildElement("localtime")->GetText();
	offset = atoi(timezone->FirstChildElement("offset")->GetText());
	cout << "localtime: " << localtime << endl;
	return true;
}
