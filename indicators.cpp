
#include "indicators.h"

#include <iostream>
#include <utility>
#include <memory>


void Indicators::setIndicator(std::unique_ptr<IStatistic> ind_) {
    ind = std::move(ind_); 
}

void Indicators::build() {
    if (ind) ind->compute(); 
}


double IStatistic::rangeSum(std::vector<double> vals, int ibeg, int iend){
    double rslt = 0.;
    for (auto it = vals.begin()+ibeg; it != vals.begin()+iend; ++it) {
        rslt+=*it;
    }
    return rslt;
}

void SMAStatistic::compute(){
    std::cout << "SMA computing" << std::endl;

}

void EMAStatistic::compute(){
    std::cout << "EMA computing" << std::endl;
}