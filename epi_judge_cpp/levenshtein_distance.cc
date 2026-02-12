#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int LevenshteinDistance(const string& A, const string& B) {
  
  vector<vector<int>> M(A.size()+1, vector<int>(B.size()+1, 0));
  for(int i = 1;i<=A.size();i++){
    M[i][0] = i;
  }
  for(int j = 1;j<=B.size();j++){
    M[0][j] = j;
  }

  for(int i = 1;i<=A.size();i++)
  {
    for(int j = 1; j<=B.size();j++)
    {
      M[i][j] = std::min(M[i-1][j-1],std::min(M[i-1][j], M[i][j-1]))+1;
      if(A[i-1] == B[j-1]) M[i][j]= M[i-1][j-1];
    }
  }

  return M[A.size()][B.size()];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
