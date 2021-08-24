

#ifndef MAGIC_VWAP_H_
#define MAGIC_VWAP_H_
#include "input.h"
#include "stocks.h"
#include "datasets.h"
#include "menu.h"
#include <iostream>

void populatedStocksFromCommandLine(Stocks& stocks);
void displayVWAPFormCommandLine();
int menu();

void mainMenu();
#endif // MAGIC_VWAP_H_