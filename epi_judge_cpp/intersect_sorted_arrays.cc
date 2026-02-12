#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

vector<int> IntersectTwoSortedArrays(const vector<int>& A,
                                     const vector<int>& B) {
  int m = A.size(), n = B.size(), a_idx = 0, b_idx = 0;
  vector<int> res;
  while(a_idx<m && b_idx<n)
  {
    if(A[a_idx]==B[b_idx])
    { 
      if(res.empty() || res.back()!=A[a_idx])
        res.push_back(A[a_idx]);
      a_idx++;
      b_idx++;
    }
    else if(A[a_idx]<B[b_idx])
    {
      a_idx++;
    }
    else{
      b_idx++;
    }
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(
      args, "intersect_sorted_arrays.cc", "intersect_sorted_arrays.tsv",
      &IntersectTwoSortedArrays, DefaultComparator{}, param_names);
}
