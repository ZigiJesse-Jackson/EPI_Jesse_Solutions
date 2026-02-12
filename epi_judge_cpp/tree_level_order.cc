#include <memory>
#include <vector>
#include <queue>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<vector<int>> BinaryTreeDepthOrder(
    const unique_ptr<BinaryTreeNode<int>>& tree) {
  if(!tree) return {};
  vector<vector<int>> level_order;
  std::queue<vector<BinaryTreeNode<int>*>> q;
  q.push({tree.get()});
  while(!q.empty()){
    vector<BinaryTreeNode<int>*> curr_order = q.back();
    q.pop();
    vector<BinaryTreeNode<int>*> next_order;
    vector<int> curr_level_order;

    for(int i=0;i<curr_order.size();i++){
      auto curr = curr_order[i];
      curr_level_order.push_back(curr->data);
      if(curr->left) next_order.push_back(curr->left.get());
      if(curr->right) next_order.push_back(curr->right.get());
    }

    if(!next_order.empty()) q.push(next_order);
    level_order.push_back(curr_level_order);
  }


  return level_order;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_level_order.cc", "tree_level_order.tsv",
                         &BinaryTreeDepthOrder, DefaultComparator{},
                         param_names);
}
