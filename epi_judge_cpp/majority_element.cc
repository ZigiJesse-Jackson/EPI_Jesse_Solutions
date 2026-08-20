#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

// string MajoritySearch(vector<string>::const_iterator stream_begin,
//                       const vector<string>::const_iterator stream_end)
// {
//   int max_freq = 0;
//   string res = "";
//   std::unordered_map<string, int> freq_count;
//   while (stream_begin != stream_end)
//   {
//     if (freq_count.count(*stream_begin) == 0)
//     {
//       freq_count[*stream_begin] = 0;
//     }
//     freq_count[*stream_begin] += 1;
//     if (max_freq < freq_count[*stream_begin])
//     {
//       res = *stream_begin;
//       max_freq = freq_count[*stream_begin];
//     }
//     stream_begin++;
//   }

//   return res;
// }

string MajoritySearch(vector<string>::const_iterator stream_begin,
                      const vector<string>::const_iterator stream_end)
{
  int candidate_freq = 0;
  string candidate = *stream_begin;
  while (stream_begin != stream_end)
  {
    candidate_freq = candidate == *stream_begin ? candidate_freq + 1 : candidate_freq - 1;
    if (candidate_freq == 0)
    {
      candidate = *stream_begin;
      candidate_freq = 1;
    }
    stream_begin++;
  }

  return candidate;
}

string MajoritySearchWrapper(const vector<string> &stream)
{
  return MajoritySearch(cbegin(stream), cend(stream));
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"stream"};
  return GenericTestMain(args, "majority_element.cc", "majority_element.tsv",
                         &MajoritySearchWrapper, DefaultComparator{},
                         param_names);
}
