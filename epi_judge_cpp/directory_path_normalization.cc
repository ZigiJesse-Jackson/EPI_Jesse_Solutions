#include <string>
#include <stack>
#include <sstream>
#include <iostream>
#include "test_framework/generic_test.h"
using std::string;
string ShortestEquivalentPath(const string& path) {
  if(path=="") return path;
  std::stack<string> stack;
  string token;
  std::istringstream iss(path);
  string norm_path = "";
  if(path.back()=='/') norm_path = "/";

  while(std::getline(iss, token, '/')){
    if(token=="." || token.empty()) continue;
    else if(token==".." && !stack.empty() && stack.top()!="..") stack.pop();
    else stack.push(token);
  }

  if(stack.empty()){
    if(path.front()=='/' && norm_path!="/") return "/"+norm_path;
    return norm_path;
  }
  if(!stack.empty() && norm_path=="/") norm_path.clear();
  norm_path += stack.top();
  stack.pop();
  while(!stack.empty()){
    norm_path = stack.top()+"/"+norm_path;
    stack.pop();
  }
  if(path.front()=='/') norm_path = "/"+norm_path;
  return norm_path;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"path"};
  return GenericTestMain(args, "directory_path_normalization.cc",
                         "directory_path_normalization.tsv",
                         &ShortestEquivalentPath, DefaultComparator{},
                         param_names);
}
