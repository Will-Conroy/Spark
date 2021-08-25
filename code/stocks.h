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

        /*----Override---*/
        friend std::ostream& operator<<(std::ostream& os, const Stocks& stocks);


        /*----Getters---*/
        Stock& getStock(std::string isin);
        const StockContainer& getStocks();

       std::map<std::pair<const Stock&, std::string>, double> getWVAPByTradeComdo();

        StockContainer getStockByEPIC(std::string epic);

        void popluateFormCSV(std::istream& is, const MAGIC_VWAP::SourceColumnMapping &cols);  
        std::string popStringFormCSVLine(std::string& line);    
};

#endif