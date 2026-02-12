#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::vector;

int LongestSubarrayWithDistinctEntries(const vector<int> &A)
{
  int last_idx = 0, max_sub_len = INT32_MIN, len_A = A.size();
  std::unordered_map<int, int> map;
  for (int i = 0; i < A.size(); i++)
  {
    if (map.find(A[i]) != map.end() && map[A[i]]>=last_idx)
    {
      max_sub_len = std::max(max_sub_len, i - last_idx);
      last_idx = map[A[i]]+1;
    }
    map[A[i]] = i;
  }

  max_sub_len = std::max(len_A-last_idx, max_sub_len);
  return max_sub_len;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "longest_subarray_with_distinct_values.cc",
                         "longest_subarray_with_distinct_values.tsv",
                         &LongestSubarrayWithDistinctEntries,
                         DefaultComparator{}, param_names);
}
