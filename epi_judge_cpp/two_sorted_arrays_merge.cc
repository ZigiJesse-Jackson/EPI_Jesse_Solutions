#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void MergeTwoSortedArrays(vector<int>& A, int m, const vector<int>& B, int n) {
  int a_idx = 0, b_idx = 0;
  vector<int> new_A;

  while(a_idx<m || b_idx<n)
  {
    if(a_idx == m)
    {
      while(b_idx<n)
      {
        new_A.push_back(B[b_idx++]);
      }
      A = new_A;
      return;
    }
    if(b_idx == n)
    {
      while(a_idx<m)
      {
        new_A.push_back(A[a_idx++]);
      }
      A = new_A;
      return;
    }
    if(A[a_idx]<=B[b_idx])
    {
      new_A.push_back(A[a_idx++]);
    }
    else
    {
      new_A.push_back(B[b_idx++]);
    }

  }
  A = new_A;
  return;
}
vector<int> MergeTwoSortedArraysWrapper(vector<int> A, int m,
                                        const vector<int>& B, int n) {
  MergeTwoSortedArrays(A, m, B, n);
  return A;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "m", "B", "n"};
  return GenericTestMain(
      args, "two_sorted_arrays_merge.cc", "two_sorted_arrays_merge.tsv",
      &MergeTwoSortedArraysWrapper, DefaultComparator{}, param_names);
}
