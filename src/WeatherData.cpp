/* ------------ WeatherData.cpp ------------ *
 *  */

#include "Audiostation.h"
#include "Constants.h"
#include <string>
#include <cstdlib>
#include <cmath>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

WeatherData::WeatherData()
{
    temp_c = {0};
    windspeed = {0.0};
}

void WeatherData::getWeatherData(Location loc)
{
    string read_buffer, temp_url;
    double var;

    temp_url = ConstantsURL::weather + "lat="+ loc.lat + "&lon=" + loc.lon + "&APPID=" + ConstantsOther::api_key; 
    read_buffer = getData(temp_url,read_buffer); //save data to buffer
    
    var = atof(getValue(read_buffer,ConstantsJSON::temperature).c_str()); //string to double
    temp_c =  round(var - 273.15); // double to int

    var = atof(getValue(read_buffer,ConstantsJSON::windspeed).c_str()); //string to double
    windspeed = roundf(3.6 * var * 100) / 100.0; //conversion to km/h and set precision to 2

    pressure = getValue(read_buffer,ConstantsJSON::pressure);
    humidity = getValue(read_buffer,ConstantsJSON::humidity);
    icon = getValue(read_buffer,ConstantsJSON::icon);

    timezone_weather.getTimeZoneData(loc);
    weather = timezone_weather.decodeIcon(icon,timezone_weather.checkSunset()); 
}

/* Function displays current weather information. */
void WeatherData::getInfo()
{
    timezone_weather.getInfo();
    cout << "Temperature: " << temp_c << " [C]"
            "\nPressure: " << pressure << " hPa"
            "\nHumidity: " << humidity <<" %"
            "\nWind speed: " << windspeed  << " km/h"
            "\nWeather: " << weather << " ( " << icon << " )" << endl << endl;
}
