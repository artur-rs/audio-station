/* ------------ WeatherData.cpp ------------ *
 *  */

#include "Audiostation.h"
#include "Constants.h"
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

/*WeatherData::WeatherData()
{
}*/

void WeatherData::getWeatherData(Location loc)
{
    string read_buffer, temp_url;
    std::stringstream stream;
    double var;

    temp_url = ConstantsURL::weather + "lat="+ loc.lat + "&lon=" + loc.lon + "&units=metric&APPID=" + ConstantsOther::api_key; 
    read_buffer = getData(temp_url,read_buffer); //save data to buffer
    
    //var = atof(getValue(read_buffer,ConstantsJSON::temperature).c_str()); //string to double
    //temp_c =  round(var - 273.15); // double to int
    temperature = getValue(read_buffer,ConstantsJSON::temperature);

    var = atof(getValue(read_buffer,ConstantsJSON::windspeed).c_str()); //string to double
    var = roundf(3.6 * var * 100) / 100.0; //conversion to km/h and set precision to 2
    
    stream << std::fixed << std::setprecision(2) << var;
    windspeed = stream.str();

    pressure = getValue(read_buffer,ConstantsJSON::pressure);
    humidity = getValue(read_buffer,ConstantsJSON::humidity);
    icon = getValue(read_buffer,ConstantsJSON::icon);

    timezone_weather.getTimeZoneData(loc);
    weather = timezone_weather.decodeIcon(icon,true); 
}

/* Function displays current weather information. */
void WeatherData::getInfo()
{
    timezone_weather.getInfo();
    cout << "Temperature: " << temperature << " [C]"
            "\nPressure: " << pressure << " hPa"
            "\nHumidity: " << humidity <<" %"
            "\nWind speed: " << windspeed  << " km/h"
            "\nWeather: " << weather << " ( " << icon << " )" << endl << endl;
}
