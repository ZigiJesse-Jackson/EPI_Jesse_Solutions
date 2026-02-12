#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
bool CanReachEnd(const vector<int>& max_advance_steps) {
  // TODO - you fill in here.
  
  int end = max_advance_steps.size()-1;
  int curr = max_advance_steps[0];
  if(curr>=end) return true;
  int furthest = curr;
  for(int i = 0; i <= furthest; i++){
    if(furthest>=end)return true;
    if(i+max_advance_steps[i]> furthest) furthest = i+max_advance_steps[i];
  }
  
  return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"max_advance_steps"};
  return GenericTestMain(args, "advance_by_offsets.cc",
                         "advance_by_offsets.tsv", &CanReachEnd,
                         DefaultComparator{}, param_names);
}
