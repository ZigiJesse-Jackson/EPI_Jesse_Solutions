#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::vector;

int LongestContainedRange(const vector<int> &A)
{
  std::unordered_map<int, int> map;
  int max_sub_within = INT32_MIN;
  for (int i = 0; i < A.size(); i++)
  {
    map[A[i]] = 1;
  }
  for (int i = 0;i<A.size();i++)
  {
    if(map.find(A[i])==map.end()) continue;
    int sub_len = 1;
    int x = 1;
    while (map.find(A[i] + x) != map.end())
    {
      sub_len+=map[A[i]+x];
      map.erase(A[i]+x);
      x++;
    }
    x = 1;
    while (map.find(A[i] - x) != map.end())
    {
      sub_len+=map[A[i]-x];
      map.erase(A[i]-x);
      x++;
    }
    map.erase(A[i]);
    max_sub_within = std::max(max_sub_within, sub_len);

  }
  return max_sub_within;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(
      args, "longest_contained_interval.cc", "longest_contained_interval.tsv",
      &LongestContainedRange, DefaultComparator{}, param_names);
}
