#include <algorithm>
#include <iterator>
#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool isValidPlacement(int r, int c,
                      const std::unordered_set<int> &rows,
                      const std::unordered_set<int> &cols,
                      const std::unordered_set<int> &diags,
                      const std::unordered_set<int> &anti_diags)
{
  return rows.find(r) == rows.end() &&
         cols.find(c) == cols.end() &&
         diags.find(c-r) == diags.end() &&
         anti_diags.find(c+r) == anti_diags.end();
}

void solveNQueens(vector<vector<int>> &matrix, vector<vector<int>> &solutions, int r, int c, int placements, std::unordered_set<int> &row_placements, std::unordered_set<int> &column_placements,
   std::unordered_set<int> &diagonal_placements, std::unordered_set<int> &anti_diagonal_placements)
{
  if (placements == matrix.size())
  {
    vector<int> curr_solution;
    for(auto it = column_placements.begin(); it != column_placements.end();){
      curr_solution.push_back(*it++);
    }
    solutions.push_back(curr_solution);
    return;
  }
  if (r > matrix.size() - 1){
    return;
  }
    

  for (int i = c; i < matrix[0].size(); i++)
  {
    if (isValidPlacement(r, i, row_placements, column_placements, diagonal_placements, anti_diagonal_placements))
    {
      matrix[r][i] = 1;
      row_placements.insert(r);
      column_placements.insert(i);
      diagonal_placements.insert(i-r);
      anti_diagonal_placements.insert(i+r);
      solveNQueens(matrix, solutions, r + 1, 0, placements + 1, row_placements, column_placements, diagonal_placements, anti_diagonal_placements);
      row_placements.erase(r);
      column_placements.erase(i);
      diagonal_placements.erase(i-r);
      anti_diagonal_placements.erase(i+r);
      matrix[r][i] = 0;
    }
  }
}

vector<vector<int>> NQueens(int n)
{
  vector<vector<int>> matrix(n, vector<int>(n, 0));
  vector<vector<int>> solutions;
  std::unordered_set<int> row_placements;
  std::unordered_set<int> col_placements;
  std::unordered_set<int> diagonal_placements;
  std::unordered_set<int> anti_diagonal_placements;
  solveNQueens(matrix, solutions, 0, 0, 0, row_placements, col_placements, diagonal_placements, anti_diagonal_placements);
  return solutions;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "n_queens.cc", "n_queens.tsv", &NQueens,
                         UnorderedComparator{}, param_names);
}
