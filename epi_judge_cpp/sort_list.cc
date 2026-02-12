#include <memory>

#include "list_node.h"
#include "test_framework/generic_test.h"

shared_ptr<ListNode<int>> Split(shared_ptr<ListNode<int>> H)
{
  if (!H || !H->next) return nullptr;

  shared_ptr<ListNode<int>> fast = H->next;
  shared_ptr<ListNode<int>> slow = H;

  while(fast && fast->next)
  {
    fast = fast->next->next;
    slow = slow->next;
  }
  shared_ptr<ListNode<int>> next_head = slow->next;
  slow->next = nullptr;
  return next_head;
}

shared_ptr<ListNode<int>> StableSortList(shared_ptr<ListNode<int>> L)
{
  if(!L || !L->next) return L;
  shared_ptr<ListNode<int>> L2 = Split(L);
  L = StableSortList(L);
  L2 = StableSortList(L2);

  if(L->data > L2->data) std::swap(L, L2);
  shared_ptr<ListNode<int>> new_L = std::make_shared<ListNode<int>>(0);
  shared_ptr<ListNode<int>> curr = new_L;

  while(L || L2)
  {
    if(!L2) {
      curr->next = L;
      break;
    }
    if(!L)
    {
      curr->next = L2;
      break;
    }
    if(L->data<=L2->data)
    {
      curr->next = L;
      curr = curr->next;
      L = L->next;
    }else{
      curr->next = L2;
      curr = curr->next;
      L2 = L2->next;
    }
  }
  
  return new_L->next;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L"};
  return GenericTestMain(args, "sort_list.cc", "sort_list.tsv", &StableSortList,
                         DefaultComparator{}, param_names);
}
