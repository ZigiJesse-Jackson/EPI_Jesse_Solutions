#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

// My old solution
// int pickCoin(const vector<int> &coins, int start_idx, int end_idx, bool isP1, vector<vector<int>> &memo_dp)
// {
//   if ((end_idx - start_idx) + 1 == 0)
//   {
//     return 0;
//   }

//   if ((end_idx - start_idx) + 1 == 1)
//   {
//     if (isP1)
//     {
//       return coins[start_idx];
//     }
//     return 0;
//   }

//   if (memo_dp[start_idx][end_idx] >= 0)
//   {
//     return memo_dp[start_idx][end_idx];
//   }
//   else
//   {
//     if (isP1)
//     {
//       memo_dp[start_idx][end_idx] = std::max(
//           coins[start_idx] + pickCoin(coins, start_idx + 1, end_idx, !isP1, memo_dp),
//           coins[end_idx] + pickCoin(coins, start_idx, end_idx - 1, !isP1, memo_dp));
//     }
//     else
//     {
//       memo_dp[start_idx][end_idx] = std::min(
//           pickCoin(coins, start_idx + 1, end_idx, !isP1, memo_dp),
//           pickCoin(coins, start_idx, end_idx - 1, !isP1, memo_dp));
//     }
//   }

//   return memo_dp[start_idx][end_idx];
// }

int MaximumRevenue(const vector<int> &coins)
{
  int n = coins.size();
  if (n == 0)
    return 0;

  vector<vector<int>> dp(n, vector<int>(n, 0));

  // Base cases
  for (int i = 0; i < n; i++)
  {
    dp[i][i] = coins[i]; // one coin
  }

  for (int i = 0; i < n - 1; i++)
  {
    dp[i][i + 1] = std::max(coins[i], coins[i + 1]); // two coins
  }

  // Fill for lengths 3 to n
  for (int length = 3; length <= n; length++)
  {
    for (int start_idx = 0; start_idx + length - 1 < n; start_idx++)
    {
      int end_idx = start_idx + length - 1;

      // Option 1: pick coins[start_idx]
      int pickLeft = coins[start_idx] + std::min(
                                            (start_idx + 2 <= end_idx) ? dp[start_idx + 2][end_idx] : 0,
                                            (start_idx + 1 <= end_idx - 1) ? dp[start_idx + 1][end_idx - 1] : 0);

      // Option 2: pick coins[end_idx]
      int pickRight = coins[end_idx] + std::min(
                                           (start_idx + 1 <= end_idx - 1) ? dp[start_idx + 1][end_idx - 1] : 0,
                                           (start_idx <= end_idx - 2) ? dp[start_idx][end_idx - 2] : 0);

      dp[start_idx][end_idx] = std::max(pickLeft, pickRight);
    }
  }

  return dp[0][n - 1];
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"coins"};
  return GenericTestMain(args, "picking_up_coins.cc", "picking_up_coins.tsv",
                         &MaximumRevenue, DefaultComparator{}, param_names);
}
