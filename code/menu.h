#ifndef MENU_H_
#define MENU_H_
#include <string>
#include <unordered_map>


namespace MENU  {

    enum Options {
            EXIT,
            SEARCH,
            LOAD,
            CALCULATE_VWAP,
            SAVE,
            JASON,
            CSV
   
    };

    struct Option{
        const std::string NAME;
        const int CODE;
        const std::string ABBREVIATION;
    };

    using OptionMapings = std::unordered_map<Options, Option>;

    struct Menu {
        const std::string TITLE;
        const OptionMapings OPTIONS;
    };


    const Menu MAIN = {
        "Main menu",
        {
            {EXIT,     Option {"Exit",0,".."}},
            {SEARCH,         Option {"Search",1,"?"}},
            {CALCULATE_VWAP,    Option {"VWAP",2,"vwap"}},
            {SAVE,   Option {"Save",3,"s"}},
            {LOAD,  Option {"Load",4,"l"}}
        }
    }; 

    const Menu STORE = {
        "Save menu",
        {
            {EXIT,     Option {"Back",0,".."}},
        }
    }; 

    constexpr size_t NUM_MENUS = 2;

    const Menu MENUS[NUM_MENUS] = { MAIN,
                                    STORE
                                                };

    const std::string DIVIDER = " | ";



    Option getOption(Menu menu, std::string input);


}




#endif // MENU_H_