#include <vector>
#include <cstdlib>

#include "test_framework/generic_test.h"
using std::vector;

// The numbering starts from one, i.e., if A = [3, 1, -1, 2] then
// FindKthLargest(1, A) returns 3, FindKthLargest(2, A) returns 2,
// FindKthLargest(3, A) returns 1, and FindKthLargest(4, A) returns -1.
int FindKthLargest(int k, vector<int> *A_ptr)
{
  int l = 0, r = A_ptr->size() - 1;
  if(r == 0) return (*A_ptr)[0];
  
  while (l < r)
  {
    int pivot = (std::rand() % (r - l)) + l, gt = l+1, lt = l+1;
    std::swap((*A_ptr)[l], (*A_ptr)[pivot]);
    while (lt <= r)
    {
      if ((*A_ptr)[l] < (*A_ptr)[lt])
        std::swap((*A_ptr)[gt++], (*A_ptr)[lt]);
      lt++;
    }
    std::swap((*A_ptr)[l], (*A_ptr)[--gt]);
    if(gt==k-1) return (*A_ptr)[gt];
    if(gt>=k) r = gt-1;
    else l = gt+1;
  }
  return (*A_ptr)[l];
}
int FindKthLargestWrapper(int k, vector<int> &A)
{
  return FindKthLargest(k, &A);
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "A"};
  return GenericTestMain(args, "kth_largest_in_array.cc",
                         "kth_largest_in_array.tsv", &FindKthLargestWrapper,
                         DefaultComparator{}, param_names);
}
