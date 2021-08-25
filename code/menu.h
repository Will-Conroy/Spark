#ifndef MENU_H_
#define MENU_H_
#include <string>

/*


  This file contains information about menus.
  Namely the layout of the menus.
 
 */


namespace MENU  {

    /*
        Lots of menus will have similer options that will be slightly different in the context of the particalur menu.

    */
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
        //unqine int code for user to input to select the  option
        const int CODE;
        //unqine short string user to inpot to select the option
        const std::string ABBREVIATION;
    };

    using OptionMapings = std::unordered_map<Options, Option>;

    //this struct store the input for all option the menu has
    struct Menu {
        //Title to inform the user
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

    //Divered for colums in tables and different options. changing this will change the look of the full program
    const std::string DIVIDER = " | ";


    //Give a user input returns the option that it maps too
    Options getOption(OptionMapings options, std::string input);
    //get the users input, check if it is valid can clean it up.
    std::string getInputFromUser(Menu menu);

    //user to make usre that tables are the equal size
    std::string autoDividers(int size, std::string leftText);
}
#endif // MENU_H_