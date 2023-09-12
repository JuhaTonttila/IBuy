
#include "exchange.h"
#include "stockdata.h"
#include "stock.h"
#include "progress.h"
#include "candle.h"
#include "nstimemanager.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <memory>
#include <ctime>

Exchange::Exchange(std::string exchange_data_path_, tm init_time_) {
    exchange_data_path = exchange_data_path_;
    // Set current date to the initial date
    time = init_time_;
    // Load the market data
    loadMarketData();
}

Exchange::Exchange(const Exchange& p1) {
    exchange_data_path = p1.exchange_data_path;
    exchange = p1.exchange;
    time = p1.time;
}

void Exchange::loadMarketData() {
    // Remember that watchlist will be an actual list at some point!
    // For now take data 2 years before the set "current" in-game date (THESE ARE NOW HARDCODED)
    tm start_io_time = time;
    TMNG::incrDays(start_io_time,-365*2);

    StockData stockdata(exchange_data_path,"",start_io_time,&exchange);
    // Make the progress tracker
    Progress input_tracker;  // This could be just a local thing and given as reference??
    input_tracker.setProgress(std::make_unique<ProgressStdout>());
    stockdata.Attach(&input_tracker);
    stockdata.readLines();
    // Clear the pointers in the StockData class??
    stockdata.close();
}

void Exchange::advanceDate() {
    TMNG::incrDays(time,1);
}

std::string Exchange::getDate() {
    // Get current date as a string in the Exchange instance
    char buff[100];
    strftime(buff, sizeof(buff), "%A %b %d %Y", &time);
    std::string s(buff);     
    return s;
}

tm Exchange::getTime() {
    return time;
}


const Stock& Exchange::getStock(std::string tick_) const {  // Why does this return a reference??
    // Get the stock instance for a specific ticker tick
    auto it = std::find_if( exchange.begin(), exchange.end(), [&] (const Stock& p) { return p.ticker == tick_; } );
    return *it;
}

Candle Exchange::getPriceAt(std::string tick_, tm inq_time) const {
    // Get the price action as Candle instance for a specific ticker at specific time

    // ERROR HANDLING FOR TICKER NOT FOUND??
    Stock st = getStock(tick_);
    Candle res = st.getPrice(inq_time);
    return res;

}