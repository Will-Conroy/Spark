#ifndef MENU_H_
#define MENU_H_
#include <string>
#include <unordered_map>


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
            {CALCULATE_VWAP,  Option {"VWAP",   1,  "vwap"}},
            {SEARCH,          Option {"Search", 0,  "?"}}

        }
    }; 

    const Menu STORE = {
        "Save menu",
        {
            {EXIT,           Option {"Back",    3   ,".."}},
            {DISPLAY,        Option {"Display", 2   ,"d"}},
            {CSV,            Option {"CSV",     1   ,"c"}},
            {JASON,          Option {"JASON",   0   ,"j"}}
        }
    }; 

    const Menu SEARCH_WVAP = {
        "Search WVAP menu",
        {
            {EXIT,          Option {"Back",         3,  ".."}},
            {EPIC,          Option {"EPIC",         2,  "e"}},
            {TRADE_TYPE,    Option {"ISIN & Type",  1,  "t"}},
            {ISIN,          Option {"ISIN",         0,  "i"}}
        }
    };

    const Menu VWAP = {
        "Calculate VWAP menu",
        {
            {EXIT,          Option {"Back",                 2,  ".."}},
            {TRADE_TYPE,    Option {"Per stock/trade type", 1,  "t"}},
            {ISIN,          Option {"Per stock",            0,  "s"}}
    };

    constexpr size_t NUM_MENUS = 4;

    const Menu MENUS[NUM_MENUS] = { MAIN,
                                    STORE,
                                    SEARCH_WVAP,
                                    VWAP
                                                };

    const std::string DIVIDER = " | ";

    Options getOption(OptionMapings options, std::string input);
}
#endif // MENU_H_