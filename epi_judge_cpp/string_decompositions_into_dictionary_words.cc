#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

vector<int> FindAllSubstrings(const string& s, const vector<string>& words) {
  std::unordered_map<string, int> map, copy_map;
  int word_len = words[0].size();
  for(int i=0;i<words.size();i++)
  {
    if(map.find(words[i])==map.end()) map[words[i]] = 0;
    map[words[i]]+=1;
  }
  vector<int> ans;
  for(int i=0;i<s.size()-word_len+1;i++)
  {
    if(map.find(s.substr(i, word_len))!=map.end())
    {
      int last_idx = i;
      copy_map = map;
      while(!copy_map.empty() && copy_map.find(s.substr(i, word_len))!=copy_map.end())
      {
        string word = s.substr(i, word_len);
        copy_map[word]-=1;
        if(copy_map[word]==0)copy_map.erase(word);
        i+=word_len;
      }
      if(copy_map.empty()) ans.push_back(last_idx);
      i = last_idx;
    }
  }
  return ans;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s", "words"};
  return GenericTestMain(args, "string_decompositions_into_dictionary_words.cc",
                         "string_decompositions_into_dictionary_words.tsv",
                         &FindAllSubstrings, DefaultComparator{}, param_names);
}
