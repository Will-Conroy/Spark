#ifndef DATASETS_H_
#define DATASETS_H_

/*


  This file contains information about the files in the datasets directory. 
 
 */


#include <string>
#include <unordered_map>

namespace MAGIC_VWAP  {


enum SourceDataType {
  None,
  TradeCSV,
};

/*
  Data from the different sources will have different collums and different names for collums.
  In this project they are all the same but to make sure it is still exspandable I have added this implamtion.
*/
enum SourceColumn {
    EPIC,
    ISIN,
    TRADE_REF,
    TRADE_TYPE,
    QUANTITY,
    PRICE,
    WVAP
};

using SourceColumnMapping = std::unordered_map<SourceColumn, std::string>;

/*
  This is a simple container that we use for storing information about the
  datasets in the data directory.
*/
struct InputFileSource {


  // FILE is the name of the file in the datasets directory
  const std::string FILE;

 
  // to parse the text from the file
  const SourceDataType PARSER;

  // COLS is a map of the column headings for this dataset
  //   - the key is a SourceColumn enum value
  //   - the value is the name of the column in the data file
  const SourceColumnMapping COLS;
};

/*
  In this namespace, we store all the data for the various datasets that can
  be found in the datasets directory.
*/
namespace InputFiles {

const InputFileSource MARKET_TRADE = {
  "market_trades.csv",
  MAGIC_VWAP::SourceDataType::TradeCSV,
  {
      {EPIC,        "epic"},
      {ISIN,        "isin"},
      {TRADE_REF,   "trade ref"},
      {TRADE_TYPE,  "trade type"},
      {QUANTITY,    "quantity"},
      {PRICE,       "price"},
  }
};

const InputFileSource VWAP_BY_STOCK = {
  "vwap_by_stock.csv",
  MAGIC_VWAP::SourceDataType::TradeCSV,
  {
      {EPIC,        "epic"},
      {ISIN,        "isin"},
      {WVAP,        "WVAP"}
  }
}; 


const InputFileSource VWAP_BY_ISIN_TRADE_COMBO = {
  "vwap_by_ISIN_trade_combo.csv",
  MAGIC_VWAP::SourceDataType::TradeCSV,
  {
     
      {ISIN,        "isin"},
      {TRADE_TYPE,  "trade type"},
      {WVAP,        "WVAP"}
  }
};




constexpr size_t NUM_DATASETS = 3;

const InputFileSource DATASETS[NUM_DATASETS] = { MARKET_TRADE,
                                                  VWAP_BY_STOCK,
                                                  VWAP_BY_ISIN_TRADE_COMBO
                                                };

const std::string DATASET_FILE_DIR = "datasets/";

} // namespace InputFiles

} // namespace MAGIC_VWAP

#endif // DATASETS_H_