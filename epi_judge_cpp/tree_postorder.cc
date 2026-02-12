#include <memory>
#include <vector>
#include <stack>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<int> PostorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  if(!tree) return {};
  std::stack<BinaryTreeNode<int>*> stack;
  BinaryTreeNode<int>* curr;
  vector<int> res;
  stack.push(tree.get());
  while(!stack.empty()){
    curr = stack.top();
    stack.pop();
    res.push_back(curr->data);
    if(curr->left){
      stack.push(curr->left.get());
    }
    if(curr->right) stack.push(curr->right.get());
  }
  
  std::reverse(res.begin(), res.end());
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_postorder.cc", "tree_postorder.tsv",
                         &PostorderTraversal, DefaultComparator{}, param_names);
}
