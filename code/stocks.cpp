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




/*
  Caculates and formates the WVAP for each unqine trade stock combo.


 @returns std::map<std::pair<ISIN, trade type> VWAP>
    std::map<std::pair<std::string, std::string>
    where the key is a pair of string the first string being the ISIN, second trade type.
    The Value is the VWAP

*/

std::map<std::pair<std::string, std::string>, double> Stocks::getWVAPByTradeComdo(){
  std::map<std::pair<std::string, std::string>, double>  out;

  for (auto const& [isan, stock] : this->stocks)
  {
      
      for (auto const& [type, trades] :  stock.getTradesByTypes())
      {
         out.insert({{stock.getISIN(), type}, cacluateVWAP(trades)});
      }
      
  }
  return out;
};

/*
  Given input steam and cols need to be filled.
  It runs though each line  of the CSV and populate the stocks.

  @param istream
    isteam for the file that is going to be read in

  @param Cols
  SourceColumnMapping of what cols are in the file, so what data they can use to populate
  
*/


void Stocks::popluateFormCSV(std::istream& is, const MAGIC_VWAP::SourceColumnMapping &cols){
    if(!(is.good()))
        throw (std::runtime_error("Failed to open file"));

    std::string line;
    std::getline(is,line);

    while (std::getline(is, line)) {
      
        std::string epic = popStringFormCSVLine(line);
        std::string isan = popStringFormCSVLine(line);
        Stock stock;
        
        //Check to see if the stock is already there, if it not creates a stock with the correct ISIN and EPIC
        try{
          stock = getStock(isan);
        }
        catch (const std::out_of_range& oor) {
          stock = Stock(epic, isan);
          stocks.insert({isan, stock});
        }
        //Now that it knows there is the correct stocks, it addeds a new trade
        getStock(isan).addTrade({popStringFormCSVLine(line), popStringFormCSVLine(line), atoi( popStringFormCSVLine(line).c_str() ), atof( popStringFormCSVLine(line).c_str() )}); 
    }
    /*
    std::cout << stocks.size() << std::endl;
    for(auto const& [isan, newStock] : stocks){
      std::cout << newStock;
    }*/
};  

/*
  Given refence to a CSV line in the form of a string. 
  this method, take the first value of the string removing it form the string and returning it.

  @param line
    a refence to a CSV line in the form of a string

  @return 
    the first value in the CSV line
  
*/


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
