#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
using std::vector;
struct candidate{
  int index;
  int value;
  bool operator<(const candidate &other)const{
    return value<other.value;
  }
};

vector<int> KLargestInBinaryHeap(const vector<int>& A, int k) {
  if(k>=A.size()) return A;
  vector<int> res;
  std::priority_queue<candidate, vector<candidate>, std::less<>> max_heap;
  max_heap.push({0, A[0]});
  while(res.size()!=k){
    auto curr_candidate = max_heap.top();
    res.push_back(max_heap.top().value);
    max_heap.pop();
    int l_child_idx = (2*(curr_candidate.index+1))-1;
    int r_child_idx = l_child_idx+1;
    if(l_child_idx<A.size()){
      max_heap.emplace(candidate{l_child_idx, A[l_child_idx]});
    }
    if(r_child_idx<A.size()){
      max_heap.emplace(candidate{r_child_idx, A[r_child_idx]});
    }
    
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "k"};
  return GenericTestMain(args, "k_largest_in_heap.cc", "k_largest_in_heap.tsv",
                         &KLargestInBinaryHeap, UnorderedComparator{},
                         param_names);
}
