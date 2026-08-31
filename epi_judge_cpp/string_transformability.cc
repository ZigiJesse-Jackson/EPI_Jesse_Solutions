#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>

#include "test_framework/generic_test.h"
using std::string;
using std::unordered_set;

int BFS(const std::unordered_set<string> &words, std::unordered_map<string, int> &graph, const string &source, const string &dest)
{
  std::queue<string> q;
  q.emplace(source);
  std::unordered_set<string> visited;
  graph[source] = 0;
  while (!q.empty())
  {
    const string curr = q.front();
    q.pop();
    if (curr == dest)
    {
      return graph[dest];
    }
    if (visited.count(curr) == 0)
    {
      visited.insert(curr);

      string adj_word = curr;
      for (int i = 0; i < curr.size(); i++)
      {
        for (char c = 'a'; c <= 'z'; c++)
        {
          adj_word[i] = c;
          if (words.count(adj_word) == 0)
          {
            continue;
          }
          if (visited.count(adj_word) == 0)
          {
            q.emplace(adj_word);
          }

          if (graph.count(adj_word) == 0)
          {
            graph[adj_word] = INT_MAX;
          }
          graph[adj_word] = std::min(graph[adj_word], graph[curr] + 1);
        }
        adj_word[i] = curr[i];
      }
    }
  }

  return -1;
}

int TransformString(unordered_set<string> D, const string &s, const string &t)
{
  if (s == t)
    return 0;
  std::unordered_map<string, int> graph;

  return BFS(D, graph, s, t);
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"D", "s", "t"};
  return GenericTestMain(args, "string_transformability.cc",
                         "string_transformability.tsv", &TransformString,
                         DefaultComparator{}, param_names);
}
