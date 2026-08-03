#include "test_framework/generic_test.h"

int countNumWays(int top, int maximum_step, std::vector<int> *const memo)
{
  if (top <= 1)
    return 1;

  if ((*memo)[top] == 0)
  {
    int numWays = 0;
    // Bound subtraction so top-i >= 0
    for (int i = 1; i <= maximum_step && i <= top; i++)
    {
      numWays += countNumWays(top - i, maximum_step, memo);
    }
    (*memo)[top] = numWays;
  }
  return (*memo)[top];
}

int NumberOfWaysToTop(int top, int maximum_step)
{
  std::vector<int> memo(top + 1, 0);
  return countNumWays(top, maximum_step, &memo);
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"top", "maximum_step"};
  return GenericTestMain(args, "number_of_traversals_staircase.cc",
                         "number_of_traversals_staircase.tsv",
                         &NumberOfWaysToTop, DefaultComparator{}, param_names);
}
