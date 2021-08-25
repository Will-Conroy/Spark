#include "magicVWAP.h"
#include <iostream>

/*----Getters---*/
Stock& Stocks::getStock(std::string isin){
  
  return this->stocks.at(isin);

};

StockContainer Stocks::getStockByEPIC(std::string epic){
  StockContainer stockOut;

  for (auto const& [isan, stock] : this->stocks)
    {
      if(stock.getEpic() == epic){
        stockOut.insert({isan, stock});
      }
    }
  
    return stockOut;

};

const StockContainer& Stocks::getStocks(){
  const StockContainer& temp = this->stocks;
  return temp;
};

std::map<std::pair<std::string, std::string>, double> Stocks::getWVAPByTradeComdo(){
  std::map<std::pair<std::string, std::string>, double>  out;

  for (auto const& [isan, stock] : this->stocks)
  {
      
      for (auto const& [type, trades] :  stock.getTradesByTypes())
      {
         out.insert({{type, stock.getISIN()}, cacluateVWAP(trades)});
      }
      
  }
  return out;
};




void Stocks::popluateFormCSV(std::istream& is, const MAGIC_VWAP::SourceColumnMapping &cols){
    if(!(is.good()))
        throw (std::runtime_error("Failed to open file"));

    std::string line;
    std::getline(is,line);

    while (std::getline(is, line)) {
      
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
    }
    /*
    std::cout << stocks.size() << std::endl;
    for(auto const& [isan, newStock] : stocks){
      std::cout << newStock;
    }*/
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


 std::ostream& operator<<(std::ostream& os, const Stocks& stocks){
    for(auto const& [isin, stock] : stocks.stocks){
        os << stock << std::endl;
    }
    return os;
  };
