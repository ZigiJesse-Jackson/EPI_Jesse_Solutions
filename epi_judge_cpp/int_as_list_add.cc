#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> AddTwoNumbers(shared_ptr<ListNode<int>> L1,
                                        shared_ptr<ListNode<int>> L2) {
  // TODO - you fill in here.
  shared_ptr<ListNode<int>> head(new ListNode<int>(0)), it;
  it = head;
  int carry = 0;
  int sum = 0;
  while(L1 || L2){
    sum = 0;
    
    if(L1){
      sum+=L1->data;
      L1 = L1->next;
    }
    if(L2){
      sum+=L2->data;
      L2 = L2->next;
    }
    sum+=carry;
    carry = sum/10;
    it->next = make_shared<ListNode<int>>(ListNode<int>{sum%10, nullptr}); 
    it = it->next;
  }

  if(carry!=0){
    it->next = make_shared<ListNode<int>>(ListNode<int>{carry, nullptr});
  }
  return head->next;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "int_as_list_add.cc", "int_as_list_add.tsv",
                         &AddTwoNumbers, DefaultComparator{}, param_names);
}