#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Interval
{
  int left, right;
};

int FindMinimumVisits(vector<Interval> intervals)
{
  std::sort(intervals.begin(), intervals.end(), [](const Interval &A, const Interval &B)
            { return A.right < B.right; });

  int i = 0, res = 0, start, end;
  while (i < intervals.size())
  {
    res += 1;
    start = intervals[i].left;
    end = intervals[i].right;

    while (++i < intervals.size() && intervals[i].left <= end)
      ;
  }
  return res;
}
namespace test_framework
{
  template <>
  struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int>
  {
  };
} // namespace test_framework

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"intervals"};
  return GenericTestMain(args, "minimum_points_covering_intervals.cc",
                         "minimum_points_covering_intervals.tsv",
                         &FindMinimumVisits, DefaultComparator{}, param_names);
}
