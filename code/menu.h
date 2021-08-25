#ifndef MENU_H_
#define MENU_H_
#include <string>

/*

  This file contains declarations for the menus. 
 
 */


namespace MENU  {

    enum Options {
            EXIT,
            SEARCH,
            EPIC,
            ISIN,
            TRADE_TYPE,
            LOAD,
            CALCULATE_VWAP,
            SAVE,
            JASON,
            CSV,
            DISPLAY
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
            {EXIT,            Option {"Exit",   3,  ".."}},
            {LOAD,            Option {"Load",   2,  "l"}},
            {CALCULATE_VWAP,  Option {"VWAP",   1,  "v"}},
            {SEARCH,          Option {"Search", 0,  "?"}}

        }
    }; 

    const Menu STORE = {
        "Save menu",
        {
            {EXIT,           Option {"Back",    3   ,".."}},
            {CSV,            Option {"CSV",     1   ,"c"}},
            {JASON,          Option {"JASON",   0   ,"j"}}
        }
    }; 


    const Menu VWAP = {
        "Calculate VWAP menu",
        {
            {EXIT,          Option {"Back",                 2,  ".."}},
            {TRADE_TYPE,    Option {"Per stock/trade type", 1,  "t"}},
            {ISIN,          Option {"Per stock",            0,  "s"}}
        }
    };

    constexpr size_t NUM_MENUS = 3;

    const Menu MENUS[NUM_MENUS] = { MAIN,
                                    STORE,
                                    VWAP
                                                };

    const std::string DIVIDER = " | ";

    Options getOption(OptionMapings options, std::string input);
    std::string getInputFromUser(Menu menu);
    std::string autoDividers(int size, std::string leftText);
}
#endif // MENU_H_