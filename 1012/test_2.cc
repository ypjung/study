

#include <vector>
using namespace std;

bool solution(vector<int> arr)
{
	bool answer = true;
    int cur_n = 0;
    vector<int> temp;
    
    if (arr.size() >= 100000) {
      while(!(arr[cur_n])) {
        if(arr[cur_n] >= 100000) {
          if(temp[arr[cur_n]] != 1) {
            temp[arr[cur_n]] = 1;
            cur_n++;
          }
          else if (temp[arr[cur_n]] == 1) {
            return !answer;
          }
        }
      }
    }
    
	return answer;
}
