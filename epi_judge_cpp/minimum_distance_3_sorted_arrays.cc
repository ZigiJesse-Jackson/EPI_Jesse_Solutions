#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int FindClosestElementsInSortedArrays(
    const vector<vector<int>> &sorted_arrays)
{
  std::vector<std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>> cmp; 
  for(const vector<int>& v: sorted_arrays) cmp.push_back({v.cbegin(), v.cend()});

  int min_idx, curr_min, curr_max = INT32_MIN, min_interval = INT32_MAX;
  bool isEnd = false;
  while(!isEnd){
    curr_min = INT32_MAX;
    for(int i = 0;i<cmp.size();i++){
      auto p = cmp[i];
      if(*p.first<curr_min) {
        curr_min = *p.first;
        min_idx = i;
      }
      if(*p.first>curr_max) {
        curr_max = *p.first;
      }
    }
    cmp[min_idx].first++;
    min_interval = std::min(min_interval, curr_max-curr_min);
    if(cmp[min_idx].first == cmp[min_idx].second) isEnd = !isEnd;
  }
  return min_interval;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "minimum_distance_3_sorted_arrays.cc",
                         "minimum_distance_3_sorted_arrays.tsv",
                         &FindClosestElementsInSortedArrays,
                         DefaultComparator{}, param_names);
}
