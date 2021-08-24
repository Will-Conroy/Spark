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




void mainMenu(){
    bool vaildInput = false;
    do{
        std::cout << MENU::MAIN.TITLE << std::endl;
        for (auto const& option : MENU::MAIN.OPTIONS)
            {
                std::cout << option.second.NAME << '(' << option.second.ABBREVIATION << ')'<< MENU::DIVIDER;
            }
        std::cout << std::endl;      
        std::string userInput;
        std::cin >>  userInput;
        try{
             switch(MENU::getOption(MENU::MAIN.OPTIONS, userInput)) {
                case MENU::EXIT:
                    break;
                case MENU::SAVE:
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