#include <vector>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::vector;

int MinimumTotalWaitingTime(vector<int> service_times)
{
  if (service_times.empty())
    return 0;
  std::sort(service_times.begin(), service_times.end());
  int res = 0;
  int sum = 0;
  for (int i = 0; i < service_times.size() - 1; i++)
  {
    sum += service_times[i];
    res += sum;
  }
  return res;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"service_times"};
  return GenericTestMain(args, "minimum_waiting_time.cc",
                         "minimum_waiting_time.tsv", &MinimumTotalWaitingTime,
                         DefaultComparator{}, param_names);
}
