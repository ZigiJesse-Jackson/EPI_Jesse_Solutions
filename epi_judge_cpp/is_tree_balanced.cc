#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <algorithm>

int check_height(BinaryTreeNode<int>* node, bool &unbalanced){
  if(!node) return 0;
  int left_height = check_height(node->left.get(), unbalanced)+1;
  int right_height = check_height(node->right.get(), unbalanced)+1;
  int height = std::max(left_height, right_height);
  if(std::abs(left_height-right_height)>1){
    unbalanced = true;
  }
  return height;
}

bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if(!tree.get()) return true;
  bool unbalanced = false;
  check_height(tree.get(), unbalanced);
  // int left_height = check_height(tree->left.get(), unbalanced);
  // int right_height = check_height(tree->right.get(), unbalanced);
  // if(!unbalanced){
  //   unbalanced = std::abs(left_height-right_height)<=1;
  // }
  return !unbalanced;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
