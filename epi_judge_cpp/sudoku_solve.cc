#include <algorithm>
#include <cmath>
#include <iterator>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::begin;
using std::end;
using std::vector;

// Custom hash function for std::pair
struct pair_hash
{
  template <class T1, class T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const
  {
    // Combine the hashes of the two elements
    auto h1 = std::hash<T1>{}(p.first);
    auto h2 = std::hash<T2>{}(p.second);
    // A common way to combine hashes
    return h1 ^ (h2 << 1);
  }
};

// Custom equality function (optional if pair's operator== works)
struct pair_equal
{
  template <class T1, class T2>
  bool operator()(const std::pair<T1, T2> &a, const std::pair<T1, T2> &b) const
  {
    return a.first == b.first && a.second == b.second;
  }
};

bool Solver(vector<vector<int>> *sudoku_grid, std::unordered_map<int, std::unordered_set<int>> &row_map,
            std::unordered_map<int, std::unordered_set<int>> &col_map,
            std::unordered_map<std::pair<int, int>, std::unordered_set<int>, pair_hash, pair_equal> &section_map,
            int row, int col)
{
  if (col >= sudoku_grid->size())
  {
    col = 0, row += 1;
    if (row >= sudoku_grid->size())
      return true;
  }
  if ((*sudoku_grid)[row][col] != 0)
    return Solver(sudoku_grid, row_map, col_map, section_map, row, col + 1);
  for (int x = 1; x <= sudoku_grid->size(); x++)
  {
    auto key = std::pair<int, int>(row / 3, col / 3);
    if (row_map[row].find(x) == row_map[row].end() && col_map[col].find(x) == col_map[col].end() &&
        section_map[key].find(x) == section_map[key].end())
    {
      section_map[key].insert(x);
      row_map[row].insert(x);
      col_map[col].insert(x);
      (*sudoku_grid)[row][col] = x;

      if (Solver(sudoku_grid, row_map, col_map, section_map, row, col + 1))
      {
        return true;
      }
      (*sudoku_grid)[row][col] = 0;

      section_map[key].erase(x);
      row_map[row].erase(x);
      col_map[col].erase(x);
    }
  }

  return false;
}

bool SolveSudoku(vector<vector<int>> *partial_assignment)
{
  std::unordered_map<int, std::unordered_set<int>> row_map;
  std::unordered_map<int, std::unordered_set<int>> col_map;
  std::unordered_map<std::pair<int, int>, std::unordered_set<int>, pair_hash, pair_equal> section_map;
  bool isAlreadySolved = true;
  for (int r = 0; r < partial_assignment->size(); r++)
  {
    for (int c = 0; c < partial_assignment->size(); c++)
    {
      int x = (*partial_assignment)[r][c];
      if (x != 0)
      {
        section_map[std::pair<int, int>(r / 3, c / 3)].insert(x);
        row_map[r].insert(x);
        col_map[c].insert(x);
      }
      else if (isAlreadySolved)
      {
        isAlreadySolved = false;
      }
    }
  }
  if (isAlreadySolved)
    return true;
  return Solver(partial_assignment, row_map, col_map, section_map, 0, 0);
}

vector<int> GatherColumn(const vector<vector<int>> &data, size_t i)
{
  vector<int> result;
  for (auto &row : data)
  {
    result.push_back(row[i]);
  }
  return result;
}

vector<int> GatherSquareBlock(const vector<vector<int>> &data,
                              size_t block_size, size_t n)
{
  vector<int> result;
  size_t block_x = n % block_size;
  size_t block_y = n / block_size;
  for (size_t i = block_x * block_size; i < (block_x + 1) * block_size; i++)
  {
    for (size_t j = block_y * block_size; j < (block_y + 1) * block_size; j++)
    {
      result.push_back(data[i][j]);
    }
  }

  return result;
}

void AssertUniqueSeq(const vector<int> &seq)
{
  vector<bool> seen(seq.size(), false);
  for (auto &x : seq)
  {
    if (x == 0)
    {
      throw TestFailure("Cell left uninitialized");
    }
    if (x < 0 || x > seq.size())
    {
      throw TestFailure("Cell value out of range");
    }
    if (seen[x - 1])
    {
      throw TestFailure("Duplicate value in section");
    }
    seen[x - 1] = true;
  }
}

void SolveSudokuWrapper(TimedExecutor &executor,
                        const vector<vector<int>> &partial_assignment)
{
  vector<vector<int>> solved = partial_assignment;

  executor.Run([&]
               { SolveSudoku(&solved); });

  if (!std::equal(begin(partial_assignment), end(partial_assignment),
                  begin(solved), end(solved), [](auto br, auto cr)
                  { return std::equal(begin(br), end(br), begin(cr), end(cr),
                                      [](int bcell, int ccell)
                                      {
                                        return bcell == 0 || bcell == ccell;
                                      }); }))
    throw TestFailure("Initial cell assignment has been changed");

  auto block_size = static_cast<size_t>(sqrt(solved.size()));

  for (size_t i = 0; i < solved.size(); i++)
  {
    AssertUniqueSeq(solved[i]);
    AssertUniqueSeq(GatherColumn(solved, i));
    AssertUniqueSeq(GatherSquareBlock(solved, block_size, i));
  }
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "partial_assignment"};
  return GenericTestMain(args, "sudoku_solve.cc", "sudoku_solve.tsv",
                         &SolveSudokuWrapper, DefaultComparator{}, param_names);
}