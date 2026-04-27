#include <algorithm>
#include <vector>
#include <unordered_set>
#include "test_framework/generic_test.h"
#include "test_framework/test_failure.h"
#include "test_framework/timed_executor.h"
using std::vector;

bool DiffersByOneBit(int x, int y);

int getBit(int num, int pos){
  return (num & (1 << pos)) != 0;
}

int flipBit(int num, int pos){
  return num ^ (1<<pos);
}

bool getGrayCode(int num_bits, std::unordered_set<int>* const history, vector<int>* const result){
  
  if(result->size()==(1<<num_bits)){
    return DiffersByOneBit(result->front(), result->back());
  }

  int previous_code = result->back();

  for(int i = 0; i<num_bits;i++){
      int num = flipBit(previous_code, i);
      if(history->find(num)==history->end()){
        result->push_back(num);
        history->insert(num);
        if( getGrayCode(num_bits,  history, result)){
            return true;
        }
        history->erase(num);
        result->pop_back();    
      }
  }
  return false;
}


vector<int> GrayCode(int num_bits) {
  std::unordered_set<int> history{0};
  vector<int> result{0};
  getGrayCode(num_bits, &history, &result);

  return result;
}

bool DiffersByOneBit(int x, int y) {
  int bit_difference = x ^ y;
  return bit_difference && !(bit_difference & (bit_difference - 1));
}

void GrayCodeWrapper(TimedExecutor& executor, int num_bits) {
  vector<int> result = executor.Run([&] { return GrayCode(num_bits); });

  int expected_size = (1 << num_bits);
  if (result.size() != expected_size) {
    throw TestFailure("Length mismatch: expected " +
                      std::to_string(expected_size) + ", got " +
                      std::to_string(result.size()));
  }
  for (int i = 1; i < result.size(); i++)
    if (!DiffersByOneBit(result[i - 1], result[i])) {
      if (result[i - 1] == result[i]) {
        throw TestFailure("Two adjacent entries are equal");
      } else {
        throw TestFailure("Two adjacent entries differ by more than 1 bit");
      }
    }

  std::sort(begin(result), end(result));
  auto uniq = std::unique(begin(result), end(result));
  if (uniq != end(result)) {
    throw TestFailure("Not all entries are distinct: found " +
                      std::to_string(std::distance(uniq, end(result))) +
                      " duplicates");
  }
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"executor", "num_bits"};
  return GenericTestMain(args, "gray_code.cc", "gray_code.tsv",
                         &GrayCodeWrapper, DefaultComparator{}, param_names);
}
