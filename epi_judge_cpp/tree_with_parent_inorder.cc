#include <vector>

#include "binary_tree_with_parent_prototype.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>> &tree)
{
  // TODO - you fill in here.
  BinaryTreeNode<int> *curr = tree.get();
  BinaryTreeNode<int> *prev = nullptr;
  vector<int> res;

  while (curr)
  {
    // left subtree unexplored
    if (prev == curr->parent)
    {
      // node has left subtree
      if (curr->left)
      {
        prev = curr;
        curr = curr->left.get();
      }
      // node does not have left subtree
      else
      {
        res.push_back(curr->data);
        prev = curr;
        // go to right subtree if it exists, else go up
        curr = curr->right? curr->right.get():curr->parent;
      }
    }
    // coming up from left subtree
    else if(prev == curr->left.get())
    {
      res.push_back(curr->data);
      prev = curr;
      // go to right subtree if it exists, else go up
      curr = curr->right? curr->right.get():curr->parent;
    }
    // coming up from right subtree
    else
    {
      prev = curr;
      curr = curr->parent;
    }
    
  }
  return res;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_with_parent_inorder.cc",
                         "tree_with_parent_inorder.tsv", &InorderTraversal,
                         DefaultComparator{}, param_names);
}
