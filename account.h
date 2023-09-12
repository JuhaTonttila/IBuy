#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "trade.h"
#include "candle.h"

#include <vector>
#include <string>

class Account {
    // Should save somehow the history of account value and the total profit

    private:
        double cash = 10000.;           // Currently available cash in the account;; HARDOCDED NOW, MAKE SOME SETUP THING WHERE THIS IS SET
        std::vector<std::string> watchlist;     // Convert to list or smth!!
        std::vector<Trade> trades; // Container for active and closed positions

        std::vector<Trade>::iterator findOpenPosition(std::string tick_); // Return an iterator to an open position with ticker tick_ 
    public:
        void setWatchlist(std::string cslist);
        const std::vector<std::string>& getWatchlist() const;

        //bool isOpenPosition(std::string tick_);
        std::vector<std::string> getOpenTradeTicks() const;
        std::vector<Trade> getPositions(bool isOpen, std::string tick_) const; // Return a vector of all open or closed trades 
        void updatePositions(std::vector<Candle> price_);                                                              // if tick_ is an empty string. Otherwise return all
                                                                               // open or closed trades with specified ticker.                                  

        // Return some fail/success value from these two so they dont have to print out anything??
        void setPosition(std::string tick_, int N, double bid_, double stoploss_=-1.0); // Add/reduce positions in active trades/open new trade.
                                                                                        // Add/open new position if N is positive, reduce/close if negative.
                                                                                        // For added/new positions stoploss is set or updated if given positive value.


};

#endif