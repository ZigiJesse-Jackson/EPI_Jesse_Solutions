#include <memory>
#include <algorithm>
#include <unordered_set>
#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::shared_ptr;


shared_ptr<ListNode<int>> OverlappingNoCycleLists(
    shared_ptr<ListNode<int>> l0, shared_ptr<ListNode<int>> l1) {
  shared_ptr<ListNode<int>>  first = l0, second = l1, checker;
  std::unordered_set<shared_ptr<ListNode<int>>> set;
  bool isOverlapping = false;
  int count1=0, count2=0;
  while(first || second){

    if(first) {
      isOverlapping = !set.insert(first).second;
      if(isOverlapping) return first;
      first = first->next;
      
      count1++;
    }
    if(second){
      isOverlapping = !set.insert(second).second;
      if(isOverlapping) return second;
      second = second->next;
      count2++;
    }
    
  }
  return nullptr;
}
void OverlappingNoCycleListsWrapper(TimedExecutor& executor,
                                    shared_ptr<ListNode<int>> l0,
                                    shared_ptr<ListNode<int>> l1,
                                    shared_ptr<ListNode<int>> common) {
  if (common) {
    if (l0) {
      auto i = l0;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l0 = common;
    }

    if (l1) {
      auto i = l1;
      while (i->next) {
        i = i->next;
      }
      i->next = common;
    } else {
      l1 = common;
    }
  }

  auto result = executor.Run([&] { return OverlappingNoCycleLists(l0, l1); });

  if (result != common) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0", "l1", "common"};
  return GenericTestMain(
      args, "do_terminated_lists_overlap.cc", "do_terminated_lists_overlap.tsv",
      &OverlappingNoCycleListsWrapper, DefaultComparator{}, param_names);
}
