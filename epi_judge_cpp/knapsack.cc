#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Item
{
  int weight, value;
};

int OptimumSubjectToCapacity(const vector<Item> &items, int capacity)
{
  vector<vector<int>> dp(items.size(), vector<int>(capacity + 1, 0));
  for (int i = 0; i < items.size(); i++)
  {
    int curr_weight = items[i].weight;
    int curr_value = items[i].value;
    for (int c = 1; c <= capacity; c++)
    {

      if (i == 0)
      {
        if (curr_weight <= c)
        {
          dp[i][c] = curr_value;
        }
      }
      else
      {
        if (c - curr_weight >= 0)
        {
          // max of not taking curr item or taking curr item with best of reduced capcacity
          dp[i][c] = std::max(dp[i - 1][c], curr_value + dp[i - 1][c - curr_weight]);
        }
        else
        {
          dp[i][c] = dp[i - 1][c];
        }
      }
    }
  }
  return dp[items.size() - 1][capacity];
}
namespace test_framework
{
  template <>
  struct SerializationTrait<Item> : UserSerTrait<Item, int, int>
  {
  };
} // namespace test_framework

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"items", "capacity"};
  return GenericTestMain(args, "knapsack.cc", "knapsack.tsv",
                         &OptimumSubjectToCapacity, DefaultComparator{},
                         param_names);
}
