#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::vector;

vector<int> PreorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  if(!tree) return {};
  vector<BinaryTreeNode<int>*> stack;
  vector<int> res;
  stack.push_back(tree.get());
  BinaryTreeNode<int>* curr;
  while(!stack.empty()){
    curr = stack.back();
    stack.pop_back();
    res.push_back(curr->data);
    if(curr->right) stack.push_back(curr->right.get());
    if(curr->left) stack.push_back(curr->left.get());
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_preorder.cc", "tree_preorder.tsv",
                         &PreorderTraversal, DefaultComparator{}, param_names);
}
