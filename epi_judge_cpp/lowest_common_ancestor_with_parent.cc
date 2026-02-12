#include "binary_tree_with_parent_prototype.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
#include <unordered_set>
#include <algorithm>

int get_len_path(const unique_ptr<BinaryTreeNode<int>>& node){
  BinaryTreeNode<int>* iterator = node.get();
  int count = 0;
  while(iterator){
    count++;
    iterator = iterator->parent;
  }
  return count;
}

BinaryTreeNode<int>* Lca(const unique_ptr<BinaryTreeNode<int>>& node0,
                         const unique_ptr<BinaryTreeNode<int>>& node1) {
  int c1 = get_len_path(node0);
  int c2 = get_len_path(node1);
  int level = std::abs(c1-c2);

  BinaryTreeNode<int>* long_iterator;
  BinaryTreeNode<int>* short_iterator;
  if(c1>c2){
    long_iterator = node0.get();
    short_iterator = node1.get();
  }
  else {
    long_iterator = node1.get();
    short_iterator = node0.get();
  } 

   while(level-->0){
    long_iterator = long_iterator->parent;
  }

  while(long_iterator && short_iterator){
    if(long_iterator == short_iterator) return long_iterator;
    long_iterator = long_iterator->parent;
    short_iterator = short_iterator->parent;
  }

  return nullptr;
}
int LcaWrapper(TimedExecutor& executor,
               const unique_ptr<BinaryTreeNode<int>>& tree, int key0,
               int key1) {
  const unique_ptr<BinaryTreeNode<int>>& node0 = MustFindNode(tree, key0);
  const unique_ptr<BinaryTreeNode<int>>& node1 = MustFindNode(tree, key1);

  auto result = executor.Run([&] { return Lca(node0, node1); });

  if (!result) {
    throw TestFailure("Result can not be nullptr");
  }
  return result->data;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree", "key0", "key1"};
  return GenericTestMain(args, "lowest_common_ancestor_with_parent.cc",
                         "lowest_common_ancestor.tsv", &LcaWrapper,
                         DefaultComparator{}, param_names);
}
