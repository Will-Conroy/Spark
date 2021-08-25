

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

//MENUS
//main menu here the user can exit the program, load new data and calcuate VWAP
void mainMenu(Stocks& stocks);
//form here user can save the data they have jsut displayed in a given formate
void saveMenu(Stocks& stocks, MAGIC_VWAP::InputFileSource fileSources);

//form here a user can calcaute the VWAP of the loaded data in 2 ways
//First unique stock, trade refence combo
//Second for each unique stock
void vwapMenu(Stocks& stocks);


//saves caculated VWAP in to CSV, with headings EPIC, ISIN, VWAP
void saveVWAPByStockToCSV(Stocks& stocks);

//saves caculated VWAP in to CSV, with headings ISIN, Trade refencem VWAP
void saveVWAPByISINTradeComboToCSV(Stocks& stocks);




#endif // MAGIC_VWAP_H_