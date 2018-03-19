/* -------------- main.cpp -------------- *
 * Main cpp file with OOP implementation. */

#include "Audiostation.h"
#include "Constants.h"
#include <cstdlib>
#include <string>
#include <string.h>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <array>

using std::string;
using std::cout;
using std::endl;

const int CMD_STR_SIZE = 3;
GeoLocalisationData geo_data;
WeatherData weather_data;
ForecastData forecast_data;
Database db_pl = Database("Poland", database_pl);
Database db_wr = Database("World ", database_world);

void textToSpeech(const char * ptr)
{
    char command[270] = {"./speech.sh "}; 
    strcat(command, ptr); 
  
    try 
    {
        cout << "Processing text to speech..." << endl;
        system(command);
        cout << "Done!" << endl;
    } 
    catch(const std::exception &exc) 
    {
        cout << "Error - exception catch:\n";
        std::cerr << exc.what();
        cout << endl;
    }
}

void setText(string astr[])
{   
    astr[1] = "Godzina " + weather_data.getTime() + "." + weather_data.getWeather();
    astr[1] += "Temperatura wynosi " + std::to_string(weather_data.getTemp());
    
    switch(weather_data.getTemp())
    {
        case -1:
        case 1: astr[1] += " stopień Celsjusza."; break;
        case -2:
        case -3:
        case -4:
        case 2:
        case 3:
        case 4: astr[1] += " stopnie Celsjusza."; break;
        default: astr[1] += " stopni Celsjusza."; break;
    }

    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << weather_data.getWindSpeed();
    
    astr[2] = "Prędkość wiatru " + stream.str() + " metrów na sekundę.";
    astr[2] += "Ciśnienie atmosferyczne wynosi " + weather_data.getPressure() + " hektopaskali.";
    astr[2] += " Wilgotność powietrza sięga " + weather_data.getHumidity() + " procent.";
}

const Location * checkLocation(char * arg)
{   
    for (int i = 0; i < DB_SIZE; i++)
    {
        if (strcmp(database_pl[i].city.c_str(),arg) == 0) 
            return &database_pl[i];
        else if (strcmp(database_world[i].city.c_str(),arg) == 0) 
            return &database_world[i]; 
        else if (i == DB_SIZE - 1) 
            return nullptr;
    }
}

void run_command(int counter, char * args[])
{
    switch(counter)
    {
        case 2: 
        {
            if(strcmp(args[1],"help") == 0) 
            {
                cout << "Available commands:\n"
                        "- database - shows location database.\n"
                        "- weather - current weather for geolocation.\n"
                        "- weather speech - current weather in audio mode for geolocation.\n"
                        "- weather [city] - current weather for city from database.\n"
                        "- weather [city] speech- current weather in audio mode for city from database.\n"
                        "- forecast - forecast data for geolocation.\n"
                        "- forecast [city] - forecast data for city from database.\n";
            }
            else if(strcmp(args[1],"database") == 0) 
            {
                db_pl.printDatabase();
                db_wr.printDatabase(); 
            }
            else if(strcmp(args[1],"weather") == 0) 
            {
                geo_data.getGeoData();
                //Location * loc_ptr = &geo_data.getLocation();
                weather_data.getWeatherData(geo_data.getLocation());
                cout << "\nCurrent weather for: ";
                geo_data.getInfo();
                weather_data.getInfo();
            }
            else if(strcmp(args[1],"forecast") == 0) 
            {
                geo_data.getGeoData();
                //Location * loc_ptr = &geo_data.getLocation();
                forecast_data.getForecastData(geo_data.getLocation());
                cout << "\nWeather forecast for: "; 
                geo_data.getInfo();
                forecast_data.getInfo();
            }
            else {cout << "Incorrect argument, check \"help\" for commands.\n";} 
            break;
        }
        case 3:
        {
            const Location * tmp_ptr_loc = checkLocation(args[2]);
                
            if(strcmp(args[1],"weather") == 0 && tmp_ptr_loc != nullptr) 
            {
                weather_data.getWeatherData(*tmp_ptr_loc);
                cout << "\nCurrent weather for: ";
                cout << tmp_ptr_loc->city << " (Lat: " << tmp_ptr_loc->lat 
                << ", Lon: " << tmp_ptr_loc->lon << ")" << endl;
                weather_data.getInfo();
            }
            else if(strcmp(args[1],"forecast") == 0 && tmp_ptr_loc != nullptr) 
            {
                forecast_data.getForecastData(*tmp_ptr_loc);
                cout << "\nWeather forecast for: "; 
                cout << tmp_ptr_loc->city << " (Lat: " << tmp_ptr_loc->lat 
                << ", Lon: " << tmp_ptr_loc->lon << ")" << endl;
                forecast_data.getInfo();
            }
            else if(strcmp(args[1],"weather") == 0 && strcmp(args[2],"speech") == 0) 
            {
                geo_data.getGeoData();
                weather_data.getWeatherData(geo_data.getLocation());
                string astr[CMD_STR_SIZE];
                
                astr[0] = "Pogoda dla miasta " + geo_data.getLocation().city; 
                setText(astr);
                
                for (int i = 0; i < CMD_STR_SIZE; i++)
                {
                    const char * cptr = astr[i].c_str();
                    textToSpeech(cptr);
                }
            }
            else {cout << "Incorrect argument[s], check \"help\" for commands or \"database\" for cities.\n";} 
            break;
        }
        case 4:
        {
            const Location * tmp_ptr_loc = checkLocation(args[2]);
            if(strcmp(args[1],"weather") == 0 && tmp_ptr_loc != nullptr && strcmp(args[3],"speech") == 0 ) 
            {
                weather_data.getWeatherData(*tmp_ptr_loc);
                string astr[CMD_STR_SIZE];
                
                astr[0] = "Pogoda dla miasta " + tmp_ptr_loc->city; 
                setText(astr);
                
                for (int i = 0; i < CMD_STR_SIZE; i++)
                {
                    const char * cptr = astr[i].c_str();
                    textToSpeech(cptr);
                }
            }
            else {cout << "Incorrect argument[s], check \"help\" for commands or \"database\" for cities.\n";} 
            break;
        }
        default: {cout << "Incorrect number of arguments, check \"help\" for commands.\n"; break;}
    }
}

int main(int argc, char * argv[])
{
    try
    {
        run_command(argc,argv);
    }
    catch(const std::exception &exc)
    {
        cout << "Error - exception catch:\n";
        std::cerr << exc.what();
        cout << endl;
        return EXIT_FAILURE;
    }      
    
    // pointers with utf8
    // location pointer in run_option (error: taking address from temporary)
    return 0;
}
