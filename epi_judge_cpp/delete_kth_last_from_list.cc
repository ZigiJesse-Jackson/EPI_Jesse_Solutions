#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

// Assumes L has at least k nodes, deletes the k-th last node in L.
shared_ptr<ListNode<int>> RemoveKthLast(const shared_ptr<ListNode<int>>& L,
                                        int k) {
  // TODO - you fill in here.
  shared_ptr<ListNode<int>> head(new ListNode<int>(0, L));
  shared_ptr<ListNode<int>> ahead = L;
  shared_ptr<ListNode<int>> behind = head;
  
  for(int i=0;i<k;i++){
    ahead = ahead->next;
  }
  while(ahead){
    ahead = ahead->next;
    behind = behind->next;
  }
  behind->next = behind->next->next;
  return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(args, "delete_kth_last_from_list.cc",
                         "delete_kth_last_from_list.tsv", &RemoveKthLast,
                         DefaultComparator{}, param_names);
}
