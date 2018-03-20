/* ------------ audiostation.h ------------ *
 *     Header for audiostation project.     */

#ifndef AUDIOSTATION_H_
#define AUDIOSTATION_H_

#include <string>
#include <array>
using std::string;
//------------------------------------------------------------------------------

struct Location
{
    string city; 
    string lat;
    string lon;
};

const int A_SIZE = 7;
typedef std::array<string, A_SIZE> str_array;
typedef std::array<int, A_SIZE> int_array;

//------------------------------------------------------------------------------
class BaseData
{
protected:
    string getValue(string input, string var);
    string getData(string url , string read_buffer);
    string splitStr(const string str, char delimiter, int number);
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);
public:
    BaseData() {}
    virtual void getInfo() = 0; //pure virtual function
    virtual ~BaseData() {};
};
//------------------------------------------------------------------------------
class GeoLocalisationData : public BaseData
{
private:
    string ip_address, ip_url;
    Location location;
public:
    GeoLocalisationData();
    ~GeoLocalisationData() {}
    virtual void getInfo();
    void getGeoData();
    Location getLocation() {return location;}
};
//------------------------------------------------------------------------------
class TimeZoneData : public BaseData
{
public:
    string sunrise, sunset, time, date;
    bool checkSunset();
    string decodeIcon(string a, bool check, bool synth);
    TimeZoneData(){}
    ~TimeZoneData() {}
    void getTimeZoneData(Location loc);
    virtual void getInfo();
};
//------------------------------------------------------------------------------
class WeatherData : public BaseData
{
private:
    int temp_c;
    double windspeed;
    string icon, humidity, pressure, weather;
    TimeZoneData timezone_weather;
public:
    WeatherData();
    ~WeatherData() {}
    const string & getTime() {return timezone_weather.time;}
    const int & getTemp() {return temp_c;}
    const double & getWindSpeed() {return windspeed;}
    const string & getHumidity() {return humidity;}
    const string & getPressure() {return pressure;}
    const string & getWeather() {return weather;}
    virtual void getInfo();
    void getWeatherData(Location loc);
};
//------------------------------------------------------------------------------
class ForecastData : public BaseData
{
private:
    int_array temps_day, temps_night;
    str_array icons, dates;
    TimeZoneData timezone_forecast;
    string convertTime(string str);
    string createSeparator(const char c, int num);
    string fillRow(string tmp, const int width);
    string separateData(string input, string var, int i);   
public:
    ForecastData() {}
    ~ForecastData() {}
    void getForecastData(Location loc);
    virtual void getInfo();
};
//------------------------------------------------------------------------------
class Database
{
private:
    const string header;
    const Location * data; 
    string createSeparator(const char c, int num);
    string fillRow(string tmp, const int width);
    void printRow(const Location * ptr);
public:
    Database(string str, const Location loc_array[]) : header(str) {data = &loc_array[0];}
    ~Database() {}
    void printDatabase();
};
#endif
