#include "nstimemanager.h"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <ctime>
#include <cstring>

tm TMNG::getTm(std::string time, std::string fmt) {
    tm tm;
    std::memset(&tm,0,sizeof(struct tm));
    strptime(time.c_str(), fmt.c_str(), &tm);
    tm.tm_isdst = -1;
    return tm;
}

size_t TMNG::toSeconds(tm tmtime) {
    return mktime(&tmtime);
}

void TMNG::incrDays(tm &tmtime, int dd) {
    const time_t S_IN_D = 24*3600;
    time_t sec = toSeconds(tmtime);
    sec += S_IN_D * dd ;
    tmtime = *localtime(&sec);
}

bool TMNG::isBefore(tm tnow, tm tref) {  
    // Check if tnow is before tref
    size_t stnow = toSeconds(tnow);
    size_t stref = toSeconds(tref);
    return ( difftime(stnow,stref) < 0. ) ;
}

bool TMNG::isAfter(tm tnow, tm tref) {
    // Check if tnow is after tref
    size_t stnow = toSeconds(tnow);
    size_t stref = toSeconds(tref);
    return ( difftime(stnow,stref) > 0. ) ;    
}

size_t TMNG::nearestTime(std::vector<tm> times, tm inq_time) {
    // Get the index for the nearest neighbour in times for inq_time
    size_t sinq = toSeconds(inq_time);
    std::vector<size_t> diff;
    diff.reserve(times.size());
    for (tm tt : times) diff.push_back( std::abs(difftime(toSeconds(tt),sinq)) );
    auto it = std::min_element(diff.begin(),diff.end());
    return std::distance(diff.begin(),it);
}