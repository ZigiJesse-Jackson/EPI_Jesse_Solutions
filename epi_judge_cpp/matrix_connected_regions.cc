#include <deque>
#include <vector>
#include <unordered_set>
#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::deque;
using std::vector;

void FlipColor(int x, int y, vector<deque<bool>> *image_ptr)
{

  bool color = (*image_ptr)[x][y];
  std::deque<std::pair<int, int>> queue;
  queue.emplace_back(std::pair<int, int>(x, y));
  while (!queue.empty())
  {
    auto curr = queue.front();
    if ((*image_ptr)[curr.first][curr.second] == color)
    {
      (*image_ptr)[curr.first][curr.second] = !color;
      if (curr.first - 1 >= 0 && (*image_ptr)[curr.first - 1][curr.second] == color)
      {
        queue.emplace_back(std::pair<int, int>(curr.first - 1, curr.second));
      }
      if (curr.first + 1 < image_ptr->size() && (*image_ptr)[curr.first + 1][curr.second] == color)
      {
        queue.emplace_back(std::pair<int, int>(curr.first + 1, curr.second));
      }
      if (curr.second - 1 >= 0 && (*image_ptr)[curr.first][curr.second - 1] == color)
      {
        queue.emplace_back(std::pair<int, int>(curr.first, curr.second - 1));
      }
      if (curr.second + 1 < (*image_ptr)[0].size() && (*image_ptr)[curr.first][curr.second + 1] == color)
      {
        queue.emplace_back(std::pair<int, int>(curr.first, curr.second + 1));
      }
    }
    queue.pop_front();
  }

  return;
}
vector<vector<int>> FlipColorWrapper(TimedExecutor &executor, int x, int y,
                                     vector<vector<int>> image)
{
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int> &row : image)
  {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i)
    {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  executor.Run([&]
               { FlipColor(x, y, &b); });

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i)
  {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j)
    {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "x", "y", "image"};
  return GenericTestMain(args, "matrix_connected_regions.cc", "painting.tsv",
                         &FlipColorWrapper, DefaultComparator{}, param_names);
}
