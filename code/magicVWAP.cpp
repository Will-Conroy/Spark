
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
            std::cout << '{' << i << " | " << MAGIC_VWAP::InputFiles::DATASETS[i].NAME << " | " << MAGIC_VWAP::InputFiles::DATASETS[i].FILE << "}, ";
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
        std::cout << MENU::MAIN.TITLE << std::endl;
        for (auto const& option : MENU::MAIN.OPTIONS)
            {
                std::cout << option.second.NAME << " , " << option.second.ABBREVIATION << MENU::DIVIDER;

            }
        std::cout << std::endl;       
     
    };


MENU::Option MENU::getOption(MENU::Menu menu, std::string input){

    if(std::isdigit(input[0])){
        for (auto const& [name, option] : menu.OPTIONS)
            {
                if(option.CODE == std::stoi(input))
                    return option;
                
            }
            throw(std::out_of_range("Unknow Code"));
    }else{
        for (auto const& [name, option] : menu.OPTIONS)
            {
                if(option.ABBREVIATION == input)
                    return option;
            }
            throw(std::out_of_range("Unknow abrevation"));
    }
};