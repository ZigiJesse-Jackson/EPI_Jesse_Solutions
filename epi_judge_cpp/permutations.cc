#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void compute_permutation(vector<int>& A, int s_idx, vector<vector<int>>& permutations_collector){
  if(s_idx >= A.size()-1){
    permutations_collector.push_back(A);
    return;
  }
  
  for(int i = s_idx; i<A.size(); i++){
    std::swap(A[i], A[s_idx]);
    compute_permutation(A, s_idx+1, permutations_collector);
    std::swap(A[i], A[s_idx]);
  }
}

vector<vector<int>> Permutations(vector<int> A) {
  // TODO - you fill in here.
  vector<vector<int>> permutations = {};
  compute_permutation(A, 0, permutations);
  return permutations;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "permutations.cc", "permutations.tsv",
                         &Permutations, UnorderedComparator{}, param_names);
}
