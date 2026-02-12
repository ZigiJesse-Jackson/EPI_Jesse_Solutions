#include <memory>

#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;

bool find_children(BinaryTreeNode<int>* node, BinaryTreeNode<int>* node0, BinaryTreeNode<int>* node1, BinaryTreeNode<int>* &ancestor){
  if(!node) return false;

  bool found0 = find_children(node->left.get(), node0, node1, ancestor);
  bool found1 = find_children(node->right.get(), node0, node1, ancestor);
  
  bool is_current = (node==node0 || node == node1);

  if ((found0 && found1) || (is_current && (found0 || found1))) ancestor = node;
  if(node == node0 && node == node1) ancestor = node;

  return found0 || found1 || is_current;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& tree,
                         const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  BinaryTreeNode<int>* ancestor = nullptr;
  find_children(tree.get(), node0.get(), node1.get(), ancestor);
  return ancestor;
}


int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(tree, node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
