#ifndef INPUT_H_
#define INPUT_H_


#include <string>
#include <fstream>


class InputSource {
protected:
    InputSource(const std::string& source);
    std::string source;

public:
    std::string getSource();

};

/*
  Source data that is contained within a file. For now, our application will
  only work with files (and in particular, the files in the datasets directory).

  or functions you implement here, and perhaps additional operators you may wish
  to overload.
*/
class InputFile : public InputSource {
public:
  InputFile(const std::string& filePath);
  std::istream& open() noexcept(false);
};

#endif // INPUT_H_