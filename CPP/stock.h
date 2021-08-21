#ifndef STOCK_H_
#define STOCK_H_
#include <string>
#include <map>

    /*Key = the trades trade refrence as a string
    Value = a Trade object storing all infornation*/

    using TradeContainer = std::map<std::string, Trade>;

    struct Trade{
        
        //Unique code for each transaction
        std::string trade_ref;

        //The type of trade
        std::string trade_type;

        //The number of shares traded
        int quatity;

        //The price at which the shares were traded (Not sure what currency but guessing pounds?)
        double price;
    };



class Stock {


private:
    //Short name for the stock
    std::string epic;

    //Long unique name for the stock
    std::string isin;

    /*All trades of this stock
    */
    TradeContainer trades;



public:
    /*----Constructors----*/
    Stock() = default;

    Stock(const std::string& epic, std::string& isin);

    /*----Getters----*/
    std::string getEpic() const;

    std::string getISIN() const;

    Trade& getTrade(std::string trade_ref) const;
    
    //get the VWAP for all trades of this stock
    double getVWAP() const;

    //get the VWAP for all trades of given type for this stock
    double getVWAP(std::string trade_type) const;

    /*----Setters---*/
    void addTrade(std::string trade_ref, std::string trade_type, int quantity, double price);

    /*----Overrides----
    friend std::ostream& operator<<(std::ostream& os, const Stock& stock);
    */

};

#endif // AREA_H_