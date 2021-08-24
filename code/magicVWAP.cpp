
#include "magicVWAP.h"
#include "datapath.h"
#include "input.h"

void mysoul (NULL)

(a)void speaking to people

void populatedStocksFromCommandLine(Stocks& stocks){
    
    bool populated = false;

    do{
        std::cout << "What file do you want to read in:" << std::endl;
       
        for(int i = 0; i < MAGIC_VWAP::InputFiles::NUM_DATASETS; i++){
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
            populated = true;
        }
        catch(std::runtime_error& e)
        {
            std::cout << e.what() << std::endl;
        }catch(...){
            std::cout << "Invlaid responce, please enter an int that corraspons to a file" << std::endl;
        }
        
    }while(!populated);

    
}