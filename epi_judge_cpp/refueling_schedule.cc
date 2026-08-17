#include <vector>

#include "test_framework/fmt_print.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;
const int kMPG = 20;

// gallons[i] is the amount of gas in city i, and distances[i] is the distance
// city i to the next city.
// int FindAmpleCity(const vector<int> &gallons, const vector<int> &distances)
// {

//   for (int i = 0; i < distances.size(); i++)
//   {
//     double tank = gallons[i];
//     if (tank < distances[i] / 20.0)
//       continue;
//     int x = i + 1 < distances.size() ? i + 1 : 0;
//     tank -= distances[i] / 20.0;
//     while (i != x)
//     {
//       // refill
//       tank += gallons[x];
//       tank -= distances[x] / 20.0;
//       if (tank < 0)
//         break;
//       x = x + 1 < distances.size() ? x + 1 : 0;
//     }
//     if (i == x)
//       return i;
//   }
//   return 0;
// }

int FindAmpleCity(const vector<int> &gallons, const vector<int> &distances)
{

  int current_gas = 0, start_idx = 0;
  for (int i = 0; i < distances.size(); i++)
  {
    current_gas += (gallons[i] - (distances[i] / 20));
    if (current_gas < 0)
    {
      current_gas = 0;
      start_idx = i + 1;
    }
  }
  return start_idx;
}
void FindAmpleCityWrapper(TimedExecutor &executor, const vector<int> &gallons,
                          const vector<int> &distances)
{
  int result = executor.Run([&]
                            { return FindAmpleCity(gallons, distances); });
  const int num_cities = gallons.size();
  int tank = 0;
  for (int i = 0; i < num_cities; ++i)
  {
    int city = (result + i) % num_cities;
    tank += gallons[city] * kMPG - distances[city];
    if (tank < 0)
    {
      throw TestFailure(FmtStr("Out of gas on city {}", i));
    }
  }
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "gallons", "distances"};
  return GenericTestMain(args, "refueling_schedule.cc",
                         "refueling_schedule.tsv", &FindAmpleCityWrapper,
                         DefaultComparator{}, param_names);
}
