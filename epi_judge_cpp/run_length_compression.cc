#include <string>
#include <algorithm>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
using std::string;
string Decoding(const string &s) {
  string decoding;
  string counter;
  int count = 0;
  for(int i= 0;i<s.size();i++){
    if(s[i]-'0'>=0 && s[i]-'0'<=9){
      counter.push_back(s[i]);
    }
    else{
      count = std::stoi(counter);
      counter.clear();
      decoding.append(count, s[i]);
    }

  }
  return decoding;
}
string Encoding(const string &s) {
  string encoding;
  int counter = 1;
  for(int i=1;i<s.size();i++){
    if(s[i]==s[i-1]){
      counter++;
    }
    else{
      encoding += std::to_string(counter);
      encoding.push_back(s[i-1]);
      counter = 1;
    }
  }
  encoding += std::to_string(counter);
  encoding.push_back(s.back());
  return encoding;
}
void RleTester(const string &encoded, const string &decoded) {
  if (Decoding(encoded) != decoded) {
    throw TestFailure("Decoding failed");
  }
  if (Encoding(decoded) != encoded) {
    throw TestFailure("Encoding failed");
  }
}

int main(int argc, char *argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"encoded", "decoded"};
  return GenericTestMain(args, "run_length_compression.cc",
                         "run_length_compression.tsv", &RleTester,
                         DefaultComparator{}, param_names);
}
