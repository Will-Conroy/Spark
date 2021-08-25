#include "menu.h"
#include "stocks.h"
#include "magicVWAP.h"

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



void MENU::mainMenu(Stocks& stocks){
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



