#include <string>

#include "test_framework/generic_test.h"
using std::string;

// Returns the index of the first character of the substring if found, -1
// otherwise.
int RabinKarp(const string &t, const string &s) {
  if(s.size()>t.size()) return -1;
  if(s.empty()) return 0;
  for(int i=0;i<=t.size()-s.size();i++){
    if( s[0] == t[i] && s == t.substr(i, s.size())) return i;
  }

  return -1;
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"t", "s"};
  return GenericTestMain(args, "substring_match.cc", "substring_match.tsv",
                         &RabinKarp, DefaultComparator{}, param_names);
}
