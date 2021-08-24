// Your First C++ Program

#include <iostream>
#include "magicVWAP.h"
#include "datasets.h"






int main() {
    std::cout << "Wecome to magicVWAP" << std::endl;

    Stocks stocks;

    populatedStocksFromCommandLine(stocks);
    

    //std::cout << stocks << std::endl;
    mainMenu();
    
    return 0;
}