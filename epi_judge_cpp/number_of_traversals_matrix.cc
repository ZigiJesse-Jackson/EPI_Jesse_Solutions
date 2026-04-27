#include "test_framework/generic_test.h"
#include <vector>
int NumberOfWays(int n, int m) {
  std::vector<std::vector<int>> dp_matrix( n, std::vector<int>(m, 1));
  if(n ==1 || m == 1) return 1;
  for(int i = 1; i<n;i++){
    for(int j = 1;j<m;j++){
      dp_matrix[i][j] = dp_matrix[i-1][j]+dp_matrix[i][j-1];
    }
  }
  return dp_matrix[n-1][m-1];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
