#include <vector>
#include <algorithm>
#include "test_framework/generic_test.h"
using std::vector;
void RotateMatrix(vector<vector<int>>* square_matrix_ptr) {
  int matrix_size = square_matrix_ptr->size()-1;
  for(int i=0;i<square_matrix_ptr->size()/2;i++){
    for(int j=i;j<matrix_size-i;j++){
      std::swap((*square_matrix_ptr)[i][j],(*square_matrix_ptr)[matrix_size-j][i]);
      std::swap((*square_matrix_ptr)[matrix_size-j][i],(*square_matrix_ptr)[matrix_size-i][matrix_size-j]);
      std::swap((*square_matrix_ptr)[matrix_size-i][matrix_size-j],(*square_matrix_ptr)[j][matrix_size-i]);
    }
  }

  return;
}
vector<vector<int>> RotateMatrixWrapper(vector<vector<int>> square_matrix) {
  RotateMatrix(&square_matrix);
  return square_matrix;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "matrix_rotation.cc", "matrix_rotation.tsv",
                         &RotateMatrixWrapper, DefaultComparator{},
                         param_names);
}
