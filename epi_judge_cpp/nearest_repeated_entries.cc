#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int FindNearestRepetition(const vector<string> &paragraph)
{
  std::unordered_map<string, int> map;
  int min_dist = -1;
  for (int i = 0; i < paragraph.size(); i++)
  {
    if (map.find(paragraph[i]) == map.end())
    {
      map[paragraph[i]] = i;
    }
    else
    {
      if (min_dist == -1)
        min_dist = i - map[paragraph[i]];
      else
        min_dist = std::min(min_dist, i - map[paragraph[i]]);
      map[paragraph[i]] = i;
    }
  }
  return min_dist;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"paragraph"};
  return GenericTestMain(args, "nearest_repeated_entries.cc",
                         "nearest_repeated_entries.tsv", &FindNearestRepetition,
                         DefaultComparator{}, param_names);
}
