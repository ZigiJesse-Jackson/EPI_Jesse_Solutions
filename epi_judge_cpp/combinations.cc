#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void compute_k_subset(int num, int n, int k, vector<int>* subset, vector<vector<int>>* const subsets){
  if(subset->size()==k){
    subsets->push_back(*subset);
    return;
  }

  if(num>n) return;

  for(int i = num; i<=n; i++){
    subset->push_back(i); 
    compute_k_subset(i+1, n, k, subset, subsets);
    subset->pop_back();
  }
}

vector<vector<int>> Combinations(int n, int k) {
  vector<int> subset = {};
  vector<vector<int>> subsets = {};
  compute_k_subset(1, n, k, &subset, &subsets);
  return subsets;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(args, "combinations.cc", "combinations.tsv",
                         &Combinations, UnorderedComparator{}, param_names);
}
