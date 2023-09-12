
#include <vector>
#include <string>
#include <memory>  // unique_prt, make_unique


class IStatistic {

    public:
        int period;
        std::vector<double> value; // This will be a dynamically allocated array for the metric
        std::vector<std::string> date; // array for the corresponding dates

        double rangeSum(std::vector<double> vals, int ibeg, int iend);

        virtual void compute() = 0; 

        virtual ~IStatistic() {};
};

class SMAStatistic : public IStatistic {
    void compute() override;
};

class EMAStatistic : public IStatistic {
    void compute() override;
};

class Indicators {
    std::unique_ptr<IStatistic> ind{};                    
    public:                                                   
        void setIndicator(std::unique_ptr<IStatistic> ind_);
        void build();   
};