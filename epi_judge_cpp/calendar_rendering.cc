#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::vector;

struct Event
{
  int start, finish;
};
int FindMaxSimultaneousEvents(const vector<Event> &A)
{
  std::vector<std::pair<int, bool>> time_points;
  for (Event e : A)
  {
    time_points.push_back({e.start, true});
    time_points.push_back({e.finish, false});
  }

  std::sort(time_points.begin(), time_points.end(), [](const std::pair<int, bool> &a, const std::pair<int, bool> &b)
            { return a.first!=b.first? a.first < b.first : a.second && !b.second; });
  int max_sim_events = 0, curr_sim_events = 0;
  for (int i = 0; i < time_points.size(); i++)
  {
    if (time_points[i].second == true)
    {
      curr_sim_events++;
      max_sim_events = std::max(max_sim_events, curr_sim_events);
      
    }
    else
      curr_sim_events--;
  }
  return max_sim_events;
}
namespace test_framework
{
  template <>
  struct SerializationTrait<Event> : UserSerTrait<Event, int, int>
  {
  };
} // namespace test_framework

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "calendar_rendering.cc",
                         "calendar_rendering.tsv", &FindMaxSimultaneousEvents,
                         DefaultComparator{}, param_names);
}
