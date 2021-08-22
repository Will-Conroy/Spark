#ifndef STOCKS_H
#define STOCKS_H


#include <map>
#include "stock.h"
#include "magicVWAP.h"
#include "datasets.h"

using StockContainer = std::map<std::string, Stock>;


class Stocks{

  private: 
    StockContainer stocks;
    

    public:

        Stocks() = default;


        /*----Getters---*/
        Stock& getStock(std::string isin);

        StockContainer& getStockByEPIC(std::string epic);

        void popluateFormCSV(std::istream& is, const MAGIC_VWAP::SourceColumnMapping &cols);  
        std::string popStringFormCSVLine(std::string& line);
};

#endif