#include <memory>
#include <vector>
#include <stack>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<int> InorderTraversal(const unique_ptr<BinaryTreeNode<int>>& tree) {
  std::stack<BinaryTreeNode<int>*> stack;
  vector<int> res;
  BinaryTreeNode<int>* curr = tree.get();
  while(!stack.empty() || curr){
    if(curr->left){
      stack.push(curr);
      curr = curr->left.get();
    }else{
      res.push_back(curr->data);
      while(!curr->right && !stack.empty()){
        curr = stack.top();
        stack.pop();
        res.push_back(curr->data);
      }
      curr = curr->right.get();
    }
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "tree_inorder.cc", "tree_inorder.tsv",
                         &InorderTraversal, DefaultComparator{}, param_names);
}
                                      