#ifndef DATASETS_H_
#define DATASETS_H_

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: Dr Martin Porcheron

  This file contains information about the files in the datasets directory. 
  This file is designed to simulate what might be returned from a
  dynamically-generated code, although all the information is actually embedded
  here in code, and constructed as your program begins execution automatically.
  This is so that you can easily read and understand it (i.e., I didn't want
  this to be the focus of the coursework).

  You must not modify this file as it will be replaced with a fresh copy
  during marking.
 */


#include <string>
#include <unordered_map>

namespace MAGIC_VWAP  {

/*
  Enums (short for enumerations) are similar to their Java implementation.
  It is a user-defined type, used to assign names to internal constants
  in code, instead of simply passing in integers/strings etc.

  For example, functions can take a value/constant from a specific enum
  and use it in a switch statement, doing different things

  As such, it is a useful way for us to specify information in both a
  machine and human-readable format.

  Unlike Java, enum in C++ only map to intenger values. You can either let
  the compiler generate the values automatically, in which it allocates a
  unique integer (0-indexed). Or, you can set the value by giving the name
  followed by = <value> (e.g. AuthorityCodeCSV=1).

  This enum specifies the format types that the Areas class can parse.
  We could have implemented an if statement that parsed a string for the data
  type, or perhaps used integers. But with a enum both in code and to anyone
  who just glances at the code can infer the meaning.
*/
enum SourceDataType {
  None,
  TradeCSV,
};

/*
  Data from the different sources typically hagve different column headings
  for the same value (e.g. some might say "Year" whereas others might say
  "Year_Code"). Here we create another enum for these column headings for
  the parser.

  Each input passed to the Areas object will have to specifiy a
  an unordered map to match each of these enum values into a string that
  the source contains.
*/
enum SourceColumn {
    EPIC,
    ISIN,
    TRADE_REF,
    TRADE_TYPE,
    QUANTITY,
    PRICE
};

/*
  Finally, we create a mapping type for mapping the SourceColumn enum above
  to a std::string, which will be the name of the key/column in the dataset.

  i.e. the mapping of AUTH_CODE could be to "Authority_Code", and so on
*/
using SourceColumnMapping = std::unordered_map<SourceColumn, std::string>;

/*
  This is a simple container that we use for storing information about the
  datasets in the data directory.
*/
struct InputFileSource {
  // CODE is the string used in the program arguments
  const std::string CODE;

  // NAME is the name given to this dataset
  const std::string NAME;

  // FILE is the name of the file in the datasets directory
  const std::string FILE;

  // PARSER is a SourceDataType that tells the populate() function in Areas how
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
  "mark_trades",
  "Mtrades",
  "mark_trades.csv",
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

constexpr size_t NUM_DATASETS = 1;

const InputFileSource DATASETS[NUM_DATASETS] = { MARKET_TRADE,
                                                };

} // namespace InputFiles

} // namespace MAGIC_VWAP

#endif // DATASETS_H_