#include <memory>
#include <vector>

#include "bst_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
using std::unique_ptr;
using std::vector;

struct Interval
{
  int left, right;
};

vector<int> RangeLookupInBST(const unique_ptr<BstNode<int>> &tree,
                             const Interval &interval)
{
  
  std::vector<BstNode<int> *> stack;
  std::vector<int> res;
  BstNode<int> *curr = tree.get();

  // find root of subtree containing interval
  while(curr){
    if(curr->data < interval.left) curr = curr->right.get();
    else if(curr->data > interval.right) curr = curr->left.get();
    else break;
  }

  while (!stack.empty() || curr)
  {
    while (curr)
    {
      stack.push_back(curr);
      curr = curr->left.get();
    }
    curr = stack.back();
    if(interval.left <= curr->data && curr->data <= interval.right)
      res.push_back(curr->data);
    stack.pop_back();
    curr = curr->right.get();
  }

  return res;
}
void RangeLookupInBSTHelper(const unique_ptr<BstNode<int>> &tree,
                            const Interval &interval, vector<int> *result) {}

namespace test_framework
{
  template <>
  struct SerializationTrait<Interval> : UserSerTrait<Interval, int, int>
  {
    static std::vector<std::string> GetMetricNames(const std::string &arg_name)
    {
      return {FmtStr("length({})", arg_name)};
    }

    static std::vector<int> GetMetrics(const Interval &x)
    {
      return {x.right - x.left};
    }
  };
} // namespace test_framework

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree", "interval"};
  return GenericTestMain(args, "range_lookup_in_bst.cc",
                         "range_lookup_in_bst.tsv", &RangeLookupInBST,
                         DefaultComparator{}, param_names);
}
