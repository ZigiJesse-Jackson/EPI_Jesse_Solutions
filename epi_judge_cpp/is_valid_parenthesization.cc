#include <string>

#include "test_framework/generic_test.h"
using std::string;
bool IsWellFormed(const string& s) {
  // TODO - you fill in here.
  string checker = "";
  for(char i: s){
    if(i=='{' || i=='(' || i=='[') checker.push_back(i);
    else{
      char b = checker.back();
      if(b =='{' && i=='}'){
        checker.pop_back();
      }
      else if(b =='(' && i==')'){
        checker.pop_back();
      }
      else if(b =='[' && i==']'){
        checker.pop_back();
      }
      else return false;
       
    }
  }

  return checker.empty();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_valid_parenthesization.cc",
                         "is_valid_parenthesization.tsv", &IsWellFormed,
                         DefaultComparator{}, param_names);
}
