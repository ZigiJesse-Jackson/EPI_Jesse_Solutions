#include <set>
#include <unordered_set>
#include <stdexcept>

#include "list_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"

int check_len(shared_ptr<ListNode<int>> list){
  if(!list) return 0;
  shared_ptr<ListNode<int>> iterator = list;
  std::unordered_set<shared_ptr<ListNode<int>>> set;
  int counter = 0;
  while(set.insert(iterator).second){
    counter++;
    if(!iterator) return 0;
    iterator = iterator->next;
  }
  return counter;
}

shared_ptr<ListNode<int>> getOverlappingNode(shared_ptr<ListNode<int>> l0,
                                           shared_ptr<ListNode<int>> l1) {
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

shared_ptr<ListNode<int>> OverlappingLists(shared_ptr<ListNode<int>> l0,
                                           shared_ptr<ListNode<int>> l1) {
   shared_ptr<ListNode<int>>  first = l0, second = l1;
  

  int len_first = check_len(first);
  int len_second = check_len(second);
  if(len_first == 0 && len_second == 0) return getOverlappingNode(first, second);
  if(len_first == 0 || len_second == 0) return nullptr;

  
  std::unordered_set<shared_ptr<ListNode<int>>> set1;
  std::unordered_set<shared_ptr<ListNode<int>>> set2;
  bool isNotCycle1 = set1.insert(first).second;
  bool isNotCycle2 = set2.insert(second).second;
  while(isNotCycle1 || isNotCycle2){
    // cycle exists but overlap is experienced before is encountered
    if(set1.find(second)!=set1.end()) return second;
    if(set2.find(first)!=set2.end()) return first;
    // cycle in l0, possible overlap
    if(!isNotCycle1){
      // both enter cycle at same time as they overlap
      if(set1.find(second)!=set1.end()) return second;
      while(isNotCycle2){
        // overlap exists
        if(set1.find(second)!=set1.end()) return second;
        second = second->next;
        isNotCycle2 = set2.insert(second).second;
      } 
      // no overlap exists
      break;
    }
    if(!isNotCycle2){
      if(set2.find(first)!=set2.end()) return first;
      while(isNotCycle1){
        if(set2.find(first)!=set2.end()) return first;
        first = first->next;
        isNotCycle1 = set1.insert(first).second;
        
      } 
      break;
    }
    first = first->next;
    second = second->next;

    isNotCycle1 = set1.insert(first).second;
    isNotCycle2 = set2.insert(second).second;
  }

  return nullptr;
}
void OverlappingListsWrapper(TimedExecutor& executor,
                             shared_ptr<ListNode<int>> l0,
                             shared_ptr<ListNode<int>> l1,
                             shared_ptr<ListNode<int>> common, int cycle0,
                             int cycle1) {
  if (common) {
    if (!l0) {
      l0 = common;
    } else {
      auto it = l0;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }

    if (!l1) {
      l1 = common;
    } else {
      auto it = l1;
      while (it->next) {
        it = it->next;
      }
      it->next = common;
    }
  }

  if (cycle0 != -1 && l0) {
    auto last = l0;
    while (last->next) {
      last = last->next;
    }
    auto it = l0;
    while (cycle0-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  if (cycle1 != -1 && l1) {
    auto last = l1;
    while (last->next) {
      last = last->next;
    }
    auto it = l1;
    while (cycle1-- > 0) {
      if (!it) {
        throw std::runtime_error("Invalid input data");
      }
      it = it->next;
    }
    last->next = it;
  }

  std::set<shared_ptr<ListNode<int>>> common_nodes;
  auto it = common;
  while (it && common_nodes.count(it) == 0) {
    common_nodes.insert(it);
    it = it->next;
  }

  auto result = executor.Run([&] { return OverlappingLists(l0, l1); });

  if (!((common_nodes.empty() && result == nullptr) ||
        common_nodes.count(result) > 0)) {
    throw TestFailure("Invalid result");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "l0",     "l1",
                                       "common",   "cycle0", "cycle1"};
  return GenericTestMain(args, "do_lists_overlap.cc", "do_lists_overlap.tsv",
                         &OverlappingListsWrapper, DefaultComparator{},
                         param_names);
}
