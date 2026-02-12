#include <vector>
#include <utility>
#include "binary_tree_node.h"
#include "test_framework/binary_tree_utils.h"
#include "test_framework/generic_test.h"
using std::vector;

int find_head(int head_val, int begin, int end, const vector<int>& tree){
  int i = begin;
  while(i!=end && tree[i]!=head_val) i++;
  return i;
}

unique_ptr<BinaryTreeNode<int>> BinaryTreeFromPreorderInorder(
    const vector<int>& preorder, const vector<int>& inorder) {

  if(preorder.empty()) return nullptr;

  
  vector<std::pair<std::pair<int, int>, std::pair<BinaryTreeNode<int>*, int>>> stack;
  // find where head is in inorder
  int i = find_head(preorder[0], 0, inorder.size()-1, inorder);
  unique_ptr<BinaryTreeNode<int>> head = std::make_unique<BinaryTreeNode<int>>(preorder[i]);
  stack.push_back(std::make_pair(std::make_pair(0, inorder.size()-1), std::make_pair(nullptr, i)));
  i = 0;
  while(!stack.empty())
  {
    auto subtree = stack.back().first;
    auto parent_info = stack.back().second;
    stack.pop_back();
    int curr_head_idx = find_head(preorder[i], subtree.first, subtree.second, inorder);
    int curr_head_val = inorder[curr_head_idx];
    BinaryTreeNode<int>* next_parent;

    // set next parent
    if(parent_info.first == nullptr)
    {
      head->data = curr_head_val;
      next_parent = head.get();
    }
    else
    {
      // add to parent's left child
      if(parent_info.second>subtree.second)
      {
        parent_info.first->left = std::make_unique<BinaryTreeNode<int>>(curr_head_val);
        next_parent = parent_info.first->left.get();
      }
      // add to parent's right child
      else
      {
        parent_info.first->right = std::make_unique<BinaryTreeNode<int>>(curr_head_val);
        next_parent = parent_info.first->right.get();
      }
    }

    // set next stack
    // add right subtree if it exists
    if(subtree.second>=curr_head_idx+1)
    {
      stack.push_back(std::make_pair(std::make_pair(curr_head_idx+1, subtree.second), std::make_pair(next_parent, curr_head_idx)));
    }
    // add left subtree if it exists
    if(subtree.first<=curr_head_idx-1)
    {
      stack.push_back(std::make_pair(std::make_pair(subtree.first, curr_head_idx-1), std::make_pair(next_parent, curr_head_idx)));
    }

    i++;
  }

  return head;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"preorder", "inorder"};
  return GenericTestMain(
      args, "tree_from_preorder_inorder.cc", "tree_from_preorder_inorder.tsv",
      &BinaryTreeFromPreorderInorder, DefaultComparator{}, param_names);
}
