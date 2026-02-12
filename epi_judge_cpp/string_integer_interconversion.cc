#include <string>
#include <math.h>
#include <algorithm>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;

string IntToString(int x) {
  string res = "";
  bool sign = false;
  if(x<0) sign = true;
  while(x!=0){
    res.push_back(x%10);
    x/=10;
  }
  if(sign)res.push_back('-');
  std::reverse(res.begin(), res.end());
  
  return res;
}
int StringToInt(const string& s) {
  int res = 0;
  int curr;
  for(int i=0;i<s.size();i++){
    curr = s[i]-'0';
    res*=10;
    res +=curr;
    if(s[i] == '-') res*=-1;
  }
  return res;
}
void Wrapper(int x, const string& s) {
  if (stoi(IntToString(x)) != x) {
    throw TestFailure("Int to string conversion failed");
  }

  if (StringToInt(s) != x) {
    throw TestFailure("String to int conversion failed");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"x", "s"};
  return GenericTestMain(args, "string_integer_interconversion.cc",
                         "string_integer_interconversion.tsv", &Wrapper,
                         DefaultComparator{}, param_names);
}
