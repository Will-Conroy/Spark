// Your First C++ Program

#include <iostream>
#include "magicVWAP.h"
#include "datasets.h"


int main() {
    std::cout << "Running!\n";
    Stocks stocks;
  
    const MAGIC_VWAP::SourceColumnMapping &cols = MAGIC_VWAP::InputFiles::MARKET_TRADE.COLS;

    InputFile input("datasets/market_trades.csv");
    stocks.popluateFormCSV(input.open(), cols);





    return 0;
}