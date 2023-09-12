#ifndef CLIENTCTRL_H
#define CLIENTCTRL_H

#include "exchange.h"
#include "account.h"
#include "candle.h"
#include "trade.h"

#include <vector>
#include <string>
#include <ctime>

// KAIKISTA FUNKTIOISTA TAALLA SIIVOTTAVA PRINTIT POIS
// Jos ctrl-funktion ei tarvi valittaa mitaan Viewille, 
// voi ctrl-funktio kutsua suoraan market and acc funktioita 

class ClientCtrl {
    // Defines the "controller" in the MCV pattern
    protected:
        Exchange* market;
        Account* acc;

    public:
        ClientCtrl(Exchange* market_, 
                   Account* acc_);
        std::vector<std::string> getWatchlist();   // Return acc.watchlist
        void assignWatchlist(std::string wl);
        bool checkWatchlist();

        std::vector<Candle> listMarketPrices(tm time_,std::vector<std::string>ticks_);  

        void updateTradeStatus();            // Update open trade stats based on current market data 
        std::vector<Trade> listOpenTrades(); // Return a vector of open trade objects

        std::string getCurrentDate();
        tm getCurrentTime();


        // JOKU RETURN VALUE NAISTAKIN ETTÄ ONNISTUKO VAI EI 
        void makeTransaction(std::string tick_, int N, double bid_, double stoploss_=-1.0);

        // Something to proceed to new day. At the same time update open trades
        // and compile and pass on information about any relevant changes
        void newMarketDay();

};

#endif