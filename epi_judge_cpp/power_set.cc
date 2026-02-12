#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

void compute_powerset(const vector<int>& input_set, int idx, vector<int> subset, vector<vector<int>>* const powerset){
  if(idx>=input_set.size()){
    powerset->push_back(subset);
    return;
  }

    // do not add element
    compute_powerset(input_set, idx+1, subset, powerset);
    // add element to subset
    subset.push_back(input_set[idx]);
    compute_powerset(input_set, idx+1, subset, powerset);
}

vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
  // TODO - you fill in here.
  vector<vector<int>> powerset = {};
  compute_powerset(input_set, 0, {}, &powerset);
  return powerset;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"input_set"};
  return GenericTestMain(args, "power_set.cc", "power_set.tsv",
                         &GeneratePowerSet, UnorderedComparator{}, param_names);
}
