#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int MinimumMessiness(const vector<string> &words, int line_length)
{
  vector<int> messiness(words.size(), INT32_MAX);
  int new_remaining_line = line_length - words[0].size();
  messiness[0] = new_remaining_line * new_remaining_line;
  for (int i = 1; i < words.size(); i++)
  {
    // creating new line and keeping track of running sum messiness at current idx
    new_remaining_line = line_length - words[i].size();
    messiness[i] = new_remaining_line * new_remaining_line + messiness[i - 1];
    for (int j = i - 1; j >= 0; j--)
    {
      // making new line containing words from j to i
      new_remaining_line -= (words[j].size() + 1);
      // words no longer fit on new line
      if (new_remaining_line < 0)
      {
        break;
      }
      // calculating messiness at current line
      int new_line_messiness = new_remaining_line * new_remaining_line;
      // getting messiness if prev line ends w word j-1
      int old_messiness = j - 1 < 0 ? 0 : messiness[j - 1];
      // checking if messiness with curr line built and messiness accumulated up to word j-1 is the best min overall we've found
      messiness[i] = std::min(messiness[i], old_messiness + new_line_messiness);
    }
  }
  return messiness.back();
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"words", "line_length"};
  return GenericTestMain(args, "pretty_printing.cc", "pretty_printing.tsv",
                         &MinimumMessiness, DefaultComparator{}, param_names);
}
