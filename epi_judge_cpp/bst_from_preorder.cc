#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

void insert(BstNode<int> *root, int k)
{
  BstNode<int> *curr = root;

  while (curr)
  {
    if (curr->data > k)
    {
      if (curr->left)
        curr = curr->left.get();
      else
      {
        curr->left = std::make_unique<BstNode<int>>(k);
        return;
      }
    }
    else
    {
      if (curr->right)
        curr = curr->right.get();
      else
      {
        curr->right = std::make_unique<BstNode<int>>(k);
        return;
      }
    }
  }
}

unique_ptr<BstNode<int>> RebuildBSTFromPreorder(
    const vector<int> &preorder_sequence)
{
  if(preorder_sequence.size()==0) return nullptr;
  unique_ptr<BstNode<int>> root = std::make_unique<BstNode<int>>(preorder_sequence[0]);
  for(int i = 1;i<preorder_sequence.size();i++){
    insert(root.get(), preorder_sequence[i]);
  }
  return root;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder_sequence"};
  return GenericTestMain(args, "bst_from_preorder.cc", "bst_from_preorder.tsv",
                         &RebuildBSTFromPreorder, DefaultComparator{},
                         param_names);
}
