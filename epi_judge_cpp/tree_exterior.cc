#include <vector>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

void ExteriorBinaryTreeHelperLeft(
    const unique_ptr<BinaryTreeNode<int>> &node, vector<const unique_ptr<BinaryTreeNode<int>> *> &list, bool isExterior)
{
  if (!node)
    return;
  if (!node->left && !node->right)
  {
    list.emplace_back(&node);
    return;
  }
  if (isExterior)
    list.emplace_back(&node);
  ExteriorBinaryTreeHelperLeft(node->left, list, isExterior);
  if (!node->left)
    ExteriorBinaryTreeHelperLeft(node->right, list, isExterior);
  else
    ExteriorBinaryTreeHelperLeft(node->right, list, false);
}

void ExteriorBinaryTreeHelperRight(
    const unique_ptr<BinaryTreeNode<int>> &node, vector<const unique_ptr<BinaryTreeNode<int>> *> &list, bool isExterior)
{
  if (!node)
    return;
  if (!node->left && !node->right)
  {
    list.emplace_back(&node);
    return;
  }
  if(!node->right)
    ExteriorBinaryTreeHelperRight(node->left, list, isExterior);
  else
    ExteriorBinaryTreeHelperRight(node->left, list, false);

  ExteriorBinaryTreeHelperRight(node->right, list, isExterior);
  if (isExterior)
    list.emplace_back(&node);
}

vector<const unique_ptr<BinaryTreeNode<int>> *> ExteriorBinaryTree(
    const unique_ptr<BinaryTreeNode<int>> &tree)
{
  if (!tree)
    return {};
  vector<const unique_ptr<BinaryTreeNode<int>> *> res;
  res.emplace_back(&tree);
  ExteriorBinaryTreeHelperLeft(tree->left, res, true);
  ExteriorBinaryTreeHelperRight(tree->right, res, true);
  return res;
}
vector<int> CreateOutputVector(
    const vector<const unique_ptr<BinaryTreeNode<int>> *> &L)
{
  if (std::find(std::begin(L), std::end(L), nullptr) != std::end(L))
  {
    throw TestFailure("Resulting list contains nullptr");
  }
  std::vector<int> output;
  for (const auto *l : L)
  {
    output.push_back((*l)->data);
  }
  return output;
}

vector<int> ExteriorBinaryTreeWrapper(
    TimedExecutor &executor, const unique_ptr<BinaryTreeNode<int>> &tree)
{
  auto result = executor.Run([&]
                             { return ExteriorBinaryTree(tree); });

  return CreateOutputVector(result);
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(args, "tree_exterior.cc", "tree_exterior.tsv",
                         &ExteriorBinaryTreeWrapper, DefaultComparator{},
                         param_names);
}
