#include <string>
#include <unordered_map>
#include <unordered_set>
#include "test_framework/generic_test.h"
using std::string;

bool IsLetterConstructibleFromMagazine(const string &letter_text,
                                       const string &magazine_text)
{
  if (letter_text.size() > magazine_text.size())
    return false;
  std::unordered_set<char> letters_set_letter;
  std::unordered_set<char> letters_set_magazine;
  std::unordered_map<char, int> letters_map_letter;
  std::unordered_map<char, int> letters_map_magazine;

  for (char c : letter_text)
  {
    if (!std::isalnum(c))
      continue;
    c = c + ('a' - 'A');
    if (letters_map_letter.find(c) == letters_map_letter.end())
      letters_map_letter[c] = 0;
      letters_set_letter.insert(c);
    letters_map_letter[c]++;
  }
  for (char c : magazine_text)
  {
    if (!std::isalnum(c))
      continue;
    c = c + ('a' - 'A');
    if (letters_map_magazine.find(c) == letters_map_magazine.end())
      letters_map_magazine[c] = 0;
      letters_set_magazine.insert(c);
    letters_map_magazine[c]++;
  }

  if (letters_set_letter.size() > letters_set_magazine.size())
    return false;
  auto set_itr = letters_set_letter.begin();
  while (set_itr != letters_set_letter.end())
  {
    char curr = *set_itr;

    if (letters_set_magazine.find(curr) == letters_set_magazine.end())
      return false;
    if(letters_map_letter[curr]>letters_map_magazine[curr]) return false;
    set_itr++;
  }

  

  return true;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
