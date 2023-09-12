
#include "account.h"
#include "csv_parsing.h"
#include "trade.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


void Account::setWatchlist(std::string cslist) {
    CSLine parser(cslist);
    watchlist = parser.buff; // Should this have a getter...
}

const std::vector<std::string>& Account::getWatchlist() const {
    return watchlist;
}

void Account::setPosition(std::string tick_, int N, double bid_, double stoploss_=-1.0) {
// Add/reduce positions in active trades/open new trade.
// Add/open new position if N is positive, reduce/close if negative.
// For added/new positions stoploss is set or updated if given positive value.

    double amount=0.;

    std::vector<Trade>::iterator trit = findOpenPosition(tick_);

    if (N > 0) {
        if ( trit == trades.end() ) {
            // Open position not found, create new
            trades.push_back(Trade(tick_));
            trit = trades.end()-1;
        }
        trit->buy(bid_,N,stoploss_);
    }
    else if (N < 0) {
        if ( trit != trades.end() ) {
            amount = trit->sell(bid_,-1*N);
        } 
        else {
            // Some error code?
        }
    }
    cash+=amount;
}

/* IS THIS NEEDED ANYWHERE
bool Account::isOpenPosition(std::string tick_) {
    bool res = false;
    // Scan through the trades vector and see if a trade with tick_ exists and is open
    for (auto tr : trades) {
        res = ( res || (tr.getTick() == tick_ && tr.isOpen()) );   // USE ANY_OF
    }
    return res;
}
*/

std::vector<std::string> Account::getOpenTradeTicks() const {
    // Get a vector of tickers for currently open trades.
    // Open trades tickers are unambiguous.
    std::vector<std::string> res;
    for (auto tr : trades) {
        if ( tr.isOpen() ) res.push_back(tr.getTick());
    }
    return res;
}

std::vector<Trade> Account::getPositions(bool isOpen, std::string tick_) const {
    // Return a vector of all open or closed trades if tick_ is an empty string. 
    // Otherwise return all open or closed trades with specified ticker.   
    std::vector<Trade> res;
    for (auto tr : trades) {
        if ( (isOpen == tr.isOpen()) && (tr.getTick() == tick_ || tick_.empty()) ) {
            res.push_back(tr);
        }
    }
    return res;
}

void Account::updatePositions(std::vector<Candle> price_) {
    for (auto pr : price_ ) {
        std::vector<Trade>::iterator it = findOpenPosition(pr.tick);
        if (it != trades.end()) it->updateValue(pr.close.back());        
    }
}

std::vector<Trade>::iterator Account::findOpenPosition(std::string tick_) {
    // Return an iterator to an open position with ticker tick_ (open positions are unique).
    std::vector<Trade>::iterator it = std::find_if( trades.begin(), trades.end(), [&](Trade& p)
                                                    { 
                                                        if (p.getTick() == tick_ && p.isOpen()) {
                                                            return true;
                                                        }
                                                        else {
                                                            return false;
                                                        }
                                                    } );
    return it;  // returns last if open position for tick_ not found
}
