#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
using std::vector;

struct vec_itr_heap
{
  vector<int>::const_iterator curr_itr;

  bool operator>(const vec_itr_heap& other) const
  {
    return *curr_itr>*other.curr_itr;
  }
};

vector<int> SortApproximatelySortedData(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator &sequence_end, int k)
{

  std::priority_queue<vec_itr_heap, vector<vec_itr_heap>, std::greater<>> min_heap;
  vector<int> res;
  while (sequence_begin != sequence_end || !min_heap.empty())
  {
    if (sequence_begin != sequence_end && min_heap.size() < k)
    {
      min_heap.emplace(vec_itr_heap{sequence_begin});
      sequence_begin = std::next(sequence_begin);
    }
    else
    {
      res.push_back(*min_heap.top().curr_itr);
      min_heap.pop();
    }
  }
  return res;
}
vector<int> SortApproximatelySortedDataWrapper(const vector<int> &sequence,
                                               int k)
{
  return SortApproximatelySortedData(cbegin(sequence), cend(sequence), k);
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence", "k"};
  return GenericTestMain(
      args, "sort_almost_sorted_array.cc", "sort_almost_sorted_array.tsv",
      &SortApproximatelySortedDataWrapper, DefaultComparator{}, param_names);
}
