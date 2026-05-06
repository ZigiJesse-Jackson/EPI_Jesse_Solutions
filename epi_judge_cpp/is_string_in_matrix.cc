#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
bool IsPatternContainedInGrid(const vector<vector<int>> &grid,
                              const vector<int> &pattern)
{

  vector<vector<vector<bool>>> dp(pattern.size(), vector<vector<bool>>(grid.size(), vector<bool>(grid[0].size(), false)));

  for (int i = 0; i < pattern.size(); i++)
  {
    for (int r = 0; r < grid.size(); r++)
    {
      for (int c = 0; c < grid[0].size(); c++)
      {
        // base case: start of sequence found in grid
        if (i == 0)
        {
          if (grid[r][c] == pattern[i])
          {
            dp[i][r][c] = true;
          }
          if (i == pattern.size() - 1 && dp[i][r][c])
          {
            return dp[i][r][c];
          }
          continue;
        }
        // relation: current sequence character found in grid
        if (pattern[i] == grid[r][c])
        {
          if (r + 1 < grid.size())
          {
            dp[i][r][c] = dp[i - 1][r + 1][c] || dp[i][r][c];
          }
          if (r - 1 >= 0)
          {
            dp[i][r][c] = dp[i - 1][r - 1][c] || dp[i][r][c];
          }
          if (c + 1 < grid[0].size())
          {
            dp[i][r][c] = dp[i - 1][r][c + 1] || dp[i][r][c];
          }
          if (c - 1 >= 0)
          {
            dp[i][r][c] = dp[i - 1][r][c - 1] || dp[i][r][c];
          }

          if (i == pattern.size() - 1 && dp[i][r][c])
          {
            return dp[i][r][c];
          }
        }
      }
    }
  }

  return false;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"grid", "pattern"};
  return GenericTestMain(args, "is_string_in_matrix.cc",
                         "is_string_in_matrix.tsv", &IsPatternContainedInGrid,
                         DefaultComparator{}, param_names);
}
