#include <memory>
#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/timed_executor.h"
using std::unique_ptr;
using test_framework::BinaryTreeSerializationTrait;
template <typename T>
struct BinaryTreeNode {
  T data;
  unique_ptr<BinaryTreeNode<T>> left, right;
  BinaryTreeNode<T>* next = nullptr;  // Populates this field.

  explicit BinaryTreeNode(T data) : data(data){};
};

void ConstructRightSibling(BinaryTreeNode<int>* tree) {
  if(!tree) return;
  std::queue<std::vector<BinaryTreeNode<int>*>> queue;
  queue.push({tree});
  while(!queue.empty()){
    auto curr_level = queue.front();
    std::vector<BinaryTreeNode<int>*> next_level;
    queue.pop();
    for(int i=0;i<curr_level.size();i++){
      auto curr_node = curr_level[i];
      if(curr_node->left) next_level.push_back(curr_node->left.get());
      if(curr_node->right) next_level.push_back(curr_node->right.get());
      if(i+1<curr_level.size())
        curr_node->next = curr_level[i+1];
    }
    if(!next_level.empty()) queue.push(next_level);
  }

  return;
}
namespace test_framework {
template <>
struct SerializationTrait<unique_ptr<BinaryTreeNode<int>>>
    : BinaryTreeSerializationTrait<unique_ptr<BinaryTreeNode<int>>, false> {};
}  // namespace test_framework

std::vector<std::vector<int>> ConstructRightSiblingWrapper(
    TimedExecutor& executor, unique_ptr<BinaryTreeNode<int>>& tree) {
  executor.Run([&] { ConstructRightSibling(tree.get()); });

  std::vector<std::vector<int>> result;
  auto level_start = tree.get();
  while (level_start) {
    result.emplace_back();
    auto level_iter = level_start;
    while (level_iter) {
      result.back().push_back(level_iter->data);
      level_iter = level_iter->next;
    }
    level_start = level_start->left.get();
  }
  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "tree"};
  return GenericTestMain(
      args, "tree_right_sibling.cc", "tree_right_sibling.tsv",
      &ConstructRightSiblingWrapper, DefaultComparator{}, param_names);
}
