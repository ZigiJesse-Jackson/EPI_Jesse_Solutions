#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<int> PlusOne(vector<int> A) {
  // TODO - you fill in here.
  vector<int> ans;
  A.back()+=1;
  for(int i = A.size()-1;i>0;i--){
    A[i-1] += A[i]/10;
    A[i] %=10;
    ans.push_back(A[i]); 
  }
  ans.push_back(A[0]%10);
  if(A[0]>=10) ans.push_back(1);
  std::reverse(ans.begin(), ans.end());
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A"};
  return GenericTestMain(args, "int_as_array_increment.cc",
                         "int_as_array_increment.tsv", &PlusOne,
                         DefaultComparator{}, param_names);
}
