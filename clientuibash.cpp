
#include "clientui.h"    
#include "clientctrl.h"
#include "candle.h"
#include "trade.h"

#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <iomanip>
#include <ctime>

void ClientUIBash::mainmenu() {
    /*
    1 New session
    2 Something?
    0 Exit
    */
    int n;
    std::cout << " == Main menu == " << std::endl;
    std::cout << " 1 - New session " << std::endl;
    std::cout << " 2 - Setup, acount etc..." << std::endl;
    std::cout << " 0 - Exit " << std::endl;
    std::cout << " Enter selection: ";
    std::cin >> n;
    std::cin.ignore();
    std::cout << std::endl;

    switch (n) {
        case 1:
            newSession();
            break;
        case 2:
            std::cout << "Not implemented \n" << std::endl;
            mainmenu();
            break;
        case 0:
            std::cout << " Exiting " << std::endl;
            return;
    }
}


void ClientUIBash::newSession() {
    /*
    Require to first set the starting date, only the print menu
    1 Screen SP500
    2 Preselect watchlist
    0 Abort and exit to main
    */

    // Somewhere need to check that the market data is loaded and everything ok. Also add error checks to the input procedure

    int n;
    std::cout << " == New Session == " << std::endl;
    std::cout << " 1 - Screen SP500 stocks " << std::endl; // Do stock screening before going into the trading phase
    std::cout << " 2 - Set watchlist " << std::endl;    // Skip screening and just set watchlist by hand and to directly to trading
    std::cout << " 3 - Start trading cycle (watchlist must be set by selections 1 or 2)" << std::endl;
    std::cout << " 0 - Exit " << std::endl;    
    std::cout << " Enter selection: ";
    std::cin >> n;
    std::cin.ignore();
    std::cout << std::endl;
    
    switch (n) {
        case 1:
            std::cout << " Not implemented " << std::endl;
            newSession();
            break;
        case 2:
            pullWatchlist();
            newSession();
            break;
        case 3:
            if (! ctrl->checkWatchlist()) {
                std::cout << "start trading cycle. \n" << std::endl;
                trading();
            }
            else {
                std::cout << " Watchlist must be set manually or by screening" 
                            " before entering trade cycle. Press enter to continue. \n" << std::endl;
                std::cin.ignore();
                newSession();
            }
            break;
        case 0:
            mainmenu();
    }
}


void ClientUIBash::trading() {
    /*
    menu:
    1 Print current daily priceaction
    2 Print status of open positions
    3 Plotter
    4 Buy shares
    5 Sell shares
    6 Reset watchlist
    7 Proceed to next day // actions performed -> move to next player -> then next day
    0 Go back to New Session menu
    -1 Kill program
    */   
    std::string date_ = ctrl->getCurrentDate();

    std::cout << " == Trading == " << std::endl;
    std::cout << " Today is " << date_ << std::endl;
    std::cout << " 1 - Print current daily priceaction in watchlist " << std::endl; // Do stock screening before going into the trading phase
    std::cout << " 2 - Print status of open positions " << std::endl;    
    std::cout << " 3 - Plotter " << std::endl;
    std::cout << " 4 - Perform a transaction " << std::endl;
    std::cout << " 5 - Reset watchlist " << std::endl;   //???
    std::cout << " 6 - Proceed to next day " << std::endl;   // Automatically check stoplosses and update status of open trades etc
    std::cout << " 0 - Return to New Session " << std::endl;

    int n;
    std::cout << " Enter selection: ";
    std::cin >> n;
    std::cin.ignore();
    std::cout << std::endl;

    switch (n) {
        case 1:
            renderWLPrice();
            trading();
            break;

        case 2:
            renderOpenPositions();
            trading();
            break;

        case 3:

            break;

        case 4:
            makeTransaction();
            trading();
            break;
        case 6:
            trading();
            break;
    }

}

void ClientUIBash::renderHeader(std::vector<std::string> headers_) {
    for (auto hh : headers_) {
        std::cout << std::setw(spacing) << hh;
    }
    std::cout << std::endl;
}

void ClientUIBash::renderWLPrice() {
    std::vector<std::string> header_ = {"Ticker","Open","High","Low","Close"};
    tm time_ = ctrl->getCurrentTime();
    std::string date_ = ctrl->getCurrentDate();
    std::vector<std::string> wl = ctrl->getWatchlist();
    std::vector<Candle> prc = ctrl->listMarketPrices(time_,wl);
    std::cout << "DATE: " << date_ << std::endl;
    renderHeader(header_);
    auto wli = wl.begin(); auto prci = prc.begin();
    while (wli <= wl.end() && prci < prc.end()) {
        renderPriceaction(*wli,*prci);
        ++wli; ++prci;
    }
    std::cout << "Press Enter to return to menu" << std::endl;
    std::cin.ignore();
}

void ClientUIBash::renderPriceaction(std::string tick_, Candle prc) {
    std::cout << std::endl;
    std::cout << std::setw(spacing) << tick_;
    std::cout << std::setw(spacing) << prc.open[0];
    std::cout << std::setw(spacing) << prc.high[0];
    std::cout << std::setw(spacing) << prc.low[0];
    std::cout << std::setw(spacing) << prc.close[0] << std::endl;
}

void ClientUIBash::renderOpenPositions() {
    // Get the ticks of open trades
    // Get stats from trades with the ticks
    std::vector<std::string> header_ = {"Ticker","Avg price","Number","Value","Return (abs)","Return (rel)"};
    std::vector<std::string> openticks; 
    std::vector<TrdStatus> openstats;

    ctrl->listOpenTradeStats(openticks,openstats);

    // Check if the resulting vectors have anything in it and then print
    renderHeader(header_);
    if (! openticks.empty() ) {
        for (int i=0; i < openticks.size(); i++) {
            renderTradeValue(openticks[i],openstats[i]);
        }
    }
    std::cout << "Press Enter to return to menu" << std::endl;
    std::cin.ignore();
}

void ClientUIBash::renderTradeValue(std::string tick_, TrdStatus stat) {
    std::cout << std::endl;
    std::cout << std::setw(spacing) << tick_;
    std::cout << std::setw(spacing) << stat.avg_price;
    std::cout << std::setw(spacing) << stat.number;
    std::cout << std::setw(spacing) << stat.value;
    std::cout << std::setw(spacing) << stat.vret_abs;
    std::cout << std::setw(spacing) << stat.vret_rel << std::endl; 
}


void ClientUIBash::pullWatchlist(){
    std::string wl;
    std::cout << " Enter comma separated list of tickers for the watchlist: ";
    std::cin >> wl;  // Get user input
    std::cin.ignore();
    std::cout << std::endl;
    ctrl->assignWatchlist(wl);
}

void ClientUIBash::makeTransaction(){
    // Ask if its a purchase or sell
    // If pruchase, ask for ticker, bid, number and stoploss
    // IF sell, ask for ticker, ask and number

    // ADD CHECKS TO USER INPUTS

    int itype;  // 1 = buy, 2 = sell
    std::cout << "Enter type of transaction: 1 - buy, 2 - sell: ";
    std::cin >> itype;
    std::cout << std::endl;

    std::string tick;
    double bid; double ask;
    double stoploss;
    int number;

    switch (itype) {
        case 1: // buy
            std::cout << "Buy: Enter ticker ";
            std::cin >> tick;
            std::cout << "Buy: Enter bid ";
            std::cin >> bid;
            std::cout << "Buy: Enter the number of shares ";
            std::cin >> number;
            std::cout << "Buy: Enter stoploss ";
            std::cin >> stoploss;
            ctrl->makeTransaction(tick,number,bid,stoploss);
            break;
        case 2: // sell
            std::cout << "Sell: Enter ticker ";
            std::cin >> tick;
            std::cout << "Sell: Enter bid ";
            std::cin >> bid;
            std::cout << "Sell: Enter the number of shares ";
            std::cin >> number;
            ctrl->makeTransaction(tick,-1*number,ask);
            break;
    }

}

void ClientUIBash::advanceTime() {
    // Move to next day
    // update status of open trades
    // Check stoplosses
}

