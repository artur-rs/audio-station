/* ------------ GeoLocalisationData.cpp ------------ *
 *  */
#include "audiostation.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

GeoLocalisationData::GeoLocalisationData()
{
    ip_url = {"https://api.ipify.org"};
    url = {"http://freegeoip.net/json/"};
}

void GeoLocalisationData::getGeoData()
{
    string read_buffer, temp_url;

    ip_address = getData(ip_url, ip_address);
    temp_url = url + ip_address;
    read_buffer = getData(temp_url,read_buffer);

    location.city = getValue(read_buffer,"city");
    location.lat = getValue(read_buffer,"lat");
    location.lon = getValue(read_buffer,"lon");
}

/* Function displays current geolocalisation. */
void GeoLocalisationData::getInfo()
{
    cout << location.city << " (Lat: " << location.lat 
            << ", Lon: " << location.lon << ")" << endl;
}
