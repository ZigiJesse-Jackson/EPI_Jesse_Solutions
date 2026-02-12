#include <vector>
#include <list>
#include <unordered_map>
#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"

class LruCache
{
private:
  std::list<int> list;
  size_t max_cap;
  std::unordered_map<int, std::list<int>::iterator> map;

public:
  LruCache(size_t capacity) : max_cap(capacity)
  {
  }
  int Lookup(int isbn)
  {
    if (map.find(isbn) != map.end())
    {
      int val = *map[isbn];
      list.erase(map[isbn]);
      list.push_front(val);
      map[isbn] = list.begin();
      return val;
    }
    return -1;
  }
  void Insert(int isbn, int price)
  {
    if (map.find(isbn) != map.end())
    {
      int val = *map[isbn];
      list.erase(map[isbn]);
      list.push_front(val);
      map[isbn] = list.begin();
    }
    else
    {
      list.push_front(price);
      map[isbn] = list.begin();
    }
    if (list.size() > max_cap)
    {
      int isbn = get_LRU_key();
      list.pop_back();
      map.erase(isbn);
    }
    return;
  }
  bool Erase(int isbn)
  {
    if(map.find(isbn)==map.end()) return false;
    list.erase(map[isbn]);
    map.erase(isbn);
    return true;
  }

  int get_LRU_key()
  {
    auto itr = std::prev(list.end());
    for (std::pair<int, std::list<int>::iterator> p : map)
    {
      if(p.second == itr) return p.first;
    }
    return -1;
  }
};
struct Op
{
  std::string code;
  int arg1;
  int arg2;
};

namespace test_framework
{
  template <>
  struct SerializationTrait<Op> : UserSerTrait<Op, std::string, int, int>
  {
  };
} // namespace test_framework

void LruCacheTester(const std::vector<Op> &commands)
{
  if (commands.empty() || commands[0].code != "LruCache")
  {
    throw std::runtime_error("Expected LruCache as first command");
  }
  LruCache cache(commands[0].arg1);

  for (int i = 1; i < commands.size(); i++)
  {
    auto &cmd = commands[i];
    if (cmd.code == "lookup")
    {
      int result = cache.Lookup(cmd.arg1);
      if (result != cmd.arg2)
      {
        throw TestFailure("Lookup: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    }
    else if (cmd.code == "insert")
    {
      cache.Insert(cmd.arg1, cmd.arg2);
    }
    else if (cmd.code == "erase")
    {
      bool result = cache.Erase(cmd.arg1);
      if (result != cmd.arg2)
      {
        throw TestFailure("Erase: expected " + std::to_string(cmd.arg2) +
                          ", got " + std::to_string(result));
      }
    }
    else
    {
      throw std::runtime_error("Unexpected command " + cmd.code);
    }
  }
}

int main(int argc, char *argv[])
{
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"commands"};
  return GenericTestMain(args, "lru_cache.cc", "lru_cache.tsv", &LruCacheTester,
                         DefaultComparator{}, param_names);
}
