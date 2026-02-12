#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

void computeMnemonic(const string& phone_number, string& mnemonic, int idx, vector<string>& mnemonics, vector<vector<char>>& mappings){
  if(idx>=phone_number.size()){
    mnemonics.push_back(mnemonic);
    return;
  }

  for(char letter: mappings[phone_number[idx]-'0']){
    mnemonic.push_back(letter);
    computeMnemonic(phone_number, mnemonic, idx+1, mnemonics, mappings);
    mnemonic.pop_back();
  }
  
}

vector<string> PhoneMnemonic(const string& phone_number) {
  string mnemonic ="";
  vector<string> mnemonics;
  vector<vector<char>> mappings{
    vector<char>{'0'},                        // 0
    vector<char>{'1'},                        // 1
    vector<char>{'A', 'B', 'C'},           // 2
    vector<char>{'D', 'E', 'F'},           // 3
    vector<char>{'G', 'H', 'I'},           // 4
    vector<char>{'J', 'K', 'L'},           // 5
    vector<char>{'M', 'N', 'O'},           // 6
    vector<char>{'P', 'Q', 'R', 'S'},      // 7
    vector<char>{'T', 'U', 'V'},           // 8
    vector<char>{'W', 'X', 'Y', 'Z'}       // 9
};
  computeMnemonic(phone_number, mnemonic, 0, mnemonics, mappings);
  return mnemonics;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"phone_number"};
  return GenericTestMain(args, "phone_number_mnemonic.cc",
                         "phone_number_mnemonic.tsv", &PhoneMnemonic,
                         UnorderedComparator{}, param_names);
}
