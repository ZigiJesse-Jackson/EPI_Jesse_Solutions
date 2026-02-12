#include <string>
#include <vector>
#include <iostream>
#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

std::unique_ptr<BinaryTreeNode<int>> ReconstructPreorder(const std::vector<int *> &preorder)
{
    if (preorder.empty() || !preorder[0])
        return nullptr;
    
    // Use a stack of pairs to manage nodes and their left/right child status
    std::vector<std::pair<BinaryTreeNode<int> *, bool>> stack;

    // Create the root node
    auto root = std::make_unique<BinaryTreeNode<int>>(*preorder[0]);
    stack.push_back({root.get(), false}); // Initially process the left child
    int i = 1;

    while (i < preorder.size())
    {
        BinaryTreeNode<int> *parent = stack.back().first;
        bool left_processed = stack.back().second;

        if (!preorder[i])
        {
            // Null node, skip to the next child
            if (!left_processed)
            {
                // Mark left child as processed
                stack.back().second = true;
            }
            else
            {
                // If both children are processed, pop the node
                stack.pop_back();
            }
        }
        else
        {
            auto new_node = std::make_unique<BinaryTreeNode<int>>(*preorder[i]);

            if (!left_processed)
            {
                // Assign as left child
                parent->left = std::move(new_node);
                stack.back().second = true;                   // Mark left child as processed
                stack.push_back({parent->left.get(), false}); // Push the left child onto the stack
            }
            else
            {
                // Assign as right child
                parent->right = std::move(new_node);
                stack.pop_back();                              // Pop after processing the right child
                stack.push_back({parent->right.get(), false}); // Push the right child onto the stack
            }
        }
        i++;
    }

    return root;
}

unique_ptr<BinaryTreeNode<int>> ReconstructPreorderWrapper(
    TimedExecutor &executor, const vector<string> &preorder)
{
    vector<int> values;
    vector<int *> ptrs;
    values.reserve(preorder.size());
    for (auto &s : preorder)
    {
        if (s == "null")
        {
            ptrs.push_back(nullptr);
        }
        else
        {
            int i = std::stoi(s);
            values.push_back(i);
            ptrs.push_back(&values.back());
        }
    }

    return executor.Run([&]
                        { return ReconstructPreorder(ptrs); });
}

int main(int argc, char *argv[])
{
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"executor", "preorder"};
    return GenericTestMain(args, "tree_from_preorder_with_null.cc",
                           "tree_from_preorder_with_null.tsv",
                           &ReconstructPreorderWrapper, DefaultComparator{},
                           param_names);
}
