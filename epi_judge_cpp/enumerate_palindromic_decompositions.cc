#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool is_palindrome(string s){
  int end = s.size()-1;
  for(int i = 0;i<(s.size()/2);i++){
    if(s[i]!=s[end-i]){
      return false;
    }
  }
  return true;
}

void get_palindrome_decompositions(vector<string>* const decomposition, string s, vector<vector<string>>* const all_decompositions){
  if(s.empty()){
    all_decompositions->push_back(*decomposition);
  }

  for(int i=0;i<s.size();i++){
    if(is_palindrome(s.substr(0, i+1))){
      decomposition->push_back(s.substr(0, i+1));
      get_palindrome_decompositions(decomposition, s.substr(i+1), all_decompositions);
      decomposition->pop_back();
    }
  }

}

vector<vector<string>> PalindromeDecompositions(const string& text) {
  vector<string> decomposition = {};
  vector<vector<string>> all_decompositions = {};
  // string text = *text;
  get_palindrome_decompositions(&decomposition, text, &all_decompositions);
  return all_decompositions;
}
bool Comp(vector<vector<string>> expected, vector<vector<string>> result) {
  std::sort(begin(expected), end(expected));
  std::sort(begin(result), end(result));
  return expected == result;
};

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"text"};
  return GenericTestMain(args, "enumerate_palindromic_decompositions.cc",
                         "enumerate_palindromic_decompositions.tsv",
                         &PalindromeDecompositions, &Comp, param_names);
}
