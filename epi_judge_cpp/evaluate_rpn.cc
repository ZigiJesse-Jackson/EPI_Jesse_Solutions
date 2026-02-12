#include <string>
#include <stack>
#include <iostream>
#include "test_framework/generic_test.h"
using std::string;
int Evaluate(const string& expression) {
  // TODO - you fill in here.
  string builder;
  std::stack<int> stack;
  for(char c: expression){
    if(c>='0' && c<='9') builder.push_back(c);
    else if(c==',' && !builder.empty()){
      stack.push(stoi(builder));
      builder.clear();
    }
    else{
      int curr;
      switch(c){
        case '+':
          curr = stack.top();
          stack.pop();
          stack.top()+=curr;
          break;
        case '*':
          curr = stack.top();
          stack.pop();
          stack.top()*=curr;
          break;
        case '-':
          curr = stack.top();
          stack.pop();
          stack.top()-=curr;
          break;
        case '/':
          curr = stack.top();
          stack.pop();
          stack.top()/=curr;
          break;
        default:
          break;
      }
    }
  }

  if(!builder.empty()){
    stack.push(stoi(builder));
  }

  return stack.top();
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"expression"};
  return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                         DefaultComparator{}, param_names);
}
