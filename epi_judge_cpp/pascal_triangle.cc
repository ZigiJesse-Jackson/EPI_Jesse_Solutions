#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
vector<vector<int>> GeneratePascalTriangle(int num_rows) {
  // TODO - you fill in here.
  if(num_rows==0) return {};
  vector<vector<int>> pascalTriangle {{1}};
  int i = 1;
  while(i<num_rows){
    vector<int> curr_row = pascalTriangle.back();
    vector<int> next_row(curr_row.size()+1, 0);
    int size = next_row.size()-1;
    for(int j=0;j<next_row.size()/2;j++){
      next_row[j] = (j==0?0:curr_row[j-1])+curr_row[j];
      next_row[size-j] = (j==0?0:curr_row[size-j])+curr_row[size-j-1];
    }
    if(next_row.size()%2==1){
      next_row[size/2] = curr_row[size/2]+curr_row[(size/2)-1];
    }
    pascalTriangle.push_back(next_row);
    i++;
  }
  return pascalTriangle;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"num_rows"};
  return GenericTestMain(args, "pascal_triangle.cc", "pascal_triangle.tsv",
                         &GeneratePascalTriangle, DefaultComparator{},
                         param_names);
}
