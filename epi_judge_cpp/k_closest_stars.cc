#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_utils.h"
using std::vector;

struct Star
{
  bool operator<(const Star &that) const
  {
    return Distance() < that.Distance();
  }

  double Distance() const { return sqrt(x * x + y * y + z * z); }

  double x, y, z;
};

vector<Star> FindClosestKStars(vector<Star>::const_iterator stars_begin,
                               const vector<Star>::const_iterator &stars_end,
                               int k)
{

  std::priority_queue<Star, vector<Star>, std::less<>> max_heap;
  while (stars_begin != stars_end)
  {
    if (max_heap.size() <k+1)
    {
      max_heap.emplace(*stars_begin);
      stars_begin = std::next(stars_begin);
    }
    else
    {
      max_heap.pop();
    }
  }
  if(max_heap.size()>k) max_heap.pop();
  vector<Star> res;
  while (!max_heap.empty())
  {
    res.push_back(max_heap.top());
    max_heap.pop();
  }
  

  std::reverse(res.begin(), res.end());

  return res;
}

namespace test_framework
{
  template <>
  struct SerializationTrait<Star> : UserSerTrait<Star, double, double, double>
  {
  };
} // namespace test_framework

std::ostream &operator<<(std::ostream &out, const Star &s)
{
  return out << s.Distance();
}

bool Comp(const vector<double> &expected, vector<Star> output)
{
  if (output.size() != expected.size())
  {
    return false;
  }

  std::sort(begin(output), end(output));

  for (int i = 0; i < output.size(); ++i)
  {
    if (!DefaultComparator()(output[i].Distance(), expected[i]))
    {
      return false;
    }
  }
  return true;
}

vector<Star> FindClosestKStarsWrapper(const vector<Star> &stars, int k)
{
  return FindClosestKStars(cbegin(stars), cend(stars), k);
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stars", "k"};
  return GenericTestMain(args, "k_closest_stars.cc", "k_closest_stars.tsv",
                         &FindClosestKStarsWrapper, &Comp, param_names);
}
