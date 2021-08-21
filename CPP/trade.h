#ifndef TRADE_H_
#define TRADE_H_
#include <string>
#include "stock.h"


class Trade {

private:
    //Stock that is being traded
    Stock stock;
    
    //Unique code for each transaction
    std::string trade_ref;

    //The type of trade
    std::string trade_type;

    //The number of shares traded
    int quatity;

    //The price at which the shares were traded (Not sure what currency but guessing pounds?)
    double price;

    //Volume weighted average
    double vwap;
 



public:
  

};

#endif // AREA_H_
