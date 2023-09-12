#ifndef TRADE_H
#define TRADE_H

#include <string>

struct TrdStatus {
    int number = 0;     // Number of shares
    double avg_price = 0; // Average price per share paid
    double value = 0.;      // Current value of investment
    double vret_abs = 0.;     // Current value return level (absolute)
    double vret_rel = 0.;      // Current value return (per cent)
    bool open = false;
};


class Trade{

    private:
        // Stored information for a trade. I don't have the data or 
        // willigness to simulate the trading process, so the "bid" and
        // "ask" are going to be taken as the buy and sell prices.
        std::string ticker;  
        double stoploss = -1.;  // stoploss, if stock price hits here, this is going to be the sell price
        TrdStatus status;       // Struct holding the current value status of the trade 
        // THESE WILL REQUIRE SOME FIRST IN-FIRST OUT tracking!!
        double profit_abs = 0.;  // Absolute secured profit from sold shares
        double profit_rel = 0.;  // Per cent secured profit from sold shares (relative to avg_price)
        // Add total return, i.e. secured profit + current value return

    public:
        // Constructor - call in preparation to buying an asset
        Trade(std::string tick_);

        // Buy shares. Return money spent
        double buy(double bid_, int number_, double stoploss_=-1);

        // Sell shares. Return the sold value in cash
        double sell(double ask_, int number_);

        // Update current investment value (based on the closing price)
        void updateValue(double close_);

        // Check if asset hit a stoploss and initiate sell if it did (based on the low price)
        void checkStoploss(double low_);

        // Set new stoploss price for an open position
        void resetStoploss(double stoploss_);

        // Check if the position is open or closed (for closed position number of shares is 0)
        bool isOpen();

        // Get the ticker for this trade 
        std::string getTick();

        // Get the current value and profit level
        TrdStatus getValue();

};


#endif

