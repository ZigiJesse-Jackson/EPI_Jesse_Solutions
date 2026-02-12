#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> NextPermutation(vector<int> perm) {
  // TODO - you fill in here.
  if(perm.size()==1 || perm.size()==0) return {};
  int r = perm.size()-1, l = perm.size()-2;
  while( l>=0 && perm[l]>=perm[l+1]){
    l--;
  }
  if(l == -1) return {};
  
  for(int i = r;i>l;i--){
    if(perm[l]<perm[i]) {
      int temp = perm[l];
      perm[l] = perm[i];
      perm[i] = temp;
      break;
    } 
  }
  l+=1;
  while(l<r){
    int temp = perm[l];
    perm[l++] = perm[r];
    perm[r--] = temp;
  }
  return perm;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"perm"};
  return GenericTestMain(args, "next_permutation.cc", "next_permutation.tsv",
                         &NextPermutation, DefaultComparator{}, param_names);
}
