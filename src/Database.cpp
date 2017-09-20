/* ------------ Database.cpp ------------ *
 *  */

#include "audiostation.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;

/*Database::~Database() 
{
    
}*/

string Database::getVariant(string tmp, int var)
{
    switch(tmp.length())
    {
        case 4: if(var == 1) {return "     ";} else {return "     ";} break; 
        case 5: if(var == 1) {return "    ";} else {return "     ";} break;
        case 6: if(var == 1) {return "    ";} else {return "    ";} break;  
        case 7: if(var == 1) {return "   ";} else {return "    ";} break; 
        case 8: if(var == 1) {return "   ";} else {return "   ";} break;
        case 9: if(var == 1) {return "  ";} else {return "   ";} break;
        case 10: if(var == 1) {return "  ";} else {return "  ";} break; 
        case 11: if(var == 1) {return " ";} else {return "  ";} break;
        case 12: if(var == 1) {return " ";} else {return " ";} break;
    }
}

void Database::printRow(Location * ptr)
{
    cout << "|" << getVariant(ptr->city,1) << ptr->city << getVariant(ptr->city,2)
             << "|" << getVariant((ptr+1)->city,1) << (ptr+1)->city << getVariant((ptr+1)->city,2)
             << "|" << getVariant((ptr+2)->city,1) << (ptr+2)->city << getVariant((ptr+2)->city,2)
             << "|" << getVariant((ptr+3)->city,1) << (ptr+3)->city << getVariant((ptr+3)->city,2) 
             << "|" << endl;
}

void Database::printDatabase()
{
    std::string separator = "-------------------------------------------------------------";
    const int rows = DB_SIZE/4;
    Location * ptr = data;
    
    cout << separator << endl;
    cout << "|                           " << header << "                          |" << endl;
    cout << separator << endl;

    for (int i = 0; i < rows; i++)
    {  
       printRow(ptr); 
       ptr += 4;
    }
    cout << separator << endl << endl;
}
        
