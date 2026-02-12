#include <string>

#include "test_framework/generic_test.h"
using std::string;
int RomanToInteger(const string& s) {
  // TODO - you fill in here.
  int sum = 0;
  int size_s = s.size();
  for(int i=0;i<s.size();i++){
    int next_i = i+1;
    if(s[i]=='I'){
      if(next_i<size_s && s[next_i]=='V'){
        sum+=4;
        i++;
        continue;
      }
      if(next_i<size_s && s[next_i]=='X'){
        sum+=9;
        i++;
        continue;
      }
      sum+=1;
      continue;
    }
    if(s[i]=='X'){
      if(next_i<size_s && s[next_i]=='L'){
        sum+=40;
        i++;
        continue;
      }
      if(next_i<size_s && s[next_i]=='C'){
        sum+=90;
        i++;
        continue;
      }
      sum+=10;
      continue;
    }

    if(s[i]=='C'){
      if(next_i<size_s && s[next_i]=='D'){
        sum+=400;
        i++;
        continue;
      }
      if(next_i<size_s && s[next_i]=='M'){
        sum+=900;
        i++;
        continue;
      }
      sum+=100;
      continue;
    }
    else{
      switch(s[i]){
        case 'V':
          sum+=5;
          break;
        case 'L':
          sum+=50;
          break;
        case 'D':
          sum+=500;
          break;
        case 'M':
          sum+=1000;
          break;
      }
        
    }

  }
  return sum;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "roman_to_integer.cc", "roman_to_integer.tsv",
                         &RomanToInteger, DefaultComparator{}, param_names);
}
