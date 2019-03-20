/* -------------- Audiostation.cpp -------------- *
 * Main cpp file with OOP implementation. */

#include "Audiostation.h"
#include "Constants.h"
#include <cstdlib>
#include <string>
#include <string.h>
#include <iostream>
#include <array>

using std::string;
using std::cout;
using std::endl;

GeoLocalisationData geo_data;
WeatherData weather_data;
ForecastData forecast_data;
Database db_pl = Database("Poland", database_pl);
Database db_wr = Database("World ", database_world);

void textToSpeech(const char * ptr) {
    char command[200] = {"./speech.sh "};

    try {
        cout << "Processing text to speech..." << endl;
        strcat(command, ptr);
        cout << "Text size: " << (unsigned) strlen(command) << endl;
        system(command);
        cout << "Done!" << endl;
    } catch (const std::exception &exc) {
        cout << "Error - exception catch:\n";
        std::cerr << exc.what();
        cout << endl;
    }
}

void setText(string astr[]) {
    astr[1] = "Godzina " + weather_data.getTime() + ". " + weather_data.getWeather() + ".";
    astr[1] += " Temperatura wynosi " + weather_data.getTemp();

    switch (stoi(weather_data.getTemp())) {
        case -1:
        case 1: astr[1] += " stopień Celsjusza.";
            break;
        case -2:
        case -3:
        case -4:
        case 2:
        case 3:
        case 4: astr[1] += " stopnie Celsjusza.";
            break;
        default: astr[1] += " stopni Celsjusza.";
            break;
    }

    astr[2] = "Prędkość wiatru " + weather_data.getWindSpeed() + " metrów na sekundę.";
    astr[2] += "Ciśnienie atmosferyczne wynosi " + weather_data.getPressure() + " hektopaskali.";
    astr[2] += " Wilgotność powietrza sięga " + weather_data.getHumidity() + " procent.";
}

const Location * checkLocation(char * arg) {
    for (int i = 0; i < DB_SIZE; i++) {
        if (strcmp(database_pl[i].city.c_str(), arg) == 0)
            return &database_pl[i];
        else if (strcmp(database_world[i].city.c_str(), arg) == 0)
            return &database_world[i];
        else if (i == DB_SIZE - 1)
            return nullptr;
    }
}

bool isFound(const char * s, const char * x) {
    string str = s;
    if (str.find(x) != std::string::npos)
        return true;
    else return false;
}

void run_cmd(int counter, char * args[]) {
    bool cmd_h, cmd_d, cmd_w, cmd_f, cmd_s;

    if (isFound(args[1], "-")) {
        cmd_h = isFound(args[1], "h");
        cmd_d = isFound(args[1], "d");
        cmd_w = isFound(args[1], "w");
        cmd_f = isFound(args[1], "f");
        cmd_s = isFound(args[1], "s");
    }
    else counter = 0;

    switch (counter) {
        case 2:
        {
            if (cmd_h) { // ----------------------------------------------- HELP
                cout << ConstantsCommands::help;
            }
            else if (cmd_d) { // -------------------------------------- DATABASE
                db_pl.printDatabase();
                db_wr.printDatabase();
            }
            else if (cmd_w || cmd_s || cmd_f) {
                geo_data.getGeoData();

                if(cmd_w) { // ----------------------------------------- WEATHER
                    weather_data.getWeatherData(geo_data.getLocation());
                    cout << ConstantsCommands::headline1;
                    geo_data.getInfo();
                    weather_data.getInfo();
                }
                if (cmd_f) { // --------------------------------------- FORECAST
                    forecast_data.getForecastData(geo_data.getLocation());
                    cout << ConstantsCommands::headline2;
                    geo_data.getInfo();
                    forecast_data.getInfo();
                }
                if (cmd_s) { // ----------------------------------------- SPEECH
                    weather_data.getWeatherData(geo_data.getLocation());
                    string astr[MAX_CMD_NUM];
                    astr[0] = ConstantsCommands::speech1 + geo_data.getLocation().city;
                    setText(astr);

                    for (int i = 0; i < MAX_CMD_NUM; i++) {
                        const char * cptr = astr[i].c_str();
                        textToSpeech(cptr);
                    }
                }
            }
            else { // ---------------------------------------------------- ERROR
                cout << ConstantsCommands::error1;
            }
            break;
        }
        case 3:
        {
            const Location * tmp_ptr_loc = checkLocation(args[2]);

            if ((cmd_w || cmd_f || cmd_s) && (tmp_ptr_loc != nullptr)) {

                if(cmd_w) { // ----------------------------------------- WEATHER
                    weather_data.getWeatherData(*tmp_ptr_loc);
                    cout << ConstantsCommands::headline1;
                    cout << tmp_ptr_loc->city << " (Lat: " << tmp_ptr_loc->lat
                    << ", Lon: " << tmp_ptr_loc->lon << ")" << endl;
                    weather_data.getInfo();
                }
                if (cmd_f) { // --------------------------------------- FORECAST
                    forecast_data.getForecastData(*tmp_ptr_loc);
                    cout << ConstantsCommands::headline2;
                    cout << tmp_ptr_loc->city << " (Lat: " << tmp_ptr_loc->lat
                        << ", Lon: " << tmp_ptr_loc->lon << ")" << endl;
                    forecast_data.getInfo();
                }
                if(cmd_s) { // ------------------------------------------ SPEECH
                    weather_data.getWeatherData(*tmp_ptr_loc);
                    string astr[MAX_CMD_NUM];

                    astr[0] = ConstantsCommands::speech1 + tmp_ptr_loc->city;
                    setText(astr);

                    for (int i = 0; i < MAX_CMD_NUM; i++) {
                        const char * cptr = astr[i].c_str();
                        textToSpeech(cptr);
                    }
                }
            }
            else { // ---------------------------------------------------- ERROR
                cout << ConstantsCommands::error2;
            }
            break;
        }
        default:
        {          // -------------------------------------------------- DEFAULT
            cout << ConstantsCommands::error3;
            break;
        }
    }
}

int main(int argc, char * argv[]) {
    try {
        run_cmd(argc, argv);
    }
    catch (const std::exception &exc) {
        cout << "Error - exception catch:\n";
        std::cerr << exc.what();
        cout << endl;
        return EXIT_FAILURE;
    }
    // location pointer in run_option (error: taking address from temporary)
    // espeak test
    // speech options, S = full / s = condensed
    // speech text optimization
    return 0;
}
