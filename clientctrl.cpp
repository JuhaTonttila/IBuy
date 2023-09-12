
#include "clientctrl.h"
#include "exchange.h"
#include "account.h"
#include "candle.h"
#include "trade.h"

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

ClientCtrl::ClientCtrl(Exchange* market_, Account* acc_) {
    market = market_;
    acc = acc_;
}


void ClientCtrl::assignWatchlist(std::string wl) {
    acc->setWatchlist(wl);  // Set to Account instance
}

std::vector<Candle> ClientCtrl::listMarketPrices(tm time_, std::vector<std::string>ticks_) {
    // Get watchlist from account and matching price information from 
    // the market 
    // WHAT IF SOME OF THE TICKERS ARE NOT FOUND??
    std::vector<Candle> wlist;
    for (auto ti : ticks_) {
        wlist.push_back(market->getPriceAt(ti, time_));
    }
    return wlist;
}

bool ClientCtrl::checkWatchlist() { 
    // Check if wathclist has been set
    return acc->getWatchlist().empty();
}

std::vector<std::string> ClientCtrl::getWatchlist() {
    return acc->getWatchlist();
}

void ClientCtrl::updateTradeStatus() {
    // Need somehow trade tickers from acc
    // then get closing prices from market
    std::vector<std::string> openticks = acc->getOpenTradeTicks();
    tm now = getCurrentTime();
    std::vector<Candle> price = listMarketPrices(now,openticks);
    acc->updatePositions(price);    
}

std::vector<Trade> ClientCtrl::listOpenTrades() {
    // Return a vector of open trades
    std::vector<Trade> res = acc->getPositions(true,"");
    return res;
}

std::string ClientCtrl::getCurrentDate() {
    return market->getDate();   // Gets the date for printing out
}

tm ClientCtrl::getCurrentTime() {
    return market->getTime();   // Gets the time as tm struct for processing
}

void ClientCtrl::makeTransaction(std::string tick_, int N, double bid_, double stoploss_=-1.0) {
    // If stoploss < 0, in effect the trade is not assigned a stoploss price
    // N > 0: add to/open new position, N < 0: reduce/close existing position.

    // First get the price of stock given by tick_ for current time
    tm time = market->getTime();
    Candle prc = market->getPriceAt(tick_,time);

    // Check the bid is within the candle price range
    if (prc.withinRange(time,bid_)) {
        // Make the trade
        acc->setPosition(tick_, N, bid_, stoploss_);
    }
    else {
        // Bid outside the price range, print something?
    }
}

void ClientCtrl::newMarketDay() {
    // 1. Advance date
    // 2. Get list of trade tickers from account
    // 3. Loop over the tickers and get close and low prices from market
    //    and the trade instance from the account
    // 4. For the trade call updateValue and checkStoploss
    /*
    market->advanceDate();
    std::vector<std::string> ticks_ = acc->getTradeTicks();
    for (std::string tt : ticks_) {
        // Get the market prices
        // Check if it's an open trade
        // Get the iterator pointing to that trade and update information
    }
    */
}