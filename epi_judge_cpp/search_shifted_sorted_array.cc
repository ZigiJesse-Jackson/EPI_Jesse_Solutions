#include <vector>
#include <climits>

#include "test_framework/generic_test.h"
using std::vector;

int SearchSmallest(const vector<int> &A)
{
  int l = 0, r = A.size() - 1, m;
  int min = 0;
  while (l < r)
  {
    m = l + ((r - l) / 2);
    if (A[m] > A[r])
    {
      min = r;
      l = m + 1;
    }
    else
    {
      min = m;
      r = m;
    }
  }
  return min;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "search_shifted_sorted_array.cc",
                         "search_shifted_sorted_array.tsv", &SearchSmallest,
                         DefaultComparator{}, param_names);
}
