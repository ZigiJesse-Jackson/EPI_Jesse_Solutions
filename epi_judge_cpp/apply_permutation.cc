#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
void ApplyPermutation(vector<int> perm, vector<int>* A_ptr) {
  // TODO - you fill in here.
  vector<int>& A = *A_ptr;
  int i = 0;
  while(i<perm.size()){
    if(perm[i] == -i || (perm[i] == 0 && i==0)) i++;
    else{
      int temp = A[i];
      A[i] = A[perm[i]];
      A[perm[i]] = temp;
      temp = perm[i];
      perm[i] = perm[perm[i]];
      perm[temp] = -temp;
    }
  }
  return;
}
vector<int> ApplyPermutationWrapper(const vector<int>& perm, vector<int> A) {
  ApplyPermutation(perm, &A);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm", "A"};
  return GenericTestMain(args, "apply_permutation.cc", "apply_permutation.tsv",
                         &ApplyPermutationWrapper, DefaultComparator{},
                         param_names);
}
