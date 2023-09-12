#ifndef STOCK_H
#define STOCK_H

#include "candle.h"
#include <string>
#include <ctime>

class Stock {

    protected:

    public:
        std::string ticker;
        Candle price;   
        Stock(std::string ticker_, Candle& price_);

        // Return the single candle/price information for time inq_time
        Candle getPrice(tm inq_time) const;

};


#endif