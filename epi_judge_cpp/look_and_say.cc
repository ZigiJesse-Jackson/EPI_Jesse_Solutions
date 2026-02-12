#include <string>
#include "test_framework/generic_test.h"
using std::string;

string LookAndSayString(string seq){
  string curr="";
  int counter = 1;
  for(int i=1; i<seq.size();i++){
    if(seq[i]!=seq[i-1]){
      curr+=std::to_string(counter);
      curr.push_back(seq[i-1]);
      counter=0;
    }
    ++counter;
  }
  
  curr+=std::to_string(counter);
  curr.push_back(seq.back());
  
  return curr;
}

string LookAndSay(int n) {
  // TODO - you fill in here.
  if(n==1) return "1";
  int i = 1;
  string res = "1";
  while(i<n){
    res = LookAndSayString(res);
    i++;
  }
  return res;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "look_and_say.cc", "look_and_say.tsv",
                         &LookAndSay, DefaultComparator{}, param_names);
}
