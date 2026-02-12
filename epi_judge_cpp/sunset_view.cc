#include <iterator>
#include <vector>
#include <utility>
#include "test_framework/generic_test.h"
using std::vector;
vector<int> ExamineBuildingsWithSunset(
    vector<int>::const_iterator sequence_begin,
    const vector<int>::const_iterator& sequence_end) {
      if(sequence_begin==sequence_end) return {};
      vector<int> stack;
      vector<std::pair<int, int>> stack_pair;
      int idx=0, len = 0;
      stack_pair.push_back(std::make_pair(*sequence_begin++, idx++));
      while(sequence_begin!=sequence_end){
        len++;
        while(!stack_pair.empty() && *sequence_begin>=stack_pair.back().first) stack_pair.pop_back();
        stack_pair.emplace_back(std::make_pair(*sequence_begin++, idx++));
      }
  
  while(!stack_pair.empty()){
    stack.push_back((stack_pair.back().second-len)+len);
    stack_pair.pop_back();
  }
  return stack;
}
vector<int> ExamineBuildingsWithSunsetWrapper(const vector<int>& sequence) {
  return ExamineBuildingsWithSunset(cbegin(sequence), cend(sequence));
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"sequence"};
  return GenericTestMain(args, "sunset_view.cc", "sunset_view.tsv",
                         &ExamineBuildingsWithSunsetWrapper,
                         DefaultComparator{}, param_names);
}
