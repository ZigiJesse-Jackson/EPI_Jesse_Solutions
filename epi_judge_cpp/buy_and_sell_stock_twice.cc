#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockTwice(const vector<double>& prices) {
  // TODO - you fill in here.
  double profit = 0;
  int buy = 0;
  vector<double> best_buy_sell = {};

  for(int i = 1; i<prices.size();i++){
    if(prices[buy]>prices[i]) buy = i;
    profit = std::max(profit, prices[i]-prices[buy]);
    best_buy_sell.push_back(profit);
  }
  int sell = prices.size()-1;
  double result = 0;
  profit = 0;
  for(int i = prices.size()-1;i>0;i--){
    if(prices[sell]<prices[i]) sell = i;
    profit = std::max(profit, prices[sell]-prices[i]);
    result = std::max(result, best_buy_sell[i-1]+profit);
  }

  return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock_twice.cc",
                         "buy_and_sell_stock_twice.tsv", &BuyAndSellStockTwice,
                         DefaultComparator{}, param_names);
}
