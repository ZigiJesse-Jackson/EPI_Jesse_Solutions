#include <string>
#include <vector>
#include "test_framework/generic_test.h"
using std::string;
using std::vector;

void generate_balanced_parentheses(int left_remaining, int right_remaining, string valid_parentheses, vector<string>* const all_balanced_parentheses_of_k){

  if(left_remaining==0 && right_remaining == 0){
    all_balanced_parentheses_of_k->push_back(valid_parentheses);
    return;
  }

  if(left_remaining>0){
    generate_balanced_parentheses(left_remaining-1, right_remaining, valid_parentheses+"(", all_balanced_parentheses_of_k);
  }
  if(right_remaining>left_remaining){
    generate_balanced_parentheses(left_remaining, right_remaining-1, valid_parentheses+")", all_balanced_parentheses_of_k);
  }

}

vector<string> GenerateBalancedParentheses(int num_pairs) {
  

  vector<string> all_k_pairs_valid_parentheses = {};
  generate_balanced_parentheses(num_pairs, num_pairs, "", &all_k_pairs_valid_parentheses);
  return all_k_pairs_valid_parentheses;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_pairs"};
  return GenericTestMain(args, "enumerate_balanced_parentheses.cc",
                         "enumerate_balanced_parentheses.tsv",
                         &GenerateBalancedParentheses, UnorderedComparator{},
                         param_names);
}
