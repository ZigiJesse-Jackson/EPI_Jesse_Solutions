#include <vector>
#include "test_framework/generic_test.h"
using std::vector;

struct ABSqrt2
{
  ABSqrt2(int a, int b) : a(a), b(b), val(a + b * std::sqrt(2)) {}

  bool operator<(const ABSqrt2 &that) const { return val < that.val; }
  int a, b;
  double val;
};

vector<double> GenerateFirstKABSqrt2(int k)
{
  int i = 0, j = 0;
  vector<ABSqrt2> res(1, ABSqrt2(0, 0));
  while (res.size() < k)
  {
    ABSqrt2 i_plus_1(res[i].a+1, res[i].b);
    ABSqrt2 j_plus_1(res[j].a, res[j].b+1);
    res.push_back(std::min(i_plus_1, j_plus_1));
    if (res.back().val==i_plus_1.val)
    {
      i++;
    }
    if(res.back().val == j_plus_1.val)
    {
      j++;
    }
  }
  vector<double> first_k(k, 0);
  for(int x=0;x<k;x++)
  {
    first_k[x] = res[x].val;
  }
  return first_k;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k"};
  return GenericTestMain(args, "a_b_sqrt2.cc", "a_b_sqrt2.tsv",
                         &GenerateFirstKABSqrt2, DefaultComparator{},
                         param_names);
}
