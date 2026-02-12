#include <string>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;

bool CanFormPalindrome(const string &s)
{
  std::unordered_map<char, int> map;
  int len = 0;
  for (char c : s)
  {
    if (!std::isalpha(c))
      continue;
    c = c + ('a' - 'A');
    if (map.find(c) == map.end())
      map[c] = 0;
    map[c]++;
    len++;
  }
  bool odd = false;
  if (len % 2 == 1)
    odd = true;
  for (std::pair<char, int> p : map)
  {
    if (p.second % 2 == 1)
    {
      if(!odd)
        return false;
      odd = false;
    }
  }
  return true;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "is_string_permutable_to_palindrome.cc",
                         "is_string_permutable_to_palindrome.tsv",
                         &CanFormPalindrome, DefaultComparator{}, param_names);
}
