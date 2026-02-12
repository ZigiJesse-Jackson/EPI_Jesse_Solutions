#include <vector>
#include <map>

#include "test_framework/generic_test.h"
using std::vector;
// Check if a partially filled matrix has any conflicts.
bool IsValidSudoku(const vector<vector<int>>& partial_assignment) {
  // TODO - you fill in here.
  vector<vector<bool>> row_checker(partial_assignment.size(), vector<bool>(partial_assignment.size(), false));
  vector<vector<bool>> col_checker(partial_assignment.size(), vector<bool>(partial_assignment.size(), false));
  std::map<std::pair<int, int>, vector<bool>> sub_checker;

  for(int r=0;r<partial_assignment.size();r++){
    for(int c=0;c<partial_assignment[0].size();c++){
      if(partial_assignment[r][c]!=0){
        int val = partial_assignment[r][c]-1;
        bool check_row = row_checker[r][val];
        bool check_col = col_checker[c][val];
        bool check_sub = false;
        std::pair<int, int> pos{r/3,c/3};
        if(sub_checker.find(pos)!=sub_checker.end()){
          check_sub = sub_checker[pos][val];
        }else{
          sub_checker[pos] = vector<bool>(partial_assignment.size(), false);
        }
        if(check_row||check_col||check_sub) return false;
        row_checker[r][val] = true;
        col_checker[c][val] = true;
        sub_checker[pos][val] = true; 
      }
    }
  }

  return true;
}



int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"partial_assignment"};
  return GenericTestMain(args, "is_valid_sudoku.cc", "is_valid_sudoku.tsv",
                         &IsValidSudoku, DefaultComparator{}, param_names);
}
