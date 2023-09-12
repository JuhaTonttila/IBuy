#ifndef STOCKDATA_H
#define STOCKDATA_H

#include "csv_parsing.h"
#include "candle.h"
#include "stock.h"
#include <string>
#include <vector>
#include <ctime>

class StockData : public CSVFile{

    protected:

        //constant indices for parsing the CSV, get from somewhere
        const int itime = 0;
        const int itick = 1;
        const int iclose = 3;
        const int ihigh = 4;
        const int ilow = 5;
        const int iopen = 6;
        const int ivol = 7;

        // Add checks for the pointers that they make sense etc.
        std::string ticker;           // Share abbreviation; if given, only the specific asset data is read. If empty, get data on all assets.
        tm tstart;           // Starting date for reading share price data 
        std::vector<Stock>* stocks;    // Add a pointer to an external Stock instance where the share price information is saved
                                      // instead of "data" in the base class. Done by processUnit

        bool isSymbol(std::string& line, std::string ticker);

    public:
        StockData(std::string& file_name, std::string ticker_, tm tstart_, std::vector<Stock>* stocks_  );

        bool filterLine(CSLine line) override;
        void skipLine() override;
        void processUnit(const CSLine& entry) override;

};  

#endif