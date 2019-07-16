#ifndef TIMEDATE_H
#define TIMEDATE_H

#include <chrono>
#include <ctime>
#include <string>



namespace sfSpace
{
    namespace Time
    {
        std::string getTimeStr(std::time_t time);

        std::size_t now();

        // Returns the Julian Date for the current UT1 time
        float getJDNowUTC();

        // Converts a Gregorian date into the corresponding Julian date
        float gregorianToJulianUTC(unsigned short year, unsigned short month,
                                   unsigned short day, unsigned short hour,
                                   unsigned short minute, float second);
    }
}

#endif // TIMEDATE_H
