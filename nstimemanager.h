#ifndef NSTIMEMANAGER_H
#define NSTIMEMANAGER_H

#include <string>
#include <vector>

namespace TMNG {

    const std::string tfmt = "%Y-%m-%d %H:%M:%S%z";  // String time format in the input data

    tm getTm(std::string time, std::string fmt);    // Create a tm instance with given string time and format
    size_t toSeconds(tm tmtime);

    size_t nearestTime(std::vector<tm> times, tm inq_time);
    bool isBefore(tm tnow, tm tref);
    bool isAfter(tm tnow, tm tref);

    void incrDays(tm &tmtime, int dd);


}

#endif