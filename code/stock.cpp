#include "stock.h"
#include <iostream>



/*
    A helper function that caculates the VWAP given a map of trades
  @param trades
    a TradeContainer that store a set of trade that you want the combind VWAP for


  @return
    a double that is the caculated VWAP

*/


 double cacluateVWAP(const TradeContainer& trades){
    double numerator = 0;
    int denominator = 0;
    
    for (auto const& [isan, trade] : trades)
    {
     numerator += trade.price * trade.quatity;
     denominator += trade.quatity;
    }

    if(denominator == 0)
    {
        return 0;
    }

    return numerator/denominator;
 };

/*
  Construct an Stock with a given a EPIC and ISIN

  @param EPIC
    Short name for the stock

 @param ISIN
    Long uniqu name for the stock


*/
Stock::Stock(const std::string& epic, std::string& isin): epic(epic), isin(isin){}

/*----Getters----*/

/*
  Gets the epic of the stock

 @return EPIC
    string of the epic
*/
std::string Stock::getEpic() const{
    return this->epic;
};

/*
  Gets the epic of the stock

 @return ISIN
    string of the isin
*/
std::string Stock::getISIN() const{
    return this->isin;
};

/*
  Return a Trade struct given a trade refence

  @param trade_ref
    a trades refence in the form of a string

 @returns Trade 
    value return of a trade

*/

Trade Stock::getTrade(std::string trade_ref) const{
    
    
    return  this->trades.at(trade_ref);
    
};



TradeContainer Stock::getTrades() const{
    return this->trades;
};

/*
  For each given type of trade for this stock, it return off of those trade 

  @param trade type
    Short name for the stock

 @return TradeContainer
        Containing all trades of that type


*/

TradeContainer Stock::getTradesByType(std::string type) const{
    TradeContainer tradesByType;
    for(auto const& x : this->trades){
        if(x.second.trade_type == type)
            tradesByType.insert(x);
    }
    return tradesByType;
};


/*
  For each unquie type of trade a TradeContainer is return with all of those trades 

 @return std::map<const std::string, const TradeContainer&>
    Key is a string indacting the type of trade
    Value is TradeContainer with all of the given trade in
*/

std::map<const std::string, const TradeContainer&> Stock::getTradesByTypes() const{
    std::map<const std::string,  TradeContainer> tradesBytype;
    
    for(auto const& x : this->trades){
        //checks if this type of trade has already been added
        //if it hasn't creates a new tradcontaner
        try{
            tradesBytype.at(x.second.trade_type).insert(x);
        }catch(std::out_of_range& e){
            TradeContainer newTradeType;
            newTradeType.insert(x);
            tradesBytype.insert(
                std::pair<const std::string,  TradeContainer>(x.second.trade_type, newTradeType)
                );
        }
    }

    std::map<const std::string,  const TradeContainer&> temp;
    for(auto const& x : tradesBytype){
       temp.insert(x);
    }
    return temp;
};





//get the VWAP for all trades of this stock
double Stock::getVWAP() const {
    const TradeContainer& temp = this->trades;
    return cacluateVWAP(temp);
}

//get the VWAP for all trades of given type for this stock
    double Stock::getVWAP(std::string trade_type) const{

        double numerator = 0;
        int denominator = 0;
        
        for (auto const& [type, trade] : this->trades)
        {
            if(trade.trade_type == trade_type){
                numerator += trade.price * trade.quatity;
                denominator += trade.quatity;

            }
        }
        if(denominator == 0)
        {
            return 0;
        }

        return numerator/denominator;

    };

 /*----Setters---*/
    void Stock::addTrade(std::string trade_ref, std::string trade_type, int quantity, double price){
         this->trades.insert(std::pair<const std::string, Trade>(trade_ref, {trade_ref, trade_type, quantity, price}));
        
    };

    void Stock::addTrade(Trade trade){
         this->trades.insert(std::pair<const std::string, Trade>(trade.trade_ref, trade));
    };  


/*----Overrides----*/


std::ostream& operator<<(std::ostream& os, const Trade& trade){
    std::string divider = " | ";
    os << trade.trade_ref << divider << trade.trade_type << divider << std::to_string(trade.quatity) << divider << std::to_string(trade.price);
    return os;
};


std::ostream& operator<<(std::ostream& os, const Stock& stock){
    std::string divider = " | ";
    std::string stockInfo = stock.getEpic() + divider + stock.getISIN() + divider ;
    os << stockInfo << stock.getTrades().size() << divider << stock.getVWAP() << divider << std::endl;
    /*for(auto const& [type, trade] : stock.getTrades()){
        os << trade << std::endl;
    }*/
    return os;
};

