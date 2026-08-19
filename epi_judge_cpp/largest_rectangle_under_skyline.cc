#include <vector>
#include <stack>

#include "test_framework/generic_test.h"
using std::vector;

bool isNewAnchorOrReachedEnd(int idx, int anchor_idx, const vector<int> &heights)
{
  return idx < heights.size() ? heights[idx] < heights[anchor_idx] : true;
}

int CalculateLargestRectangle(const vector<int> &heights)
{
  std::stack<int> anchor_indices;
  int max_rec_area = 0;

  for (int i = 0; i <= heights.size(); i++)
  {
    // met another anchor whose height is the same as the last tracked anchor so we ignore it
    if (!anchor_indices.empty() && i < heights.size() && heights[i] == heights[anchor_indices.top()])
    {
      anchor_indices.pop();
      anchor_indices.emplace(i);
    }
    else
    {
      while (!anchor_indices.empty() && isNewAnchorOrReachedEnd(i, anchor_indices.top(), heights))
      {
        // height that anchors spanning rectangle
        int height = heights[anchor_indices.top()];
        anchor_indices.pop();
        int width = anchor_indices.empty() ? i : i - anchor_indices.top() - 1;
        max_rec_area = std::max(max_rec_area, height * width);
      }
      anchor_indices.emplace(i);
    }
  }

  return max_rec_area;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"heights"};
  return GenericTestMain(args, "largest_rectangle_under_skyline.cc",
                         "largest_rectangle_under_skyline.tsv",
                         &CalculateLargestRectangle, DefaultComparator{},
                         param_names);
}
