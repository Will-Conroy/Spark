#include "magicVWAP.h"
#include "datapath.h"
#include "input.h"
#include "menu.h"
#include <string>

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
    std::cout << "ISIN:" << std::endl;
    std::string isin;
    std::cin >> isin;
    std::cout << stocks.getStock(isin).getVWAP();
};

void displayVWAPPerStock(Stocks& stocks){
    std::cout << " EPIC  |      ISIN      |#tr | VWAP" << std::endl;
    std::cout << stocks;
};

void displayVWAPromCommandLineByISINTradeCombo(Stocks& stocks){
    
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

                case MENU::SEARCH:
                    searchMenu(stocks);
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


void searchMenu(Stocks& stocks){

    bool vaildInput = false;
    do{   
        std::string userInput = MENU::getInputFromUser(MENU::SEARCH_WVAP);
     
        try{
             switch(MENU::getOption(MENU::SEARCH_WVAP.OPTIONS, userInput)) {
                case MENU::EXIT:
                    mainMenu(stocks);
                    break;
                case MENU::EPIC:
                    
                case MENU::TRADE_TYPE:
                   
                case MENU::ISIN:
                    displayVWAPFromCommandLineByISIN(stocks);
                    searchMenu(stocks);
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
                   
                case MENU::ISIN:
                    displayVWAPPerStock(stocks);
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