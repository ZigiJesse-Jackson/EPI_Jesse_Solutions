#include <memory>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

BstNode<int>* searchGreaterThanK(const unique_ptr<BstNode<int>>& node, int k, const unique_ptr<BstNode<int>>& min, const unique_ptr<BstNode<int>>& max){
  if(!node) return node.get();
  if(node->data <= k)
  {
    if(!node->right) return max.get();
    return searchGreaterThanK(node->right, k, node, max);
  }
  if(node->data > k)
  {
    if(!node->left) return node.get();
    return searchGreaterThanK(node->left, k, min, node);
  }
  return nullptr;

}

BstNode<int>* FindFirstGreaterThanK(const unique_ptr<BstNode<int>>& tree,
                                    int k) {
  if(!tree) return tree.get();
  if(tree->data <= k) return searchGreaterThanK(tree->right, k, tree, nullptr);
  if(tree->data > k) return searchGreaterThanK(tree->left, k, nullptr, tree);
  return nullptr;                                  
}
int FindFirstGreaterThanKWrapper(const unique_ptr<BstNode<int>>& tree, int k) {
  auto result = FindFirstGreaterThanK(tree, k);
  return result ? result->data : -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "search_first_greater_value_in_bst.cc",
                         "search_first_greater_value_in_bst.tsv",
                         &FindFirstGreaterThanKWrapper, DefaultComparator{},
                         param_names);
}
