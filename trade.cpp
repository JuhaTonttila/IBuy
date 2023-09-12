
#include "trade.h"

#include <string>
#include <iostream>

Trade::Trade(std::string tick_) {
    ticker = tick_;
    status.open = true;
}

double Trade::buy(double bid_, int number_, double stoploss_) {
        // Update the average price per share paid
        status.avg_price = (status.avg_price*status.number + bid_*number_)/(status.number+number_);

        // Update the number of shares owned
        status.number += number_; 

        // If >0 stoploss is given, update the value
        if (stoploss_ > 0.) {
            resetStoploss(stoploss_);
        }
    return -number_*bid_;
}


double Trade::sell(double bid_, int number_) {

    if ( number_ > status.number) {
        std::cout << "Trying to sell higher number of shares than owned. The number sold will be truncated" << std::endl;
        number_ = status.number;
    }

    // Update the secured profit. 
    //profit_abs += number_*(ask_ - avg_price);

    // Update the number of shares owned
    status.number -= number_;
    status.open = (status.number > 0);
    return number_*bid_;
}

void Trade::updateValue(double close_){
    if (status.open) {
        status.value = status.number * close_;
        status.vret_abs = status.value-status.avg_price;
        status.vret_rel = (status.value-status.avg_price)/status.avg_price;
    }
    else {
        // DO NOTHING/PRINT SOMETHING?
    }
}

void Trade::checkStoploss(double low_) {
    // If the "low" is lower than stoploss (>0), initiate sell
    if (stoploss > low_ && stoploss > 0.) {
        sell(low_,status.number);  // Sell entire position
    } 
}

void Trade::resetStoploss(double stoploss_) {
    stoploss = stoploss_;
}

bool Trade::isOpen() {
    // If number of shares is zero, consider the position closed. The trade object continues to 
    // store the profit information for closed trades.
    return status.open;
}

std::string Trade::getTick() {
    return ticker;
}

TrdStatus Trade::getValue() {
    return status;
}