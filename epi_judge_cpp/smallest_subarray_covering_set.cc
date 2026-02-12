#include <string>
#include <unordered_set>
#include <unordered_map>
#include <list>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

struct Subarray
{
  int start, end;
};

Subarray FindSmallestSubarrayCoveringSet(
    const vector<string> &paragraph, const unordered_set<string> &keywords)
{

  std::unordered_map<string, int> map;
  int earliest_idx = -1, min_dist = INT32_MAX;
  Subarray sub = {INT32_MIN, INT32_MAX};
  for (int i = 0; i < paragraph.size(); i++)
  {
    string curr_word = paragraph[i];
    if (keywords.find(curr_word) != keywords.end())
    {
      if (map.find(curr_word) == map.end())
        map[curr_word] = 0;
      map[curr_word]++;
      if (earliest_idx == -1)
        earliest_idx = i;
    }

    if (map.size() == keywords.size())
    {
      while (map.size() == keywords.size())
      {
        if (map.find(paragraph[earliest_idx]) != map.end())
        {
          if (min_dist > (i - earliest_idx))
          {
            min_dist = i - earliest_idx;
            sub.start = earliest_idx;
            sub.end = i;
          }
          map[paragraph[earliest_idx]]--;
          if (map[paragraph[earliest_idx]] == 0)
            map.erase(paragraph[earliest_idx]);
        }
        earliest_idx++;
      }
      while (keywords.find(paragraph[earliest_idx]) == keywords.end() && earliest_idx<i)
        earliest_idx++;
    }
  }
  return sub;
}
int FindSmallestSubarrayCoveringSetWrapper(
    TimedExecutor &executor, const vector<string> &paragraph,
    const unordered_set<string> &keywords)
{
  unordered_set<string> copy = keywords;

  auto result = executor.Run(
      [&]
      { return FindSmallestSubarrayCoveringSet(paragraph, keywords); });

  if (result.start < 0 || result.start >= paragraph.size() || result.end < 0 ||
      result.end >= paragraph.size() || result.start > result.end)
  {
    throw TestFailure("Index out of range");
  }

  for (int i = result.start; i <= result.end; i++)
  {
    copy.erase(paragraph[i]);
  }

  if (!copy.empty())
  {
    throw TestFailure("Not all keywords are in the range");
  }

  return result.end - result.start + 1;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_set.cc",
                         "smallest_subarray_covering_set.tsv",
                         &FindSmallestSubarrayCoveringSetWrapper,
                         DefaultComparator{}, param_names);
}
