/* ------------ TimeZoneData.cpp ------------ *
 *  */

#include "audiostation.h"
#include <string>
#include <cstring>
#include <iostream>
#include <ctime>

using std::string;
using std::cout;
using std::endl;

TimeZoneData::TimeZoneData() 
{
    url = "http://api.geonames.org/timezoneJSON?";
}

void TimeZoneData::getTimeZoneData(Location loc)
{
    string read_buffer, temp_url, date_time;
    
    temp_url = url + "lat="+ loc.lat +"&lng=" + loc.lon
            + "&username=" + username;
    read_buffer = getData(temp_url,read_buffer);
    
    sunrise = splitStr(getValue(read_buffer,"sunrise"),' ',2);
    sunset = splitStr(getValue(read_buffer,"sunset"),' ',2);
    date_time = getValue(read_buffer,"time\"");
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
    if (a == "01d" && !check)  str = "     Słonecznie    ";
    else if (a == "01n" || (a == "01d" && check))  str = "    Bezchmurnie    ";
    else if (a == "02d" || a == "03d" || a == "02n" || a == "03n") 
        str = "Lekkie zachmurzenie";
    else if (a == "10d" || a == "10n") str = "    Lekki deszcz   ";
    else if (a == "04d" || a == "04n") str = " Duże zachmurzenie ";
    else if (a == "09d" || a == "09n")  str = "   Opady deszczu   ";
    else if (a == "11d" || a == "11n") str = " Burza z piorunami ";
    else if (a == "13d" || a == "13n") str = "    Opady śniegu   ";
    else str = "       Mglisto     ";
    
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

