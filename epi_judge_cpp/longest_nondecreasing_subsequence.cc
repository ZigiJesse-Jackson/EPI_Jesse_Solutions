#include <vector>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::vector;

int Sub(int idx, const vector<int> &A, vector<int> *const memo)
{
  // first base case: gone beyond A
  if (idx >= A.size())
  {
    return 0;
  }

  if ((*memo)[idx] < 0)
  {
    // second base case: idx is the last element
    (*memo)[idx] = 1;
    for (int i = idx + 1; i < A.size(); i++)
    {
      if (A[idx] <= A[i])
      {
        (*memo)[idx] = std::max((*memo)[idx], 1 + Sub(i, A, memo));
      }
    }
  }
  return (*memo)[idx];
}

int LongestNondecreasingSubsequenceLength(const vector<int> &A)
{
  vector<int> memo(A.size(), -1);
  // Find LNDSL at i
  for (int i = 0; i < A.size(); i++)
  {
    Sub(i, A, &memo);
  }
  return *std::max_element(memo.begin(), memo.end());
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_nondecreasing_subsequence.cc",
                         "longest_nondecreasing_subsequence.tsv",
                         &LongestNondecreasingSubsequenceLength,
                         DefaultComparator{}, param_names);
}
