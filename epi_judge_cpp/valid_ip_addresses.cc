#include <algorithm>
#include <string>
#include <vector>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

bool validateSegment(string segment){
  if(segment.size()>3) return false;
  if(segment.front()=='0' && segment.size()>1) return false;
  if(stoi(segment)>255) return false;
  return true;
}


vector<string> GetValidIpAddress(const string& s) {
  // TODO - you fill in here.
  vector<string> ip_addresses;
  for(int i_1=1;i_1<s.size();i_1++){
    string first = s.substr(0, i_1);
    if(!validateSegment(first)) continue;
    first.push_back('.');

    for(int i_2=1;i_1+i_2<s.size() && i_2<4;i_2++){
      string second = s.substr(i_1, i_2);
      if(!validateSegment(second)) continue;
      second.push_back('.');

      for(int i_3=1;i_1+i_2+i_3<s.size() && i_3<4;i_3++){
        string third = s.substr(i_1+i_2, i_3);
        if(!validateSegment(third)) continue;
        third.push_back('.');
        string fourth = s.substr(i_1+i_2+i_3);
        if(!validateSegment(fourth)) continue;
          ip_addresses.push_back(first+second+third+fourth);
      }

    }

  }
  return ip_addresses;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"s"};
  return GenericTestMain(args, "valid_ip_addresses.cc",
                         "valid_ip_addresses.tsv", &GetValidIpAddress,
                         UnorderedComparator{}, param_names);
}
