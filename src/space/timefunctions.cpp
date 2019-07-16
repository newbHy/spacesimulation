#include "space/timefunctions.h"

#ifdef DEBUG
#include <iostream>
#endif // DEBUG



namespace sfSpace
{
namespace Time
{


////////////////////////////////////////////////////////////////////////////////
std::string getTimeStr(std::time_t time)
{
    char buffer [80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", std::gmtime(&time));
    return std::string(buffer);
}


////////////////////////////////////////////////////////////////////////////////
std::size_t now()
{
    return std::time(nullptr);
}


////////////////////////////////////////////////////////////////////////////////
float gregorianToJulianUTC(unsigned short year, unsigned short month,
                           unsigned short day, unsigned short hour,
                           unsigned short minute, float second)
{
    if (month < 3)
    {
        month += 12;
        year -= 1;
    }

    unsigned int B1 = year / 100;
    unsigned int B2 = B1 / 4;
    unsigned int B = 2 - B1 + B2;

    float C;
    C = (second / 60.0) + minute;
//  C = (second / 61.0) + minute // leap seconds
    C = ((C / 60.0) + hour ) / 24.0;


    unsigned int R1 = 365.25 * (year + 4716);
    unsigned int R2 = 30.6001 * (month + 1);

    return R1 + R2 + day + B - 1524.5 + C;
}


////////////////////////////////////////////////////////////////////////////////
float getJDNowUTC()
{
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::gmtime(&t);

    return gregorianToJulianUTC(1900 + tm->tm_year, tm->tm_mon + 1,
                tm->tm_mday + 1, tm->tm_hour + 1, tm->tm_min + 1, tm->tm_sec+1);
}

}
}

