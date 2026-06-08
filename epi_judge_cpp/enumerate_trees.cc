#include <algorithm>
#include <stack>
#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::vector;

// Helper function to deep clone a tree
std::unique_ptr<BinaryTreeNode<int>> clone_tree(const std::unique_ptr<BinaryTreeNode<int>> &root)
{
  if (!root)
    return nullptr;

  auto new_node = std::make_unique<BinaryTreeNode<int>>(root->data);
  if (root->left != nullptr)
  {
    new_node->left = clone_tree(root->left);
  }
  if (root->right != nullptr)
  {
    new_node->right = clone_tree(root->right);
  }
  return new_node;
}

vector<unique_ptr<BinaryTreeNode<int>>> GenerateAllBinaryTrees(int num_nodes)
{
  vector<unique_ptr<BinaryTreeNode<int>>> result;

  // base case
  if (num_nodes == 0)
  {
    result.emplace_back(nullptr);
    return result;
  }

  for (int left = 0; left < num_nodes; left++)
  {
    int right = num_nodes - 1 - left;
    // generate all left and right subtrees
    vector<unique_ptr<BinaryTreeNode<int>>> left_subtrees = GenerateAllBinaryTrees(left);
    vector<unique_ptr<BinaryTreeNode<int>>> right_subtrees = GenerateAllBinaryTrees(right);

    // create all possible combinations of node with left and right subtrees generated
    for (auto &left_subtree : left_subtrees)
    {
      for (auto &right_subtree : right_subtrees)
      {

        result.emplace_back(std::move(std::make_unique<BinaryTreeNode<int>>(0, clone_tree(left_subtree), clone_tree(right_subtree))));
      }
    }
  }

  return result;
}

vector<int> SerializeStructure(const unique_ptr<BinaryTreeNode<int>> &tree)
{
  vector<int> result;

  std::stack<BinaryTreeNode<int> *> stack;
  stack.push(tree.get());
  while (!stack.empty())
  {
    auto p = stack.top();
    stack.pop();
    result.push_back(p != nullptr);
    if (p)
    {
      stack.push(p->left.get());
      stack.push(p->right.get());
    }
  }
  return result;
}

vector<vector<int>> GenerateAllBinaryTreesWrapper(TimedExecutor &executor,
                                                  int num_nodes)
{
  auto result = executor.Run([&]
                             { return GenerateAllBinaryTrees(num_nodes); });

  vector<vector<int>> serialized;
  for (auto &x : result)
  {
    serialized.push_back(SerializeStructure(x));
  }
  std::sort(begin(serialized), end(serialized));
  return serialized;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_nodes"};
  return GenericTestMain(args, "enumerate_trees.cc", "enumerate_trees.tsv",
                         &GenerateAllBinaryTreesWrapper, DefaultComparator{},
                         param_names);
}
