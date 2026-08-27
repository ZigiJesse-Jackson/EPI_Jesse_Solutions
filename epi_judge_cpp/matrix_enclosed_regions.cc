#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>

#include "test_framework/generic_test.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::vector;

struct PairHash
{
  std::size_t operator()(const std::pair<int, int> &p) const
  {
    auto h1 = std::hash<int>{}(p.first);
    auto h2 = std::hash<int>{}(p.second);
    return h1 ^ (h2 << 1);
  }
};

void recordBoundaryRegions(vector<vector<char>> *board_ptr, std::unordered_set<std::pair<int, int>, PairHash> &visited, int x, int y)
{
  std::queue<std::pair<int, int>> pairQ;
  pairQ.emplace(std::pair<int, int>{x, y});
  while (!pairQ.empty())
  {
    auto curr = pairQ.front();

    if (visited.count(curr) < 1)
    {
      visited.emplace(curr);
      if (curr.first - 1 >= 0 && (*board_ptr)[curr.first - 1][curr.second] == 'W')
      {
        pairQ.emplace(std::pair<int, int>{curr.first - 1, curr.second});
      }
      if (curr.first + 1 < board_ptr->size() && (*board_ptr)[curr.first + 1][curr.second] == 'W')
      {
        pairQ.emplace(std::pair<int, int>{curr.first + 1, curr.second});
      }
      if (curr.second - 1 >= 0 && (*board_ptr)[curr.first][curr.second - 1] == 'W')
      {
        pairQ.emplace(std::pair<int, int>{curr.first, curr.second - 1});
      }
      if (curr.second + 1 < (*board_ptr)[0].size() && (*board_ptr)[curr.first][curr.second + 1] == 'W')
      {
        pairQ.emplace(std::pair<int, int>{curr.first, curr.second + 1});
      }
    }
    pairQ.pop();
  }
}

void fillInRegion(vector<vector<char>> *board_ptr, int x, int y)
{
  std::queue<std::pair<int, int>> pairQ;
  pairQ.emplace(std::pair<int, int>{x, y});
  while (!pairQ.empty())
  {
    auto curr = pairQ.front();
    if ((*board_ptr)[curr.first][curr.second] != 'B')
    {
      (*board_ptr)[curr.first][curr.second] = 'B';
      if ((*board_ptr)[curr.first - 1][curr.second] == 'W')
      {
        pairQ.emplace(std::pair<int, int>{curr.first - 1, curr.second});
      }
      if ((*board_ptr)[curr.first + 1][curr.second] == 'W')
      {
        pairQ.emplace(std::pair<int, int>{curr.first + 1, curr.second});
      }
      if ((*board_ptr)[curr.first][curr.second - 1] == 'W')
      {
        pairQ.emplace(std::pair<int, int>{curr.first, curr.second - 1});
      }
      if ((*board_ptr)[curr.first][curr.second + 1] == 'W')
      {
        pairQ.emplace(std::pair<int, int>{curr.first, curr.second + 1});
      }
    }

    pairQ.pop();
  }
}

void FillSurroundedRegions(vector<vector<char>> *board_ptr)
{
  std::unordered_set<std::pair<int, int>, PairHash> visited;
  if (board_ptr->size() <= 2 || (*board_ptr)[0].size() <= 2)
    return;

  // all first and last cells in rows
  for (int i = 0; i < board_ptr->size(); i++)
  {
    int last_idx = (*board_ptr)[0].size() - 1;
    if ((*board_ptr)[i][0] == 'W')
    {
      recordBoundaryRegions(board_ptr, visited, i, 0);
    }
    if ((*board_ptr)[i][last_idx] == 'W')
    {
      recordBoundaryRegions(board_ptr, visited, i, last_idx);
    }
  }

  // all cells in first and last row
  for (int i = 0; i < (*board_ptr)[0].size(); i++)
  {
    int last_idx = (*board_ptr).size() - 1;
    if ((*board_ptr)[0][i] == 'W')
    {
      recordBoundaryRegions(board_ptr, visited, 0, i);
    }
    if ((*board_ptr)[last_idx][i] == 'W')
    {
      recordBoundaryRegions(board_ptr, visited, last_idx, i);
    }
  }

  // solving in-place
  for (int x = 1; x < board_ptr->size() - 1; x++)
  {
    for (int y = 1; y < (*board_ptr)[0].size() - 1; y++)
    {
      if (visited.count(std::pair<int, int>{x, y}) < 1 && (*board_ptr)[x][y] == 'W')
      {
        fillInRegion(board_ptr, x, y);
      }
    }
  }
  return;
}
vector<vector<string>> FillSurroundedRegionsWrapper(
    TimedExecutor &executor, vector<vector<string>> board)
{
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++)
  {
    for (const string &s : board[i])
    {
      if (s.size() != 1)
      {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  executor.Run([&]
               { FillSurroundedRegions(&char_vector); });

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++)
  {
    for (char c : char_vector[i])
    {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "board"};
  return GenericTestMain(
      args, "matrix_enclosed_regions.cc", "matrix_enclosed_regions.tsv",
      &FillSurroundedRegionsWrapper, DefaultComparator{}, param_names);
}
