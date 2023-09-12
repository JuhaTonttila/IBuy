

#include "clientui.h"
#include "clientctrl.h"
#include "exchange.h"
#include "account.h"
#include "trade.h"  // for testing
#include "nstimemanager.h"

#include <iostream>
#include <string>    // for testing
#include <vector>    // for testing
#include <memory>
#include <ctime>


void testAccount() {

    // Standalone test for class Account (and trade)
    // Buy & sell dummy stocks and test methods to retrieve data/stats

    
    Account account_1;

    /*
    Will build the trade vector as follows:
    AAA - closed
    BBB - open
    CCC - closed
    AAA - open
    CCC - open    
    */

    account_1.buyShares("AAA",1,10.,9.9);
    account_1.sellShares("AAA",1,11.);
    account_1.buyShares("BBB",1,20.,19.9);
    account_1.buyShares("CCC",1,5.,4.9);
    account_1.sellShares("CCC",1.,6.);
    account_1.buyShares("AAA",1,12.,11.9);
    account_1.buyShares("CCC",1,7.,6.9);
    account_1.sellShares("DDD",1,5.); // should print error

    std::vector<Trade> test; 
    test = account_1.getPositions(true,"");
    std::cout << "open trades" << std::endl;
    for (auto t : test) {
        std::cout << t.getTick() << std::endl;
    }

    test = account_1.getPositions(false,"");
    std::cout << "closed trades" << std::endl;
    for (auto t : test) {
        std::cout << t.getTick() << std::endl;
    }

    test = account_1.getPositions(false,"CCC");
    std::cout << "selected closed trades" << std::endl;
    for (auto t : test) {
        std::cout << t.getTick() << std::endl;
    }





}


void runIBuy(){



    tm init_time = TMNG::getTm("2022-01-03","%Y-%m-%d");


    // Initialize the (model) data holders
    Exchange market("data/sp500_stocks.csv",init_time);

    
    Account account_1;

    // Start the controller
    ClientCtrl ctrl(&market, &account_1);

    // Initialize user interface
    ClientUI client;
    client.setCui(std::make_unique<ClientUIBash>());

    client.init(&ctrl);
    client.mainmenu();
 
}




int main() {

    testAccount();
    //runIBuy();



    /*
    std::string file_name = "data/sp500_stocks.csv";

    std::vector<Stock> sp500_market;

    StockData sp500(file_name,"ABBV","2023-01-05",&sp500_market);
    // Make the progress tracker
    ProgressStdout* input_tracker = new ProgressStdout();
    sp500.Attach(input_tracker);
    sp500.readLines();
    sp500.close();
    delete input_tracker;
    //std::cout << content[0].buff[0] << content[0].buff[1] << content[0].buff[2] << std::endl;

    
    std::cout << "size " << sp500_market.size() << std::endl;
    for (auto tick : sp500_market) {
        std::cout << tick.ticker << " " <<  tick.price.time.size() << std::endl;
    }

    for (int i=0; i < 6; ++i) {
        std::cout << sp500_market[0].ticker <<" " << sp500_market[0].price.close[i] << std::endl;
    }
    */
    /*
    sp500_market[0].getSMA(2);
    */

   //std::vector<Indicator> inds;


    /*
    Indicators SMAs;
    SMAs.setIndicator(std::make_unique<SMAStatistic>());
    SMAs.build();

    Indicators EMAs;
    EMAs.setIndicator(std::make_unique<EMAStatistic>());
    */
}
