#include <vector>
#include <unordered_set>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::vector;

// bool HasThreeSum(vector<int> A, int t)
// {
//   // put everything in set
//   std::unordered_set<int> h_set;
//   for (const int &a : A)
//   {
//     h_set.insert(a);
//   }

//   // check if t divisible by 3 and result in set
//   if (t % 3 == 0 && h_set.count(t / 3) > 0)
//     return true;

//   for (int i = 0; i < A.size(); i++)
//   {
//     // check if t - 2*A[i] in set
//     if (h_set.count(t - (A[i] * 2)) > 0)
//       return true;
//     for (int j = i + 1; j < A.size(); j++)
//     {
//       // check if t - (A[i]+A[j]) in set
//       if (h_set.count(t - (A[i] + A[j])) > 0)
//         return true;
//     }
//   }

//   return false;
// }

bool HasThreeSum(vector<int> A, int t)
{

  std::sort(A.begin(), A.end());

  int new_t;
  for (int i = 0; i < A.size(); i++)
  {
    // check if t divisible by 3 and result in set
    if (t == (3 * A[i]))
      return true;

    new_t = t - A[i];
    int k = A.size() - 1;
    for (int j = i; j <= k;)
    {
      if (new_t == A[j] + A[k])
        return true;
      if (new_t < A[j] + A[k])
        k--;
      else
        j++;
    }
  }

  return false;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "t"};
  return GenericTestMain(args, "three_sum.cc", "three_sum.tsv", &HasThreeSum,
                         DefaultComparator{}, param_names);
}
