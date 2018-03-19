/* ------------ GeoLocalisationData.cpp ------------ *
 *  */
#include "Audiostation.h"
#include "Constants.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

GeoLocalisationData::GeoLocalisationData()
{
    ip_url = ConstantsURL::ip;
}

void GeoLocalisationData::getGeoData()
{
    string read_buffer, temp_url;

    read_buffer = getData(ip_url, ip_address);
    temp_url = ConstantsURL::localisation + ip_address;
    read_buffer = getData(temp_url,read_buffer);

    location.city = getValue(read_buffer,ConstantsJSON::city);
    location.lat = getValue(read_buffer,ConstantsJSON::latitude);
    location.lon = getValue(read_buffer,ConstantsJSON::longitude);
}

/* Function displays current geolocalisation. */
void GeoLocalisationData::getInfo()
{
    cout << location.city << " (Lat: " << location.lat 
            << ", Lon: " << location.lon << ")" << endl;
}
