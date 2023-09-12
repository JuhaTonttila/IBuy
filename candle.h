#ifndef CANDLE_H
#define CANDLE_H

#include <string>
#include <vector>
#include <ctime>

class Candle {
    public:
        std::string tick;
        std::vector<tm> time;
        std::vector<double> low;
        std::vector<double> high;
        std::vector<double> open;
        std::vector<double> close;
        std::vector<int> volume;

        // Constructor
        //Candle();

        // Copy constructor
        //Candle(const Candle& p1);

        // Allows to use default constructor and avoid pointers
        void init(std::string tick_, int length_);

        void append(tm time_,double (priceaction)[4], int volume_);

        // Get price information for specific time. Return a Candle instance whose contents have length 1
        Candle getCandle(tm inq_time) const;

        // Check if price prc is lower than the days low
        bool lowerThanLow(double prc);

        // Check if price prc is within the days price range
        bool withinRange(tm inq_time, double prc);
};

#endif