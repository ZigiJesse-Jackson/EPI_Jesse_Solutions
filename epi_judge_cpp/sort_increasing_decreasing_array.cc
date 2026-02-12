#include <vector>
#include <queue>
#include "test_framework/generic_test.h"
using std::vector;

struct vec_iter
{
  std::vector<int>::const_iterator start;
  std::vector<int>::const_iterator end;
  bool reverse;
  bool operator>(const vec_iter &other) const
  {
    return *start > *other.start;
  }
};

vector<int> SortKIncreasingDecreasingArray(const vector<int> &A)
{
  bool reverse = false;
  int curr = 0;
  std::priority_queue<vec_iter, vector<vec_iter>, std::greater<>> min_heap;
  for (int i = 1; i < A.size(); i++)
  {
    if (!reverse && A[i - 1] > A[i])
    {
      min_heap.emplace(vec_iter{A.begin() + curr, A.begin() + i - 1, reverse});
      curr = i;
      reverse = !reverse;
    }
    else if (reverse && A[i - 1] <= A[i])
    {
      min_heap.emplace(vec_iter{A.begin() + i - 1, A.begin() + curr,  reverse});
      curr = i;
      reverse = !reverse;
    }
  }

  if (!reverse)
    {
      min_heap.emplace(vec_iter{A.begin() + curr, A.begin() + A.size()-1, reverse});
    }
    else 
    {
      min_heap.emplace(vec_iter{A.begin()+ A.size() - 1, A.begin() + curr,  reverse});
    }


  vector<int> res;
  while (!min_heap.empty())
  {
    auto curr = min_heap.top();
    min_heap.pop();
    res.push_back(*curr.start);
    if (curr.start != curr.end)
    {
      if (!curr.reverse)
      {
        min_heap.emplace(vec_iter{std::next(curr.start), curr.end, curr.reverse});
      }
      else
      {
        min_heap.emplace(vec_iter{std::prev(curr.start), curr.end, curr.reverse});
      }
    }
  }

  return res;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "sort_increasing_decreasing_array.cc",
                         "sort_increasing_decreasing_array.tsv",
                         &SortKIncreasingDecreasingArray, DefaultComparator{},
                         param_names);
}
