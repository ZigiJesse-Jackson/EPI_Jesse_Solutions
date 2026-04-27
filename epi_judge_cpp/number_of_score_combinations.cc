#include <vector>

#include "test_framework/generic_test.h"
using std::vector;

int NumCombinationsForFinalScore(int final_score, const vector<int>& individual_play_scores) {
  vector<vector<int>> dp_matrix = vector(individual_play_scores.size()+1, vector<int>(final_score+1, 0)); 
  for(int i= 1; i<=individual_play_scores.size();i++){
    for(int j= 0; j<=final_score;j++){
        if(j==0){
          dp_matrix[i][j] = 1;
          continue;
        }
        int curr_score = individual_play_scores[i-1];
        dp_matrix[i][j] = dp_matrix[i-1][j] + (j-curr_score >= 0 ? dp_matrix[i][j-curr_score]:0);
    }
  }
  return dp_matrix[individual_play_scores.size()][final_score];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
