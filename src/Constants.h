
#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
using std::string;

namespace ConstantsURL
{
    const string weather        = "http://api.openweathermap.org/data/2.5/weather?";
    const string localisation   = "http://freegeoip.net/json/";
    const string ip             = "https://api.ipify.org";
    const string timezone       = "http://api.geonames.org/timezoneJSON?";
    const string forecast       = "http://api.openweathermap.org/data/2.5/forecast/daily?";
}

namespace ConstantsOther
{
    const string username       = "artur560";
    const string api_key        = "3981018313f7c5839c599b868ea745a8";  
}

namespace ConstantsJSON 
{
    const string temperature    = "temp";
    const string windspeed      = "speed";
    const string pressure       = "pressure";
    const string humidity       = "humidity";
    const string icon           = "icon";
    const string city           = "city";
    const string latitude       = "lat";
    const string longitude      = "lon";
    const string sunrise        = "sunrise";
    const string sunset         = "sunset";
    const string time           = "time\"";
    const string day_temp       = "day";
    const string night_temp     = "night";
    const string date           = "dt";   
}

namespace ConstantsWeather
{
    const string sunny          = "     Słonecznie    ";
    const string clear_sky      = "    Bezchmurnie    ";
    const string few_clouds     = "Lekkie zachmurzenie";
    const string broken_clouds  = " Duże zachmurzenie ";
    const string shower_rain    = " Przelotny deszcz  "; 
    const string rain           = "   Opady deszczu   ";
    const string thunderstorm   = " Burza z piorunami ";
    const string snow           = "    Opady śniegu   ";
    const string mist           = "       Mglisto     ";
}

namespace ConstantsIcon
{
    const string clear_sky_d      = "01d";
    const string clear_sky_n      = "01n";
    const string few_clouds_d     = "02d";
    const string few_clouds_n     = "02n";
    const string scatt_clouds_d   = "03d";
    const string scatt_clouds_n   = "03n";
    const string broken_clouds_d  = "04d";
    const string broken_clouds_n  = "04n";
    const string shower_rain_d    = "09d";
    const string shower_rain_n    = "09n";
    const string rain_d           = "10d";
    const string rain_n           = "10n";
    const string thunderstorm_d   = "11d";
    const string thunderstorm_n   = "11n";
    const string snow_d           = "13d";
    const string snow_n           = "13n";
    const string mist_d           = "50d";
    const string mist_n           = "50n";  
}

const int DB_SIZE = 24;

const Location database_pl[DB_SIZE] = 
{
    {"Bialystok","53.14" , "23.16"},    {"Bydgoszcz","53.12" , "18.01"},    {"Czestochowa","50.83" , "19.11"},  {"Gdansk","54.36" , "18.64"},    
    {"Gdynia","54.51" , "18.50"},       {"Gorzow_Wlkp","52.74" , "15.23"},  {"Katowice","50.26" , "19.02"},     {"Kielce","50.89" , "20.65"},       
    {"Krakow","50.08" , "19.92"},       {"Lublin","51.25" , "22.57"},       {"Lodz","51.77" , "19.46"},         {"Olsztyn","53.78" , "20.49"},  
    {"Opole","50.67" , "17.95"},        {"Poznan","52.40" , "16.90"},       {"Radom","21.16" , "51.42"},        {"Rzeszow","50.05" , "22.00"},      
    {"Siedlce","52.17" , "22.29"},      {"Suwalki","54.11" , "22.94"},      {"Szczecin","53.43" , "14.62"},     {"Torun","53.01" , "18.59"},        
    {"Warszawa","52.23" , "21.04"},     {"Wroclaw","51.11" , "17.03"},      {"Zakopane","49.27" , "19.97"},     {"Zielona_Gora","51.94" , "15.49"}
};
    
const Location database_world[DB_SIZE] =    
{    
    {"Ankara","39.92" , "32.85"},       {"Ateny","37.98" , "23.72"},         {"Bangkok","13.75" , "100.52"},        {"Berlin","52.52" , "13.41"},     
    {"Budapeszt","47.50" , "19.04"},    {"Buenos_Aires","-34.61" , "-58.38"},{"Johannesburg","-26.20" , "28.04"},   {"Kair","30.06" , "31.25"},        
    {"Londyn","51.51" , "-0.12"},       {"Los_Angeles","34.05" , "-118.24"}, {"Madryt","40.49" , "-3.68"},          {"Meksyk","19.43" , "-99.13"},         
    {"Miami","25.77" , "-80.19"},       {"Montreal","45.51" , "-73.59"},     {"Moskwa","55.75" , "37.62"},          {"Nowy_Jork","40.71" , "-74.01"},   
    {"Oslo","10.75" , "59.91"},         {"Paryz","48.85" , "2.35"},          {"Pekin","39.91" , "116.40"},          {"Rzym","41.89" , "12.48"},          
    {"Sydney","-33.87" , "151.21"},     {"Sztokholm","59.33" , "18.06"},     {"Tokio","35.69" , "139.70"},          {"Waszyngton","38.89" , "-77.04"}
};

#endif /* CONSTANTS_H */

