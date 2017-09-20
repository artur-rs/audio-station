/* ------------ AbstractClass.cpp ------------ *
 * Abstract Class for all meteo/timezone data  */

#include "audiostation.h"
#include <curl/curl.h>
#include <iostream>
#include <sstream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::size_t;

/* Function writes callback used in libcurl */
size_t BaseData::writeCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

/* Function splits string (str) by char specified in delimiter (delimiter),
 * and returns first or second token (number should be 1 or 2)*/
string BaseData::splitStr(const string str, char delimiter, int number)
{
    std::vector<string> tokens;
    std::stringstream strstream(str);
    string temp_str;
    
    while(getline(strstream,temp_str,delimiter))
    {
        tokens.push_back( temp_str );
    }
    return tokens[number - 1];
}

/* Function uses libcurl for getting data from url (url)
 * and returns callback in buffer (read_buffer)*/
string BaseData::getData(string url, string read_buffer)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read_buffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    else
    {
        cout << "CURL init error, url: " << url << endl;
        throw std::exception();
    }
    return read_buffer;
}

/* Simple JSON parser, takes out variable value 
 * specified in var from input (input) */
string BaseData::getValue(string input, string var)
{
    signed int ind = input.find(var); 
    string str = input.substr(ind);
    ind = str.find(":");
    str = str.substr(ind+1);
    ind = str.find(",");
    str = str.substr(0,ind);
    ind = str.find("}");
    if(ind != -1)
        str = str.substr(0,ind);
    do{
        ind =  str.find("\"");
        switch(ind){
            case -1: break;
            case 0: {str = str.substr(1);break;}
            default: {str = str.substr(0,ind);break;}
        }
    }while(ind != -1);
    return str;
}


