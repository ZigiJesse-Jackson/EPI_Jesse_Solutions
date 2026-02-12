#include <vector>
#include <queue>
#include <iostream>

#include "test_framework/generic_test.h"
using std::vector;

vector<double> OnlineMedian(vector<int>::const_iterator sequence_begin,
                            const vector<int>::const_iterator &sequence_end)
{

  std::priority_queue<int, vector<int>, std::greater<int>> min_heap;
  std::priority_queue<int, vector<int>, std::less<int>> max_heap;
  vector<double> res;
  max_heap.push(*sequence_begin);
  res.push_back(*sequence_begin);
  sequence_begin = std::next(sequence_begin);

  while (sequence_begin != sequence_end)
  {
    int curr = *sequence_begin;
    sequence_begin = std::next(sequence_begin);
    if (max_heap.top() > curr)
      max_heap.push(curr);
    else
      min_heap.push(curr);
    int diff = max_heap.size() - min_heap.size();
    // rebalancing
    if (diff > 1)
    {
      while (diff > 1)
      {
        min_heap.push(max_heap.top());
        max_heap.pop();
        diff = max_heap.size() - min_heap.size();
      }
    }
    else if (diff < -1)
    {
      while (diff < -1)
      {
        max_heap.push(min_heap.top());
        min_heap.pop();
        diff = max_heap.size() - min_heap.size();
      }
    }
    if (diff == 0)
    {
      res.push_back((max_heap.top() + min_heap.top()) *0.5);
    }
    if (diff == 1)
      res.push_back(max_heap.top());
    if (diff == -1)
      res.push_back(min_heap.top());
  }
  return res;
}
vector<double> OnlineMedianWrapper(const vector<int> &sequence)
{
  return OnlineMedian(cbegin(sequence), cend(sequence));
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "online_median.cc", "online_median.tsv",
                         &OnlineMedianWrapper, DefaultComparator{},
                         param_names);
}
