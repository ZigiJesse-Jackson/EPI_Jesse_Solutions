#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int GetMaxTrappedWater(const vector<int> &heights)
{
  int l = 0, r = heights.size() - 1;
  int max_trapped = 0;
  while (l < r)
  {
    max_trapped = std::max(max_trapped, (std::min(heights[l], heights[r]) * (r - l)));
    if (heights[l] < heights[r])
    {
      l++;
    }
    else
    {
      r--;
    }
  }
  return max_trapped;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "max_trapped_water.cc", "max_trapped_water.tsv",
                         &GetMaxTrappedWater, DefaultComparator{}, param_names);
}
