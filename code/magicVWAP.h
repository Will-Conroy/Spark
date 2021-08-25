

#ifndef MAGIC_VWAP_H_
#define MAGIC_VWAP_H_
#include "input.h"
#include "stocks.h"
#include "datasets.h"
#include "menu.h"
#include <iostream>


void populatedStocksFromCommandLine(Stocks& stocks);
void displayVWAPFromCommandLineByISIN(Stocks& stocks);
void displayVWAPPerStock(Stocks& stocks);
void displayVWAPromCommandLineByISINTradeCombo(Stocks& stocks);
void mainMenu(Stocks& stocks);
void saveVWAPByStockToCSV(Stocks& stocks);
void saveVWAPByISINTradeComboToCSV(Stocks& stocks);
void saveMenu(Stocks& stocks, MAGIC_VWAP::InputFileSource fileSources);
void vwapMenu(Stocks& stocks);



#endif // MAGIC_VWAP_H_