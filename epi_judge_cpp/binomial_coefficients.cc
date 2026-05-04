#include "test_framework/generic_test.h"
#include <vector>

int ComputeBinomialCoefficient(int n, int k) {
  if(k==0 ) return 1;
  if(n==0) return 0;
  
  std::vector<std::vector<int>> dp(k,std::vector<int>(n, 0));
  for(int i=0;i<k;i++){
    for(int j=0;j<n;j++){
      if(i==0){
        dp[i][j] = j+1;
      }
      else if(i==j){
        dp[i][j] = 1;
      }
      else if(j==0){
        continue;
      }
      else{
        dp[i][j] = dp[i][j-1]+dp[i-1][j-1];
      }
    }
  }
  return dp[k-1][n-1];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(
      args, "binomial_coefficients.cc", "binomial_coefficients.tsv",
      &ComputeBinomialCoefficient, DefaultComparator{}, param_names);
}
