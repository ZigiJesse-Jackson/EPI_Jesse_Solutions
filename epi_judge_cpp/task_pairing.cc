#include <tuple>
#include <vector>
#include <algorithm>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct PairedTasks
{
  int task_1, task_2;
};

vector<PairedTasks> OptimumTaskAssignment(vector<int> task_durations)
{
  std::sort(task_durations.begin(), task_durations.end());
  std::vector<PairedTasks> res(task_durations.size() / 2, PairedTasks{});
  int x = 0;
  for (int i = 0; i < res.size(); i++)
  {
    res[i].task_1 = task_durations[x++];
  }
  for (int i = x; i < task_durations.size(); i++)
  {
    res[--x].task_2 = task_durations[i];
  }
  return res;
}

namespace test_framework
{
  template <>
  struct SerializationTrait<PairedTasks> : UserSerTrait<PairedTasks, int, int>
  {
  };
} // namespace test_framework

bool operator==(const PairedTasks &lhs, const PairedTasks &rhs)
{
  return std::tie(lhs.task_1, lhs.task_2) == std::tie(rhs.task_1, rhs.task_2);
}

std::ostream &operator<<(std::ostream &out, const PairedTasks &t)
{
  return PrintTo(out, std::make_tuple(t.task_1, t.task_2));
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"task_durations"};
  return GenericTestMain(args, "task_pairing.cc", "task_pairing.tsv",
                         &OptimumTaskAssignment, DefaultComparator{},
                         param_names);
}
