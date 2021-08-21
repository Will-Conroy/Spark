
#include "input.h"

#include <iostream>

InputSource::InputSource(const std::string& source): source(source){}


/*
  This function is callable from a constant context.

  @return
    A non-modifable value for the source passed into the construtor.
*/
std::string InputSource::getSource(){
    return this->source;
}

/*
  Constructor for a file-based source.

  @param path
    The complete path for a file to import.

  @example
    InputFile input("data/areas.csv");
*/
InputFile::InputFile(const std::string& filePath) : InputSource(filePath){}



/*
  Open a file stream to the file path retrievable from getSource()
  and return a reference to the stream.

  @return
    A standard input stream reference

  @throws
    std::runtime_error if there is an issue opening the file, with the message:
    InputFile::open: Failed to open file <file name>

  @example
    InputFile input("data/areas.csv");
    input.open();
*/
std::istream& InputFile::open(){
    std::istream* fileStream = new std::ifstream(InputFile::getSource());
    if(!(fileStream->good())){
            throw std::runtime_error("InputFile::open: Failed to open file " + InputFile::getSource());
    }
    return *fileStream;
}