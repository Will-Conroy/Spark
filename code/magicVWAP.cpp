#include "magicVWAP.h"
#include "datasets.h"
#include "input.h"
#include "menu.h"
#include <string>
#include <fstream>



void populatedStocksFromCommandLine(Stocks& stocks){
    
    bool populated = false;

    do{
        std::cout << "What file do you want to read in:" << std::endl;
       
        for(unsigned int i = 0; i < MAGIC_VWAP::InputFiles::NUM_DATASETS; i++){
            std::cout << MAGIC_VWAP::InputFiles::DATASETS[i].FILE << '(' << i << ')' << MENU::DIVIDER;
        }
        std::cout << std::endl;
        std::string fileNum;
        std::cin >> fileNum;

        try
        {
            int intFileNum = stoi(fileNum);
            InputFile input(MAGIC_VWAP::InputFiles::DATASET_FILE_DIR + MAGIC_VWAP::InputFiles::DATASETS[intFileNum].FILE);
            stocks.popluateFormCSV(input.open(), MAGIC_VWAP::InputFiles::DATASETS[intFileNum].COLS);
            std::cout << MAGIC_VWAP::InputFiles::DATASETS[intFileNum].FILE << ": succefuly populated" << std::endl;
            populated = true;
        }
        catch(std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
        }catch(...){
            std::cout << "Invlaid responce, please enter an int that corraspons to a file" << std::endl;
        }
        
    }while(!populated);

};


void displayVWAPFromCommandLineByISIN(Stocks& stocks){
    std::cout << std::endl << "ISIN:" << std::endl;
    std::string isin;
    std::cin >> isin;
    std::cout << stocks.getStock(isin).getVWAP();
    std::cout << std::endl;
};

void displayVWAPPerStock(Stocks& stocks){
    
    std::cout << std::endl << " EPIC " << MENU::DIVIDER << MENU::autoDividers(17, "ISIN") << MENU::autoDividers(11, "VWAP") << std::endl;
    
    for(const auto& [isin, stock] : stocks.getStocks()){
        std::cout << stock.getEpic() << MENU::DIVIDER << isin << MENU::DIVIDER << MENU::autoDividers(11, std::to_string(stock.getVWAP()))<< std::endl << std::endl;
    }
    std::cout << std::endl;
};

void displayVWAPromCommandLineByISINTradeCombo(Stocks& stocks){
    std::string lastISIN = "";
    std::cout << std::endl << MENU::autoDividers(17, "ISIN") << MENU::autoDividers(15, "Trade Type") << MENU::autoDividers(11, "VWAP") << std::endl;
    for(const auto& [info, vwap]: stocks.getWVAPByTradeComdo()){
        const auto& [isin, trade] = info;
        if(isin != lastISIN){
            std::cout << std::endl;
            lastISIN = isin;
        }
        std::cout << isin << MENU::DIVIDER  << MENU::autoDividers(15, trade) << MENU::autoDividers(10, std::to_string(vwap)) << std::endl;
    }
    std::cout << std::endl;
};

void mainMenu(Stocks& stocks){
    bool vaildInput = false;
    do{
        std::string userInput = MENU::getInputFromUser(MENU::MAIN);
        try{
             switch(MENU::getOption(MENU::MAIN.OPTIONS, userInput)) {
                case MENU::EXIT:
                    break;

                case MENU::LOAD:
                    populatedStocksFromCommandLine(stocks);
                    mainMenu(stocks);
                    break;

                case MENU::CALCULATE_VWAP:
                    vwapMenu(stocks);
                    break;

                default:
                    throw(std::out_of_range("Missing menu option"));
                    break;
            }

            vaildInput = true;
        }catch(std::out_of_range& e){
            std::cout << e.what() << std::endl;
        }

    }while(!vaildInput);
};



void vwapMenu(Stocks& stocks){

    bool vaildInput = false;
    do{   
        std::string userInput = MENU::getInputFromUser(MENU::VWAP);
     
        try{
             switch(MENU::getOption(MENU::VWAP.OPTIONS, userInput)) {
                case MENU::EXIT:
                    mainMenu(stocks);
                    break;
                    
                case MENU::TRADE_TYPE:
                    displayVWAPromCommandLineByISINTradeCombo(stocks);
                    saveMenu(stocks, MAGIC_VWAP::InputFiles::VWAP_BY_ISIN_TRADE_COMBO);
                    break;
                   
                case MENU::ISIN:
                    displayVWAPPerStock(stocks);
                    saveMenu(stocks, MAGIC_VWAP::InputFiles::VWAP_BY_STOCK);
                    break;
                default:
                    throw(std::out_of_range("Missing menu option"));
                    break;
            }

            vaildInput = true;
        }catch(std::out_of_range& e){
            std::cout << e.what() << std::endl;
        }
    }while(!vaildInput);
}



void saveMenu(Stocks& stocks, MAGIC_VWAP::InputFileSource fileSources){

    bool vaildInput = false;
    do{   
        std::string userInput = MENU::getInputFromUser(MENU::STORE);
     
        try{
             switch(MENU::getOption(MENU::STORE.OPTIONS, userInput)) {
                case MENU::EXIT:
                    mainMenu(stocks);
                    break;
                    
                case MENU::CSV:
                    if(fileSources.FILE == MAGIC_VWAP::InputFiles::VWAP_BY_STOCK.FILE){
                        saveVWAPByStockToCSV(stocks);  
                    }else if(fileSources.FILE == MAGIC_VWAP::InputFiles::VWAP_BY_ISIN_TRADE_COMBO.FILE){
                        saveVWAPByISINTradeComboToCSV(stocks);
                    }
                    vwapMenu(stocks);
                    break;
                   
                case MENU::JASON:
                default:
                    throw(std::out_of_range("Missing menu option"));
                    break;
            }

            vaildInput = true;
        }catch(std::out_of_range& e){
            std::cout << e.what() << std::endl;
        }
    }while(!vaildInput);
}



MENU::Options MENU::getOption(MENU::OptionMapings options, std::string input){

    if(std::isdigit(input[0])){
        for (auto const& [name, option] : options)
            {
                if(option.CODE == std::stoi(input))
                    return name;
                
            }
            throw(std::out_of_range("Unknown Code"));
    }else{
        for (auto const& [name, option] : options)
            {
                if(option.ABBREVIATION == input)
                    return name;
            }
            throw(std::out_of_range("Unknown abrevation"));
    }
};


std::string MENU::getInputFromUser(MENU::Menu menu){
     std::cout << menu.TITLE << std::endl;
        for (auto const& option : menu.OPTIONS)
            {
                std::cout << option.second.NAME << '(' << option.second.ABBREVIATION << ')'<< MENU::DIVIDER;
            }
        std::cout << std::endl;      
        std::string userInput;
        std::cin >>  userInput;
        return userInput;
};

std::string MENU::autoDividers(int size, std::string leftText){
    std::string out = leftText;
    int difference = size - ( leftText + MENU::DIVIDER).size();
    for(int i = difference; i > 0; i--){
        out += ' ';
    }
    return out + MENU::DIVIDER;
};


void saveVWAPByStockToCSV(Stocks& stocks){
    std::ofstream file;
    file.open (MAGIC_VWAP::InputFiles::DATASET_FILE_DIR + MAGIC_VWAP::InputFiles::VWAP_BY_STOCK.FILE);
    file << MAGIC_VWAP::InputFiles::VWAP_BY_STOCK.COLS.at(MAGIC_VWAP::SourceColumn::EPIC) << ','
            << MAGIC_VWAP::InputFiles::VWAP_BY_STOCK.COLS.at(MAGIC_VWAP::SourceColumn::ISIN) << ','
             << MAGIC_VWAP::InputFiles::VWAP_BY_STOCK.COLS.at(MAGIC_VWAP::SourceColumn::WVAP) << std::endl;

    for(const auto& [isin, stock] : stocks.getStocks()){
        file << stock.getEpic() << ',' << isin << ','<< stock.getVWAP() <<',' << std::endl;
    }
    file.close();
};


void saveVWAPByISINTradeComboToCSV(Stocks& stocks){
    std::ofstream file;
    file.open (MAGIC_VWAP::InputFiles::DATASET_FILE_DIR + MAGIC_VWAP::InputFiles::VWAP_BY_ISIN_TRADE_COMBO.FILE);
    file << MAGIC_VWAP::InputFiles::VWAP_BY_ISIN_TRADE_COMBO.COLS.at(MAGIC_VWAP::SourceColumn::EPIC) << ','
            << MAGIC_VWAP::InputFiles::VWAP_BY_ISIN_TRADE_COMBO.COLS.at(MAGIC_VWAP::SourceColumn::ISIN) << ','
             << MAGIC_VWAP::InputFiles::VWAP_BY_ISIN_TRADE_COMBO.COLS.at(MAGIC_VWAP::SourceColumn::WVAP) << std::endl;

    for(const auto& [info, vwap]: stocks.getWVAPByTradeComdo()){
        const auto& [isin, trade] = info;
        file << isin << ','  <<  trade << ',' << vwap  << std::endl;
    }
    file.close();
};


