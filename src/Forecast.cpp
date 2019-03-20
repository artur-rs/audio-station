/* ------------ ForecastData.cpp ------------ *
 *  */
#include "Audiostation.h"
#include "Constants.h"
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

/*ForecastData::ForecastData()
{

}*/

void ForecastData::getForecastData(Location loc)
{
    string read_buffer;
    string temp_url = ConstantsURL::forecast + "lat="+ loc.lat + "&lon=" + loc.lon
            + "&units=metric&cnt=7&appid=" + ConstantsOther::api_key;

    read_buffer = getData(temp_url, read_buffer);

    for (int i = 0; i < A_SIZE; i++)
    {	// save temperature for 7 days (string to double & round double & cast to int)
        temps_day[i] = round(atof(separateData(read_buffer, ConstantsJSON::day_temp, i).c_str()));
        temps_night[i] = round(atof(separateData(read_buffer, ConstantsJSON::night_temp, i).c_str()));
        icons[i] = separateData(read_buffer, ConstantsJSON::icon, i);
        dates[i] = separateData(read_buffer, ConstantsJSON::date, i);
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


string ForecastData::createSeparator(const char c, int num)
{
    string str;

    for(int i = 1; i <= num; i++)
    {
        str += c;
    }

    return str;
}

string ForecastData::fillRow(string tmp, const int width)
{
    int diff = width - tmp.size();
    int mod = diff % 2;

    string filledRow = createSeparator(ROW_FILL, diff/2)
            + tmp + createSeparator(ROW_FILL, diff/2 + mod);

    return filledRow;
}

/* Function displays table with forecast information. */
void ForecastData::getInfo()
{
    string separator = createSeparator(TABLE_SEPARATOR, FORECAST_TABLE_WIDTH);
    string tmp;

    cout << separator << endl;
    // HEADER - first row
    cout << COL_SEPARATOR << createSeparator(ROW_FILL, DATE_COL_WIDTH) << COL_SEPARATOR
         << fillRow(ConstantsForecast::header2,2*TEMPERATURE_COL_WIDTH+1)  << COL_SEPARATOR
         << createSeparator(ROW_FILL, WEATHER_COL_WIDTH) << COL_SEPARATOR << endl;
    // HEADER - second row
    cout << COL_SEPARATOR << fillRow(ConstantsForecast::header1, DATE_COL_WIDTH) << COL_SEPARATOR
         << createSeparator(TABLE_SEPARATOR, 2*TEMPERATURE_COL_WIDTH+1)  << COL_SEPARATOR
         << fillRow(ConstantsForecast::header5, WEATHER_COL_WIDTH) << COL_SEPARATOR << endl;
    // HEADER - third row
    cout << COL_SEPARATOR << createSeparator(ROW_FILL, DATE_COL_WIDTH) << COL_SEPARATOR
         << fillRow(ConstantsForecast::header3,TEMPERATURE_COL_WIDTH)  << COL_SEPARATOR
         << fillRow(ConstantsForecast::header4,TEMPERATURE_COL_WIDTH)  << COL_SEPARATOR
         << createSeparator(ROW_FILL, WEATHER_COL_WIDTH) << COL_SEPARATOR << endl;
    cout << separator << endl;

    for(int i = 0; i < A_SIZE; i++)
    {
        tmp = std::to_string(temps_day[i]);
        cout << COL_SEPARATOR << fillRow(dates[i], DATE_COL_WIDTH) << COL_SEPARATOR
             << fillRow(tmp,TEMPERATURE_COL_WIDTH) << COL_SEPARATOR;

         tmp = std::to_string(temps_night[i]);
        cout << fillRow(tmp,TEMPERATURE_COL_WIDTH) << COL_SEPARATOR
             << fillRow(timezone_forecast.decodeIcon(icons[i],false), WEATHER_COL_WIDTH)
             << COL_SEPARATOR << endl;
    }
    cout << separator << endl << endl;
}
