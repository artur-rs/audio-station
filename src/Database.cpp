/* ------------ Database.cpp ------------ *
 *  */

#include "Audiostation.h"
#include "Constants.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;

/*Database::~Database()
{

}*/

string Database::createSeparator(const char c, int num)
{
    string str;

    for(int i = 1; i <= num; i++)
    {
        str += c;
    }

    return str;
}

string Database::fillRow(string tmp, const int width)
{
    int diff = width - tmp.size();
    int mod = diff % 2;

    string filledRow = createSeparator(ROW_FILL, diff/2)
            + tmp + createSeparator(ROW_FILL, diff/2 + mod);

    return filledRow;
}

void Database::printRow(const Location * ptr)
{
    cout << COL_SEPARATOR << fillRow(ptr->city,COL_WIDTH)
        << COL_SEPARATOR << fillRow((ptr+1)->city,COL_WIDTH)
        << COL_SEPARATOR << fillRow((ptr+2)->city,COL_WIDTH)
        << COL_SEPARATOR << fillRow((ptr+3)->city,COL_WIDTH)
        << COL_SEPARATOR << endl;
}

void Database::printDatabase()
{
    string separator = createSeparator(TABLE_SEPARATOR, TABLE_WIDTH);
    string header_row = fillRow(header, TABLE_WIDTH-2);

    cout << separator << endl;
    cout << COL_SEPARATOR << header_row << COL_SEPARATOR << endl;
    cout << separator << endl;

    for (int i = 0; i < ROWS; i++)
    {
       printRow(data);
       data += COLUMNS;
    }
    cout << separator << endl << endl;
}
