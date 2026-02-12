#include <string>

#include "test_framework/generic_test.h"
using std::string;

string SnakeString(const string& s) {
  // TODO - you fill in here.
  string top, bottom, middle;
  for(int i=0;i<s.size();i++){
    if(i%2==0)middle.push_back(s[i]);
    else if((i+1)%4==0)bottom.push_back(s[i]);
    else top.push_back(s[i]);
  }
  return top+middle+bottom;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "snake_string.cc", "snake_string.tsv",
                         &SnakeString, DefaultComparator{}, param_names);
}
