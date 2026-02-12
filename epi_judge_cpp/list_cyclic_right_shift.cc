#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"
using std::shared_ptr;

shared_ptr<ListNode<int>> CyclicallyRightShiftList(shared_ptr<ListNode<int>> L,
                                                   int k) {
                                                  
  shared_ptr<ListNode<int>> ahead = L, behind = L, head(new ListNode<int>(0, L));
  if(!L) return nullptr;

  int i = 1;
  while(ahead->next){
    i++;
    ahead = ahead->next;
  }
  int pos = k%i;
  int len = i;
  if(pos == 0) return L;
  i = 1;
  while(i++<len-pos){
    behind = behind->next;
  }

  ahead->next = head->next;
  head->next = behind->next;
  behind->next = nullptr;


  return head->next;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L", "k"};
  return GenericTestMain(
      args, "list_cyclic_right_shift.cc", "list_cyclic_right_shift.tsv",
      &CyclicallyRightShiftList, DefaultComparator{}, param_names);
}
