/* -------------- main.cpp -------------- *
 * Main cpp file with OOP implementation. */

#include "audiostation.h"
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

Location database_pl[DB_SIZE] = 
{
    {"Bialystok","53.14" , "23.16"},    {"Bydgoszcz","53.12" , "18.01"},    {"Czestochowa","50.83" , "19.11"},  {"Gdansk","54.36" , "18.64"},    
    {"Gdynia","54.51" , "18.50"},       {"Gorzow_Wlkp","52.74" , "15.23"}, {"Katowice","50.26" , "19.02"},     {"Kielce","50.89" , "20.65"},       
    {"Krakow","50.08" , "19.92"},       {"Lublin","51.25" , "22.57"},       {"Lodz","51.77" , "19.46"},         {"Olsztyn","53.78" , "20.49"},  
    {"Opole","50.67" , "17.95"},        {"Poznan","52.40" , "16.90"},       {"Radom","21.16" , "51.42"},        {"Rzeszow","50.05" , "22.00"},      
    {"Siedlce","52.17" , "22.29"},      {"Suwalki","54.11" , "22.94"},      {"Szczecin","53.43" , "14.62"},     {"Torun","53.01" , "18.59"},        
    {"Warszawa","52.23" , "21.04"},     {"Wroclaw","51.11" , "17.03"},      {"Zakopane","49.27" , "19.97"},     {"Zielona_Gora","51.94" , "15.49"}
};
    
Location database_world[DB_SIZE] =    
{    
    {"Ankara","39.92" , "32.85"},       {"Ateny","37.98" , "23.72"},         {"Bangkok","13.75" , "100.52"},        {"Berlin","52.52" , "13.41"},     
    {"Budapeszt","47.50" , "19.04"},    {"Buenos_Aires","-34.61" , "-58.38"},{"Johannesburg","-26.20" , "28.04"},   {"Kair","30.06" , "31.25"},        
    {"Londyn","51.51" , "-0.12"},       {"Los_Angeles","34.05" , "-118.24"}, {"Madryt","40.49" , "-3.68"},          {"Meksyk","19.43" , "-99.13"},         
    {"Miami","25.77" , "-80.19"},       {"Montreal","45.51" , "-73.59"},     {"Moskwa","55.75" , "37.62"},          {"Nowy_Jork","40.71" , "-74.01"},   
    {"Oslo","10.75" , "59.91"},         {"Paryz","48.85" , "2.35"},          {"Pekin","39.91" , "116.40"},          {"Rzym","41.89" , "12.48"},          
    {"Sydney","-33.87" , "151.21"},     {"Sztokholm","59.33" , "18.06"},     {"Tokio","35.69" , "139.70"},          {"Waszyngton","38.89" , "-77.04"}
};

const int CMD_STR_SIZE = 3;
GeoLocalisationData geo_data;
WeatherData weather_data;
ForecastData forecast_data;
Database db_pl = Database("Poland",database_pl);
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

Location * checkLocation(char * arg)
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
            Location * tmp_ptr_loc = checkLocation(args[2]);
                
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
            Location * tmp_ptr_loc = checkLocation(args[2]);
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
        cout << "Error - exception catched:\n";
        std::cerr << exc.what();
        cout << endl;
        return EXIT_FAILURE;
    }      
    
    // pointers with utf8
    // location pointer in run_option (error: taking address from temporary)
    return 0;
}
