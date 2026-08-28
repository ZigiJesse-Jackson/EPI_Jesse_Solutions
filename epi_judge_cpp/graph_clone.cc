#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
using std::queue;
using std::unordered_set;
using std::vector;

struct GraphVertex
{

  int label;
  enum Color
  {
    white,
    black
  } color = white;
  vector<GraphVertex *> edges;
};

GraphVertex *CloneGraph(GraphVertex *graph)
{
  if (!graph)
    return nullptr;

  std::unordered_map<GraphVertex *, GraphVertex *> cloneMap;
  GraphVertex *sentinel = new GraphVertex{0};

  queue<GraphVertex *> q;
  queue<GraphVertex *> parentQ;

  q.push(graph);
  parentQ.push(sentinel);

  while (!q.empty())
  {
    auto curr = q.front();
    q.pop();

    GraphVertex *currClone = nullptr;

    if (curr->color == GraphVertex::white)
    {
      currClone = new GraphVertex{curr->label};
      cloneMap[curr] = currClone;
      curr->color = GraphVertex::black;

      // Connect to parent
      if (!parentQ.empty())
      {
        parentQ.front()->edges.push_back(currClone);
        parentQ.pop();
      }

      // Process children
      for (auto edge : curr->edges)
      {
        q.push(edge);
        parentQ.push(currClone); // push parent for this child
      }
    }
    else
    {
      // Already visited — look up existing clone and connect to parent
      currClone = cloneMap[curr];
      if (!parentQ.empty())
      {
        parentQ.front()->edges.push_back(currClone);
        parentQ.pop();
      }
    }
  }

  return sentinel->edges[0];
}

vector<int> CopyLabels(const vector<GraphVertex *> &edges)
{
  vector<int> labels;
  transform(begin(edges), end(edges), back_inserter(labels),
            [](const auto &e)
            { return e->label; });
  return labels;
}

void CheckGraph(GraphVertex *node, const vector<GraphVertex> &graph)
{
  if (!node || node == &graph[0])
  {
    throw TestFailure("Graph was not copied");
  }

  unordered_set<GraphVertex *> vertex_set;
  queue<GraphVertex *> q;
  q.emplace(node);
  vertex_set.emplace(node);
  while (!q.empty())
  {
    auto vertex = q.front();
    q.pop();
    if (vertex->label >= graph.size())
    {
      throw TestFailure("Invalid vertex label");
    }
    vector<int> label1 = CopyLabels(vertex->edges),
                label2 = CopyLabels(graph[vertex->label].edges);
    sort(begin(label1), end(label1));
    sort(begin(label2), end(label2));
    if (label1 != label2)
    {
      throw TestFailure("Edges mismatch");
    }
    for (GraphVertex *e : vertex->edges)
    {
      if (vertex_set.emplace(e).second)
      {
        q.emplace(e);
      }
    }
  }
  for (auto &v : vertex_set)
  {
    delete v;
  }
}

struct Edge
{
  int from;
  int to;
};

namespace test_framework
{
  template <>
  struct SerializationTrait<Edge> : UserSerTrait<Edge, int, int>
  {
  };
} // namespace test_framework

void CloneGraphTest(int k, const vector<Edge> &edges)
{
  vector<GraphVertex> graph;
  if (k <= 0)
  {
    throw std::runtime_error("Invalid k value");
  }
  graph.reserve(k);

  for (int i = 0; i < k; i++)
  {
    graph.push_back(GraphVertex{i});
  }

  for (const Edge &e : edges)
  {
    if (e.from < 0 || e.from >= k || e.to < 0 || e.to >= k)
    {
      throw std::runtime_error("Invalid vertex index");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }
  GraphVertex *result = CloneGraph(&graph[0]);
  CheckGraph(result, graph);
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"k", "edges"};
  return GenericTestMain(args, "graph_clone.cc", "graph_clone.tsv",
                         &CloneGraphTest, DefaultComparator{}, param_names);
}
