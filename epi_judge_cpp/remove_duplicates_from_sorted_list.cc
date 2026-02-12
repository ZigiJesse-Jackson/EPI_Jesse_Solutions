#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> RemoveDuplicates(const shared_ptr<ListNode<int>>& L) {
  // TODO - you fill in here.
  shared_ptr<ListNode<int>> head(new ListNode<int>(0, L));
  shared_ptr<ListNode<int>> curr = L;
  while(curr){
    if(curr->next && curr->data == curr->next->data){
      curr->next = curr->next->next;
    }
    else{
      curr = curr->next;
    }
  }
  return head->next;
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "remove_duplicates_from_sorted_list.cc",
                         "remove_duplicates_from_sorted_list.tsv",
                         &RemoveDuplicates, DefaultComparator{}, param_names);
}
