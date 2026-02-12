#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> MatrixInSpiralOrder(const vector<vector<int>>& square_matrix) {
  // TODO - you fill in here.
  int T = 0, B = square_matrix.size()-1, R = B, L = 0;

  vector<int> spiral_order;
  long long num = square_matrix.size()*square_matrix.size();
  while(spiral_order.size()<num){
    for(int i=L;i<=R;i++){
      spiral_order.push_back(square_matrix[T][i]);
    }
    T++;
    for(int i = T;i<=B;i++){
      spiral_order.push_back(square_matrix[i][R]);
    }
    R--;
    for(int i=R;i>=L;i--){
      spiral_order.push_back(square_matrix[B][i]);
    }
    B--;
    for(int i = B;i>=T;i--){
      spiral_order.push_back(square_matrix[i][L]);
    }
    L++;

  }
  return spiral_order;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"square_matrix"};
  return GenericTestMain(args, "spiral_ordering.cc", "spiral_ordering.tsv",
                         &MatrixInSpiralOrder, DefaultComparator{},
                         param_names);
}
