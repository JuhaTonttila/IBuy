
#include "candle.h"
#include "nstimemanager.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <ctime>

// Candle:
// Constructor
//Candle::Candle() {
//}
// Copy constructor
//Candle::Candle(const Candle& p1) {
//    *this = p1;
//}

void Candle::init(std::string tick_, int length_) {
    // Reserve vector resources to make extensions faster
    low.reserve(length_);  // Anticipated size
    high.reserve(length_);  
    open.reserve(length_);  
    close.reserve(length_);  
    volume.reserve(length_);              
    time.reserve(length_);
    tick = tick_;
}


void Candle::append(tm time_, double (priceaction)[4], int volume_) {
    time.push_back(time_);
    low.push_back(priceaction[0]);
    high.push_back(priceaction[1]);
    open.push_back(priceaction[2]);
    close.push_back(priceaction[3]);
    volume.push_back(volume_);    
}

Candle Candle::getCandle(tm inq_time) const {
    Candle res; 
    res.init(tick,1);
    size_t idx = TMNG::nearestTime(time,inq_time);
    double prc[4] = {low[idx],high[idx],open[idx],close[idx]};
    res.append(time[idx],prc,volume[idx]);
    return res;
}




/*
double Candle::getPriceVariation() {
    // Get days price variation
    return high-low;
}
bool Candle::lowerThanLow(double prc) {
    // Check if price prc is lower than the days low
    return ( prc <= low);
}
*/
bool Candle::withinRange(tm inq_time, double prc) {
    // Check if price prc is within the price range at given time
    Candle cdl = getCandle(inq_time);
    return ( prc <= cdl.high[0] && prc >= cdl.low[0]);
}

