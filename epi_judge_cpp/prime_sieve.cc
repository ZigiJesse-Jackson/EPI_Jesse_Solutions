#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
// Given n, return all primes up to and including n.
vector<int> GeneratePrimes(int n) {
  // TODO - you fill in here.
  vector<int> ans;
  vector<bool> is_prime = vector<bool>(n+1, TRUE);
  for(int i = 2; i<=n;i++){
    if(is_prime[i]){
      ans.push_back(i);
      for(int j = i+i; j<=n;j+=i){
        is_prime[j] = FALSE;
      }
    }
  }

  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n"};
  return GenericTestMain(args, "prime_sieve.cc", "prime_sieve.tsv",
                         &GeneratePrimes, DefaultComparator{}, param_names);
}
