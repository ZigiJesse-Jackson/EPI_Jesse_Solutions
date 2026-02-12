#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include <stack>
#include <utility>

int SumRootToLeaf(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if(!tree) return 0;
  int sum = 0;
  std::stack<std::pair<BinaryTreeNode<int>*, int>> stack;
  stack.push(std::make_pair(tree.get(), 0));

  while(!stack.empty()){
    auto curr = stack.top();
    stack.pop();
    int running_sum = curr.second*2;
    running_sum+=curr.first->data;

    if(curr.first->right){
      stack.push(std::make_pair(curr.first->right.get(), running_sum));
    }
    if(curr.first->left){
      stack.push(std::make_pair(curr.first->left.get(), running_sum));

    }

    if(!curr.first->left && !curr.first->right){
      sum += running_sum;
    }
  }

  return sum;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "sum_root_to_leaf.cc", "sum_root_to_leaf.tsv",
                         &SumRootToLeaf, DefaultComparator{}, param_names);
}
