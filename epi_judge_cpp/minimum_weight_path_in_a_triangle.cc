#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int MinimumPathWeight(const vector<vector<int>> &triangle)
{
  if (triangle.empty())
    return 0;
  // base case
  vector<int> res = triangle.front();
  // std::cout << std::endl
  //           << res.size() << std::endl;

  // prefix/suffix sub problem division
  for (int r = 1; r < triangle.size(); r++)
  {
    vector<int> level = triangle[r];
    // memo_pad
    vector<int> intermediate(level.size(), INT_MAX);
    for (int i = 0; i < res.size(); i++)
    {
      // adjacent btw current and previous level
      intermediate[i] = std::min(res[i] + level[i], intermediate[i]);
      // adjacent by current level
      intermediate[i + 1] = std::min(res[i] + level[i + 1], intermediate[i + 1]);
    }
    res = intermediate;
  }

  return *std::min_element(res.begin(), res.end());
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"triangle"};
  return GenericTestMain(args, "minimum_weight_path_in_a_triangle.cc",
                         "minimum_weight_path_in_a_triangle.tsv",
                         &MinimumPathWeight, DefaultComparator{}, param_names);
}
