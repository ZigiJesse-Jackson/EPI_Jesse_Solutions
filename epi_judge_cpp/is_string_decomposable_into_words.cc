#include <string>
#include <unordered_set>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::string;
using std::unordered_set;
using std::vector;

vector<string> DecomposeIntoDictionaryWords(
    const string &domain, const unordered_set<string> &dictionary)
{
  vector<int> memo(domain.size(), -1);
  for (int i = 0; i < domain.size(); i++)
  {
    if (dictionary.count(domain.substr(0, i + 1)) > 0)
    {
      memo[i] = 0;
    }
    else
    {
      for (int j = i - 1; j >= 0; j--)
      {
        if (memo[j] > -1 && dictionary.count(domain.substr(j + 1, i - j)) > 0)
        {
          memo[i] = j + 1;
          break;
        }
      }
    }
  }

  if (memo.back() == -1)
  {
    return {};
  }
  int end = domain.size() - 1;

  vector<string> res;
  while (end > -1)
  {
    int start = memo[end];
    res.push_back(domain.substr(memo[end], end - start + 1));
    end = memo[end] - 1;
  }
  std::reverse(res.begin(), res.end());
  return res;
}

void DecomposeIntoDictionaryWordsWrapper(
    TimedExecutor &executor, const string &domain,
    const unordered_set<string> &dictionary, bool decomposable)
{
  vector<string> result = executor.Run(
      [&]
      { return DecomposeIntoDictionaryWords(domain, dictionary); });
  if (!decomposable)
  {
    if (!result.empty())
    {
      throw TestFailure("domain is not decomposable");
    }
    return;
  }

  if (std::any_of(std::begin(result), std::end(result),
                  [&](const std::string &s)
                  { return !dictionary.count(s); }))
  {
    throw TestFailure("Result uses words not in dictionary");
  }

  if (std::accumulate(std::begin(result), std::end(result), string()) !=
      domain)
  {
    throw TestFailure("Result is not composed into domain");
  }
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "domain", "dictionary",
                                       "decomposable"};
  return GenericTestMain(args, "is_string_decomposable_into_words.cc",
                         "is_string_decomposable_into_words.tsv",
                         &DecomposeIntoDictionaryWordsWrapper,
                         DefaultComparator{}, param_names);
}
