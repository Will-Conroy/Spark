#ifndef STOCK_H_
#define STOCK_H_
#include <string>
#include <map>
#include "trade.h"

class Stock {

private:
    //Short name for the stock
    std::string epic;

    //Long unique name for the stock
    std::string isin;

    //Volume weighted average
    double vwap;

    /*All trades of this stock
    Key = the trades trade refrence as a string
    Value = a Trade object storing all infornation*/
    std::map<std::string, Trade> trades;



public:
  

};

#endif // AREA_H_