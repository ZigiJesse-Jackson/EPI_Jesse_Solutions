#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

double FindSalaryCap(int target_payroll, vector<int> current_salaries) {
  if(target_payroll>std::accumulate(current_salaries.begin(), current_salaries.end(), 0)) return -1;
  sort(current_salaries.begin(), current_salaries.end());
  double cap = target_payroll;
  int count = current_salaries.size();
  int idx = 0;
  while(idx < current_salaries.size() && (cap/count)>current_salaries[idx])
  {
    cap-=current_salaries[idx++];
    count-=1;
  }

  if( (cap/count)<=0) return -1;
  return cap/count;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"target_payroll", "current_salaries"};
  return GenericTestMain(args, "find_salary_threshold.cc",
                         "find_salary_threshold.tsv", &FindSalaryCap,
                         DefaultComparator{}, param_names);
}
