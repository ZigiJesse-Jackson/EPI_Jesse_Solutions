#include <vector>
#include <queue>
#include <utility>
#include "test_framework/generic_test.h"
using std::vector;

struct vect_iterator{
  vector<int>::const_iterator current;
  vector<int>::const_iterator end;

  bool operator>(const vect_iterator& other) const{
    return *current > *other.current;
  }
};

vector<int> MergeSortedArrays(const vector<vector<int>> &sorted_arrays)
{
  // TODO - you fill in here.
  std::priority_queue<vect_iterator, vector<vect_iterator>, std::greater<>> min_heap;
  vector<int> res;
  for (const vector<int>& v : sorted_arrays)
  {
    if (!v.empty())
    {
      min_heap.emplace(vect_iterator{v.cbegin(), v.cend()});
    }
  }
  while (!min_heap.empty())
  {
    res.push_back(*min_heap.top().current);
    auto next = min_heap.top();
    min_heap.pop();
    if(++next.current!=next.end) min_heap.push(next);
  }
  return res;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sorted_arrays"};
  return GenericTestMain(args, "sorted_arrays_merge.cc",
                         "sorted_arrays_merge.tsv", &MergeSortedArrays,
                         DefaultComparator{}, param_names);
}
