#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> EvenOddMerge(const shared_ptr<ListNode<int>>& L) {
  // TODO - you fill in here.
  shared_ptr<ListNode<int>> ahead, behind = L, head_even(new ListNode<int>(0, L)), head_odd(new ListNode<int>(0));
  if(!L) return nullptr;
  if(!L->next) return L;
  ahead = L->next;
  head_odd->next = ahead;
  
  while(ahead && ahead->next){
    behind->next = ahead->next;
    behind = behind->next;
    ahead->next = behind->next;
    ahead = ahead->next;
  }
  behind->next = head_odd->next;

  return L;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "even_odd_list_merge.cc",
                         "even_odd_list_merge.tsv", &EvenOddMerge,
                         DefaultComparator{}, param_names);
}
