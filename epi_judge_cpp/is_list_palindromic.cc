#include "list_node.h"
#include "test_framework/generic_test.h"

int getLenLinkedList(shared_ptr<ListNode<int>> L){
  int i=0;
  while(L){
    i++;
    L = L->next;
  }
  return i;
}


bool CompareLinkedLists( shared_ptr<ListNode<int>> L1, shared_ptr<ListNode<int>> L2){
  while (L1 && L2) {
    if (L1->data != L2->data) return false;
    L1 = L1->next;
    L2 = L2->next;
  }
  
  return !L1 && !L2;
}

bool IsLinkedListAPalindrome(shared_ptr<ListNode<int>> L) {
  int len = getLenLinkedList(L);
  shared_ptr<ListNode<int>> L1 = L;
  shared_ptr<ListNode<int>> L2 = L;
  shared_ptr<ListNode<int>> prev = nullptr;
  int i = 0;
  while(i<(len/2)){
    L2 = L1->next;
    L1->next = prev;
    prev = L1;
    L1 = L2;
    i++;
  }
  if(len%2==1) L2 = L2->next;;
  return CompareLinkedLists(prev, L2);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "is_list_palindromic.cc",
                         "is_list_palindromic.tsv", &IsLinkedListAPalindrome,
                         DefaultComparator{}, param_names);
}
