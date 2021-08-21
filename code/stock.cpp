#include "stock.h"



Stock::Stock(const std::string& epic, std::string& isin): epic(epic), isin(isin){}

/*----Getters----*/
std::string Stock::getEpic() const{
    return this->epic;
};

std::string Stock::getISIN() const{
    return this->isin;
};

Trade Stock::getTrade(std::string trade_ref) const{
    
    Trade const trade = this->trades.at(trade_ref);
    return  trade;
    
};


//get the VWAP for all trades of this stock
double Stock::getVWAP() const {

    double numerator = 0;
    int denominator = 0;
    
    for (auto const& [isan, trade] : this->trades)
    {
     numerator += trade.price * trade.quatity;
     denominator += trade.quatity;
    }

    if(denominator == 0)
    {
        return 0;
    }

    return numerator/denominator;
};

//get the VWAP for all trades of given type for this stock
    double Stock::getVWAP(std::string trade_type) const{

        double numerator = 0;
        int denominator = 0;
        
        for (auto const& [isan, trade] : this->trades)
        {
            if(trade.trade_type == trade_type){
                numerator += trade.price * trade.quatity;
                denominator += trade.quatity;

            }
        }

        if(denominator == 0)
        {
            return 0;
        }

        return numerator/denominator;

    };

 /*----Setters---*/
    void Stock::addTrade(std::string trade_ref, std::string trade_type, int quantity, double price){
         this->trades.insert(std::pair<const std::string, Trade>(trade_ref, {trade_ref, trade_type, quantity, price}));
        
    };   
