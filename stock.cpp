#include "stock.h"
#include "candle.h"
#include <string>
#include <ctime>

Stock::Stock(std::string ticker_, Candle& price_) {
    ticker = ticker_;
    price = price_;
}

Candle Stock::getPrice(tm inq_time) const {
    Candle res = price.getCandle(inq_time);
    return res;
}

