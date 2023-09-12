#include "stockdata.h"
#include "csv_parsing.h"
#include "stock.h"
#include "nstimemanager.h"

#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <limits>

// StockData
// Constructor
StockData::StockData(std::string& file_name, std::string ticker_, tm tstart_, std::vector<Stock>* stocks_) : CSVFile(file_name){
    ticker = ticker_;
    tstart = tstart_;
    stocks = stocks_;
}

void StockData::skipLine() {
    fs.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}


bool StockData::filterLine(CSLine line) {
    // tickerin pitais voida olla stringi missa useita osakkeita pilkulla erotettuna,
    // -> pilko ne jossain vektoriksi ja isSymbol tarkistukseen any. Oletetaan kuitenkin,
    // etta osakkeen koko aikasarja on aina yhtenaisena input tiedostossa
    bool b1 = (isSymbol(line.buff[itick],ticker) || ticker.empty());
    tm bufftime = TMNG::getTm(line.buff[itime],TMNG::tfmt);
    bool b2 = (TMNG::isAfter(bufftime,tstart)); 
    return (b1 && b2);
}

bool StockData::isSymbol(std::string& line, std::string ticker) {
    std::size_t found = line.find(ticker);
    return (found != std::string::npos);
}


void StockData::processUnit(const CSLine& entry) {
    
    // at this point entry is one step ahead of data, so skip the very first call
    if (!data.empty()) { 
        
        CSLine& last = data.back();

        // If all data on previous share has been read (ticker changes),
        // make new Stock item. The content is copied there and "data" is cleared.
        if ( last.buff[itick] != entry.buff[itick] ) {

            int size = data.size(); 

            Candle price_tmp; // Use this intermediate variable to first gather the
                              // values. The data may contain missing values and this allows to filter them out...
            price_tmp.init(size);


            int i = 0;
            for (auto dt : data) {
                if (std::any_of( dt.buff.begin(), dt.buff.end(), [](std::string i){return i.empty();} )) {
                    continue;  // Line contains missing data so don't try to save it
                }

                double priceaction[4] = {std::stod(dt.buff[ilow]), 
                                        std::stod(dt.buff[ihigh]),
                                        std::stod(dt.buff[iopen]),
                                        std::stod(dt.buff[iclose])};

                int intvol = std::stoi(dt.buff[ivol]);
                
                tm bftime = TMNG::getTm(dt.buff[itime],TMNG::tfmt);
                price_tmp.append(bftime,priceaction,intvol);
        
                ++i;
            }

            // Set the new stock item
            Stock newstock(last.buff[itick],price_tmp);
            stocks->push_back(newstock);
            data.clear();  // Clear the existing input data from CSVFile buffer as its no longer needed
        }

    }
    
}
