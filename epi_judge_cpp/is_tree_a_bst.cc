#include <memory>
#include <stack>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool checkBST(const unique_ptr<BinaryTreeNode<int>>& node, int min, int max){
  if(node == nullptr) return true;
  if(node->data < min || node->data > max) return false;
  bool isBST = checkBST(node->left, min, node->data) && checkBST(node->right, node->data, max);
  return isBST;
}

bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {

  return checkBST(tree, INT32_MIN, INT32_MAX);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
