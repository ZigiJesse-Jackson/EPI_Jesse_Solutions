#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <algorithm>

bool check_symmetry(BinaryTreeNode<int>* left_node, BinaryTreeNode<int>* right_node){
  if(!left_node && !right_node) return true;
  if(!left_node || !right_node) return false;
  if(left_node->data != right_node->data) return false;

  bool lhs = check_symmetry(left_node->left.get(), right_node->right.get());
  bool rhs = check_symmetry(left_node->right.get(), right_node->left.get());

  return lhs && rhs;
}

bool IsSymmetric(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  if(!tree.get()) return true;
  bool symmetric = check_symmetry(tree->left.get(), tree->right.get());
  return symmetric;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_symmetric.cc", "is_tree_symmetric.tsv",
                         &IsSymmetric, DefaultComparator{}, param_names);
}
