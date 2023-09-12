#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "stock.h"
#include "candle.h"

#include <vector>
#include <string>
#include <ctime>


class Exchange {
    // This will act as a common source data holder given to the Account instances
    // (i.e. the "model" of MCV).
    private:
        std::string exchange_data_path = "data/sp500_stocks.csv"; // Make user-configurable
        std::vector<Stock> exchange;                              // In-memory stock exchange data 
        tm time;                                       // Current in-game date || convert to TIME to make it more general?

    public:
        Exchange(std::string exchange_data_path_, tm init_time_);
        Exchange(const Exchange& p1);
        void loadMarketData();

        void advanceDate();
        std::string getDate();    // Get the current date set in the Exchange instance
        tm getTime();             // Get the current time as tm struct from the Echange instance
        const Stock& getStock(std::string tick_) const;  // Get the stock instance for a specific ticker tick
        Candle getPriceAt(std::string tick_, tm inq_time) const; // Get the price action as Candle instance for a specific ticker at specific time

};



#endif