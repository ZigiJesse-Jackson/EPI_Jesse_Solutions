#include <string>
#include <vector>
#include <list>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

struct Subarray
{
  // Represent subarray by starting and ending indices, inclusive.
  int start, end;
};

Subarray FindSmallestSequentiallyCoveringSubset(
    const vector<string> &paragraph, const vector<string> &keywords)
{
  int min_dist = INT32_MAX;
  std::unordered_map<string, int> k_map;
  vector<int> latest_occurence(keywords.size(), -1);
  vector<int> shortest_subarray_length_at_idx(keywords.size(), INT32_MAX);

  for(int i=0;i<keywords.size();i++){
    k_map[keywords[i]] = i;
  }

  Subarray sub;
  for (int i = 0; i < paragraph.size(); i++)
  {
    if(k_map.find(paragraph[i])!=k_map.end()){
      int k_idx = k_map[paragraph[i]];
      if(k_idx==0){
        shortest_subarray_length_at_idx[k_idx] = 1;
      }else if(shortest_subarray_length_at_idx[k_idx-1]<INT32_MAX){
        int dist_to_prev_kword = i - latest_occurence[k_idx-1];
        shortest_subarray_length_at_idx[k_idx] = dist_to_prev_kword + shortest_subarray_length_at_idx[k_idx-1];
      }
      latest_occurence[k_idx] = i;

      if(k_idx == keywords.size()-1 && shortest_subarray_length_at_idx.back()<min_dist){
        min_dist = shortest_subarray_length_at_idx.back();
        sub.start = i - shortest_subarray_length_at_idx.back()+1;
        sub.end = i;
      }
    }
  }
  return sub;
}
int FindSmallestSequentiallyCoveringSubsetWrapper(
    TimedExecutor &executor, const vector<string> &paragraph,
    const vector<string> &keywords)
{
  auto result = executor.Run([&]
                             { return FindSmallestSequentiallyCoveringSubset(paragraph, keywords); });

  int kw_idx = 0;
  if (result.start < 0)
  {
    throw TestFailure("Subarray start index is negative");
  }
  int para_idx = result.start;

  while (kw_idx < keywords.size())
  {
    if (para_idx >= paragraph.size())
    {
      throw TestFailure("Not all keywords are in the generated subarray");
    }
    if (para_idx >= paragraph.size())
    {
      throw TestFailure("Subarray end index exceeds array size");
    }
    if (paragraph[para_idx] == keywords[kw_idx])
    {
      kw_idx++;
    }
    para_idx++;
  }
  return result.end - result.start + 1;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "paragraph", "keywords"};
  return GenericTestMain(args, "smallest_subarray_covering_all_values.cc",
                         "smallest_subarray_covering_all_values.tsv",
                         &FindSmallestSequentiallyCoveringSubsetWrapper,
                         DefaultComparator{}, param_names);
}
