#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

bool MatrixSearch(const vector<vector<int>>& A, int x) {
  for(int r = 0; r<A.size();r++){
    if(x>A[r].back()) continue;
    if(x<A[r].front()) return false;
    int left = 0, right = A[r].size()-1;
    while(left<=right){
      int mid = left +((right-left)/2);
      if(A[r][mid]==x) return true;
      if(A[r][mid]>x) right = mid-1;
      else left = mid+1;
    }
  }
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "x"};
  return GenericTestMain(args, "search_row_col_sorted_matrix.cc",
                         "search_row_col_sorted_matrix.tsv", &MatrixSearch,
                         DefaultComparator{}, param_names);
}
