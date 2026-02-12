#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> ReverseList(shared_ptr<ListNode<int>> L){
  if(!L) return nullptr;
  shared_ptr<ListNode<int>> curr, prev, next;
  curr = L;
  while(curr!=nullptr){
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }  
  return prev;
}

shared_ptr<ListNode<int>> ReverseSublist(shared_ptr<ListNode<int>> L, int start,
                                         int finish) {
  shared_ptr<ListNode<int>> start_node, finish_node, L_before_start_node, L_after_start_node, curr;
  shared_ptr<ListNode<int>> head(new ListNode<int>);
  if (!L || start == finish) return L;
  head->next = L;
  L_before_start_node = head;
  for(int i=1;i<start;i++){
    L_before_start_node = L_before_start_node->next;
  }
  start_node = L_before_start_node->next;
  finish_node = start_node;
  for(int i=start;i<finish;i++) finish_node = finish_node->next;
  L_after_start_node = finish_node->next;
  finish_node->next = nullptr;

  L_before_start_node->next = ReverseList(start_node);;
  while(L_before_start_node->next!=nullptr){
    L_before_start_node = L_before_start_node->next;
  }
  L_before_start_node->next = L_after_start_node;

  return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "start", "finish"};
  return GenericTestMain(args, "reverse_sublist.cc", "reverse_sublist.tsv",
                         &ReverseSublist, DefaultComparator{}, param_names);
}
