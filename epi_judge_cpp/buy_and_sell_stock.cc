#include <vector>
#include <algorithm>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  // TODO - you fill in here.
  double profit = 0;
  double buy = prices[0];
  for(int i=0;i<prices.size();i++){
    if(prices[i]<buy) buy = prices[i];
    else{
      profit = std::max(profit, prices[i]-buy);
    }
  } 
  return profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
