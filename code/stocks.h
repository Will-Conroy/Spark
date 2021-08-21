#ifndef STOCKS_H
#define STOCKS_H


#include <map>
#include "stock.h"
#include "magicVWAP.h"

using StockContainer = std::map<std::string, Stock>;


class Stocks{

  private: 
    StockContainer stocks;
    

    public:

        Stocks();


        /*----Getters---*/
        Stock& getStock(std::string isin);

        StockContainer& getStockByEPIC(std::string epic);

        void popluateFormCSV(std::istream& is, const MAGIC_VWAP::SourceColumnMapping& cols);  

};

#endif