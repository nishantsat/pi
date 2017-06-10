#include <string>
using std::string;

class CsvParser {
public:
  explicit CsvParser(string fname);
  size_t nrows() const;
  size_t ncols() const;
};
