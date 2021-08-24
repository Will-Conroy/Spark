#include "magicVWAP.h"
#include <iostream>

/*----Getters---*/
Stock& Stocks::getStock(std::string isin){
  
  return this->stocks.at(isin);

};

StockContainer& Stocks::getStockByEPIC(std::string epic){
  StockContainer stockOut;
  for (auto const& [isan, stock] : this->stocks)
    {
      if(stock.getEpic() == epic){
        stockOut.insert({isan, stock});
      }
    }
  
    return stockOut;

};



void Stocks::popluateFormCSV(std::istream& is, const MAGIC_VWAP::SourceColumnMapping &cols){
  if(cols.size() < 3)
        throw std::out_of_range("Not enough columns");

    if(!(is.good()))
        throw (std::runtime_error("Failed to open file"));

    //reading first line which is just the name of cols
    //As coursework states that this should remain constant, throw away the line
    std::string line;
    std::getline(is,line);

    while (std::getline(is, line)) {
        //std::cout << line << '\n';
        std::string epic = popStringFormCSVLine(line);
        std::string isan = popStringFormCSVLine(line);
        Stock stock;
        
        try{
          stock = getStock(isan);
        }
        catch (const std::out_of_range& oor) {
          stock = Stock(epic, isan);
          stocks.insert({isan, stock});
        }
 

        
        getStock(isan).addTrade({popStringFormCSVLine(line), popStringFormCSVLine(line), atoi( popStringFormCSVLine(line).c_str() ), atof( popStringFormCSVLine(line).c_str() )});
        //std::cout << stock.getTrades().size() << std::endl;
        
        
    }
    std::cout << stocks.size() << std::endl;
    for(auto const& [isan, newStock] : stocks){
      std::cout << newStock;
    }
};  

std::string Stocks::popStringFormCSVLine(std::string& line){

      if(line.find(",") == std::string::npos){
          std::string out = line;
          line = "";
          return out;
      }

      std::size_t pos = line.find(",");
      std::string out = line.substr(0,pos);

      //deletes outputted variable
      line = line.erase (0,pos+1);

      return out;
  };
