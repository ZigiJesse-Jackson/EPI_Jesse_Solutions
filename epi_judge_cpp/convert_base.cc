#include <string>
#include <array>
#include <math.h>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::string;

// string ConvertBase(const string& num_as_string, int b1, int b2) {
//   // TODO - you fill in here.

//   std::array<char, 17> mappings {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
//   int curr_b_i = num_as_string.size()-1;
//   int b_10 = 0;
//   bool isNegative = false;
//   for(int i=0;i<num_as_string.size();i++){
//     if(num_as_string[i]=='-') {
//       isNegative = true;
//       continue;
//     }
//     int num = num_as_string[i]-'0';
//     if(num>9) num-=97;
//     b_10+=((num)*pow(b1, curr_b_i));
//     curr_b_i--;
//   }
//   string res = "";
//   while(b_10!=0){
//     int curr = b_10%b2;
//     res.push_back(mappings[curr]);
//     b_10/=b2;
//   }
//   if(isNegative) res.push_back('-');
//   std::reverse(res.begin(), res.end());
//   return res;
// }

std::string ConvertBase(const std::string& num_as_string, int b1, int b2) {
    if (num_as_string == "0") return "0";  // Handle the special case where the input is "0".

    std::array<char, 36> mappings {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 
                                   'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
                                   'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
                                   'U', 'V', 'W', 'X', 'Y', 'Z'};
    bool isNegative = num_as_string[0]=='-'?true:false;
    int i = isNegative? 1:0;
    // Convert from base b1 to base 10.
    int b_10=0, curr_b_i = num_as_string.size(), digit=0;
    for (; i < num_as_string.size(); ++i) {
        digit = num_as_string[i];
        if(digit-'0'<=9) digit-='0';
        else {
          digit-='A';
          digit+=10;
        }
        b_10 = b_10*b1+digit;
    }

    // Convert from base 10 to base b2.
    std::string result;
    while (b_10 > 0) {
        int remainder = b_10 % b2;
        result.push_back(mappings[remainder]);
        b_10 /= b2;
    }

    if (isNegative) {
        result.push_back('-');
    }

    std::reverse(result.begin(), result.end());  // Reverse the string to get the correct result.
    return result;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_as_string", "b1", "b2"};
  return GenericTestMain(args, "convert_base.cc", "convert_base.tsv",
                         &ConvertBase, DefaultComparator{}, param_names);
}
