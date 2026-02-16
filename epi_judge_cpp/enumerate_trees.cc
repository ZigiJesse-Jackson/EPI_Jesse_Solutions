#include <algorithm>
#include <stack>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;

// Helper function to deep clone a tree
std::unique_ptr<BinaryTreeNode<int>> clone_tree(const std::unique_ptr<BinaryTreeNode<int>>& root) {
    if (!root) return nullptr;
    
    auto new_node = std::make_unique<BinaryTreeNode<int>>(root->data);
    if(root->left!=nullptr){
      new_node->left = clone_tree(root->left);
    }
    if(root->right!=nullptr){
      new_node->right = clone_tree(root->right);
    }
    return new_node;
}

void generate_valid_binary_tree(const unique_ptr<BinaryTreeNode<int>>& root, unique_ptr<BinaryTreeNode<int>>& current_node, int remaining_nodes,
vector<unique_ptr<BinaryTreeNode<int>>>* const valid_binary_trees){
  if(remaining_nodes<0) {
    return;
  }
  if(remaining_nodes==0){
    valid_binary_trees->push_back(clone_tree(root));
    return;
  }

  // grow left
  current_node->left = std::make_unique<BinaryTreeNode<int>>(-1);
  generate_valid_binary_tree(root, current_node->left, remaining_nodes-1, valid_binary_trees);
  current_node->left = nullptr;

  // grow right
  current_node->right = std::make_unique<BinaryTreeNode<int>>(1);
  generate_valid_binary_tree(root, current_node->right, remaining_nodes-1, valid_binary_trees);
  current_node->right = nullptr;

  // grow both
    current_node->left = std::make_unique<BinaryTreeNode<int>>(-1);
    current_node->right = std::make_unique<BinaryTreeNode<int>>(1);
    generate_valid_binary_tree(root, current_node->left, remaining_nodes-2, valid_binary_trees);
    generate_valid_binary_tree(root, current_node->right, remaining_nodes-2, valid_binary_trees);
    current_node->left = nullptr;
    current_node->right = nullptr;
}

vector<unique_ptr<BinaryTreeNode<int>>> GenerateAllBinaryTrees(int num_nodes) {
  if(num_nodes<1) return {};
  vector<unique_ptr<BinaryTreeNode<int>>> valid_trees = {};
  unique_ptr<BinaryTreeNode<int>> root = std::make_unique<BinaryTreeNode<int>>(0); 
  generate_valid_binary_tree(root, root, num_nodes, &valid_trees);
  return valid_trees;
}

vector<int> SerializeStructure(const unique_ptr<BinaryTreeNode<int>>& tree) {
  vector<int> result;

  std::stack<BinaryTreeNode<int>*> stack;
  stack.push(tree.get());
  while (!stack.empty()) {
    auto p = stack.top();
    stack.pop();
    result.push_back(p != nullptr);
    if (p) {
      stack.push(p->left.get());
      stack.push(p->right.get());
    }
  }
  return result;
}

vector<vector<int>> GenerateAllBinaryTreesWrapper(TimedExecutor& executor,
                                                  int num_nodes) {
  auto result = executor.Run([&] { return GenerateAllBinaryTrees(num_nodes); });

  vector<vector<int>> serialized;
  for (auto& x : result) {
    serialized.push_back(SerializeStructure(x));
  }
  std::sort(begin(serialized), end(serialized));
  return serialized;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_nodes"};
  return GenericTestMain(args, "enumerate_trees.cc", "enumerate_trees.tsv",
                         &GenerateAllBinaryTreesWrapper, DefaultComparator{},
                         param_names);
}
