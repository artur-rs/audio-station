/* ------------ ForecastData.cpp ------------ *
 *  */

#include "audiostation.h"
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <array>

using std::string;
using std::cout;
using std::endl;

ForecastData::ForecastData()
{
    url = "http://api.openweathermap.org/data/2.5/forecast/daily?";
}

void ForecastData::getForecastData(Location loc)
{
    string read_buffer;
    string temp_url = url + "lat="+ loc.lat + "&lon=" + loc.lon + "&units=metric&cnt=7&appid=" + api_key;
    
    read_buffer = getData(temp_url, read_buffer);

    for (int i = 0; i < A_SIZE; i++)
    {	// save temperature for 7 days (string to double & round double & cast to int)
        temps_day[i] = round(atof(separateData(read_buffer, "day", i).c_str()));
        temps_night[i] = round(atof(separateData(read_buffer, "night", i).c_str()));
        icons[i] = separateData(read_buffer, "icon", i);
        dates[i] = separateData(read_buffer, "dt", i);
        dates[i] = convertTime(dates[i]);
    }
    
    timezone_forecast.getTimeZoneData(loc);
}

/* Function converts from unix timestamp string to formatted string (YYYY-MM-DD)*/
string ForecastData::convertTime(string str)
{
    char date[20], timestamp[20];
    struct std::tm *tm;

    strcpy(timestamp, str.c_str());
    time_t t = (time_t) strtol(timestamp,NULL,10);
    tm = localtime(&t);
    strftime(date, sizeof(date), "%Y-%m-%d", tm);

    return str = date;
}

/* Same as BaseClass separate method (getValue), but with array implementation.
 * Variable i represents current loop iteration. */
string ForecastData::separateData(string input, string var, int i)
{
    int ints[A_SIZE], j = 0;
    for (int i = -1; (i = input.find(var, i + 1)) != -1; ) {
        ints[j]=i;
        j++;
    }
    string str = input.substr(ints[i]);
    ints[i] = str.find(":");
    str = str.substr(ints[i]+1);
    ints[i] = str.find(",");
    str = str.substr(0,ints[i]);
    do{
        ints[i] =  str.find("\"");
        switch(ints[i]){
        case -1: break;
        case 0: {str = str.substr(1);break;}
        default: {str = str.substr(0,ints[i]);break;}
        }
    } while(ints[i] != -1);

    return str;
}

/* Function returns formatted string for table displayed in getInfo() function.
 * string tmp is input string which format depends on, int var represents left (1)
   or right (2) side where retutned string should be displayed.*/
string ForecastData::getVariant(string tmp, int var)
{
    switch(tmp.length())
    {
        case 1: if(var == 1) return " |     "; else return "   |     "; break; 
        case 2: if(var == 1) return " |    "; else return "   |    "; break;
        case 3: if(var == 1) return " |   "; else return "   |   "; break;       
    }
}

/* Function displays table with forecast information. */
void ForecastData::getInfo()
{
    string separator = {"--------------------------------------------------------"};
    string tmp;

    cout << separator << endl;
    cout << "|            |  Temperature [C]  |                     |" << endl
         << "|    Date    |-------------------|       Weather       |" << endl
         << "|            |   Day   |  Night  |                     |" << endl;
    cout << separator << endl;       
    
    for(int i = 0; i < A_SIZE; i++)
    {
        tmp = std::to_string(temps_day[i]);
        cout << "| " << dates[i];
        cout << getVariant(tmp,1) << temps_day[i]; 
        
        tmp = std::to_string(temps_night[i]);         
        cout << getVariant(tmp,2) << temps_night[i] << "   | " 
             << timezone_forecast.decodeIcon(icons[i], timezone_forecast.checkSunset()) << " |" << endl;
    }
    cout << separator << endl << endl;
}


