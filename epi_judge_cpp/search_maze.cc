#include <istream>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
#include <unordered_set>
using std::vector;
enum class Color
{
  kWhite,
  kBlack
};

struct Coordinate
{
  bool operator==(const Coordinate &that) const
  {
    return x == that.x && y == that.y;
  }

  int x, y;
};
struct CoordinateHash
{
  std::size_t operator()(const Coordinate &p) const
  {
    auto h1 = std::hash<int>{}(p.x);
    auto h2 = std::hash<int>{}(p.y);
    return h1 ^ (h2 << 1);
  }
};
vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate &s,
                              const Coordinate &e)
{
  vector<Coordinate> path;
  std::unordered_set<Coordinate, CoordinateHash> visited;
  path.emplace_back(s);
  visited.emplace(s);
  while (!path.empty())
  {
    Coordinate curr = path.back();
    if (curr == e)
      return path;
    Coordinate nextUp{curr.x, curr.y - 1};
    if (curr.y - 1 >= 0 && visited.count(nextUp) == 0 && maze[curr.x][curr.y] != Color::kBlack)
    {
      visited.emplace(nextUp);
      path.emplace_back(nextUp);
      continue;
    }
    Coordinate nextLeft{curr.x - 1, curr.y};
    if (curr.x - 1 >= 0 && visited.count(nextLeft) == 0 && maze[curr.x][curr.y] != Color::kBlack)
    {
      visited.emplace(nextLeft);
      path.emplace_back(nextLeft);
      continue;
    }
    Coordinate nextRight{curr.x + 1, curr.y};
    if (curr.x + 1 < maze.size() && visited.count(nextRight) == 0 && maze[curr.x][curr.y] != Color::kBlack)
    {
      visited.emplace(nextRight);
      path.emplace_back(nextRight);
      continue;
    }
    Coordinate nextDown{curr.x, curr.y + 1};
    if (curr.y + 1 < maze[0].size() && visited.count(nextDown) == 0 && maze[curr.x][curr.y] != Color::kBlack)
    {
      visited.emplace(nextDown);
      path.emplace_back(nextDown);
      continue;
    }

    path.pop_back();
  }

  return path;
}

namespace test_framework
{
  template <>
  struct SerializationTrait<Color> : SerializationTrait<int>
  {
    using serialization_type = Color;

    static serialization_type Parse(const json &json_object)
    {
      return static_cast<serialization_type>(
          SerializationTrait<int>::Parse(json_object));
    }
  };
} // namespace test_framework

namespace test_framework
{
  template <>
  struct SerializationTrait<Coordinate> : UserSerTrait<Coordinate, int, int>
  {
    static std::vector<std::string> GetMetricNames(const std::string &arg_name)
    {
      return {};
    }

    static std::vector<int> GetMetrics(const Coordinate &x) { return {}; }
  };
} // namespace test_framework

bool PathElementIsFeasible(const vector<vector<Color>> &maze,
                           const Coordinate &prev, const Coordinate &cur)
{
  if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == Color::kWhite))
  {
    return false;
  }
  return cur == Coordinate{prev.x + 1, prev.y} ||
         cur == Coordinate{prev.x - 1, prev.y} ||
         cur == Coordinate{prev.x, prev.y + 1} ||
         cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TimedExecutor &executor,
                       const vector<vector<Color>> &maze, const Coordinate &s,
                       const Coordinate &e)
{
  vector<vector<Color>> copy = maze;

  auto path = executor.Run([&]
                           { return SearchMaze(copy, s, e); });

  if (path.empty())
  {
    return s == e;
  }

  if (!(path.front() == s) || !(path.back() == e))
  {
    throw TestFailure("Path doesn't lay between start and end points");
  }

  for (size_t i = 1; i < path.size(); i++)
  {
    if (!PathElementIsFeasible(maze, path[i - 1], path[i]))
    {
      throw TestFailure("Path contains invalid segments");
    }
  }

  return true;
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "maze", "s", "e"};
  return GenericTestMain(args, "search_maze.cc", "search_maze.tsv",
                         &SearchMazeWrapper, DefaultComparator{}, param_names);
}
