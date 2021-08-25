// Your First C++ Program

#include <iostream>
#include "magicVWAP.h"
#include "datasets.h"






int main() {
    std::cout << "Wecome to magicVWAP" << std::endl;

    Stocks stocks;

    populatedStocksFromCommandLine(stocks);
    
    mainMenu(stocks);
     
    return 0;
}