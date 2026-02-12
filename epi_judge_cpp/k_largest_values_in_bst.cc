#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;
using std::vector;

vector<int> FindKLargestInBST(const unique_ptr<BstNode<int>>& tree, int k) {
  // TODO - you fill in here.
  std::vector<int> res(k, 0);
  std::vector<BstNode<int>*> stack;
  BstNode<int>* curr = tree.get();
  int i = 0;

  while(!stack.empty() || curr)
  {
    while(curr)
    {
      stack.push_back(curr);
      curr = curr->right.get();
    }

    if(k==i) break;
    curr = stack.back();
    res[i++] = curr->data;
    stack.pop_back();
    curr = curr->left.get();
  }
  return res;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "k"};
  return GenericTestMain(args, "k_largest_values_in_bst.cc",
                         "k_largest_values_in_bst.tsv", &FindKLargestInBST,
                         UnorderedComparator{}, param_names);
}
