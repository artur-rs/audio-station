/* ------------ TimeZoneData.cpp ------------ *
 *  */

#include "Audiostation.h"
#include "Constants.h"
#include <string>
#include <cstring>
#include <iostream>
#include <ctime>

using std::string;
using std::cout;
using std::endl;
using namespace ConstantsIcon;

/*TimeZoneData::TimeZoneData() 
{
    
}*/

void TimeZoneData::getTimeZoneData(Location loc)
{
    string read_buffer, temp_url, date_time;
    
    temp_url = ConstantsURL::timezone + "lat="+ loc.lat +"&lng=" + loc.lon
            + "&username=" + ConstantsOther::username;
    read_buffer = getData(temp_url,read_buffer);
    
    sunrise = splitStr(getValue(read_buffer,ConstantsJSON::sunrise),' ',2);
    sunset = splitStr(getValue(read_buffer,ConstantsJSON::sunset),' ',2);
    date_time = getValue(read_buffer,ConstantsJSON::time);
    date = splitStr(date_time, ' ', 1);
    time = splitStr(date_time, ' ', 2);
}

/* Boolean function that checks if sun was set. */
bool TimeZoneData::checkSunset()
{   
    int h1, h2, m1, m2;
    h1 = std::stoi(time.substr(0,2));
    h2 = std::stoi(sunset.substr(0,2));
    m1 = std::stoi(time.substr(3,2));
    m2 = std::stoi(sunset.substr(3,2));
    
    if (h1 > h2) return true;
    else if(h1 == h2 && m1 >= m2) return true;
    else return false;
}

/* Method decodes icon from html response in JSON data and returns
 * string with weather information. */
string TimeZoneData::decodeIcon(string a, bool check)
{   
    string str;
    if (a == clear_sky_d && !check)  
        str = ConstantsWeather::sunny;
    else if (a == clear_sky_n || (a == clear_sky_d && check))  
        str = ConstantsWeather::clear_sky;
    else if (a == few_clouds_d || a == few_clouds_n || a == scatt_clouds_d || a == scatt_clouds_n) 
        str = ConstantsWeather::few_clouds;
    else if (a == rain_d || a == rain_n) 
        str = ConstantsWeather::rain;
    else if (a == broken_clouds_d || a == broken_clouds_n) 
        str = ConstantsWeather::broken_clouds;
    else if (a == shower_rain_d || a == shower_rain_n)  
        str = ConstantsWeather::shower_rain;
    else if (a == thunderstorm_d || a == thunderstorm_n) 
        str = ConstantsWeather::thunderstorm;
    else if (a == snow_d || a == snow_n) 
        str = ConstantsWeather::snow;
    else if (a == mist_d || a == mist_n)
        str = ConstantsWeather::mist;
    
    return str;
}

/* Function displays current date and time info. */
void TimeZoneData::getInfo()
{
    cout << "Date: " << date
        << "\nTime: " << time 
        << "\nSunrise: " << sunrise
        << "\nSunset: " << sunset << endl;
}

