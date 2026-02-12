#include <string>

#include "test_framework/generic_test.h"
using std::string;

int SSDecodeColID(const string& col) {
  // TODO - you fill in here.
  int b_10 = 0, digit;
  for(int i=0;i<col.size();i++){
    digit = (col[i]-'A')+1;
    b_10 = (b_10*26)+digit;
  }
  return b_10;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"col"};
  return GenericTestMain(args, "spreadsheet_encoding.cc",
                         "spreadsheet_encoding.tsv", &SSDecodeColID,
                         DefaultComparator{}, param_names);
}
