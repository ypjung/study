/*두 수를 입력받아 두 수의 최대공약수와 최소공배수를 반환해주는 gcdlcm 함수를 완성해 보세요. 배열의 맨 앞에 최대공약수, 그 다음 최소공배수를 넣어 반환하면 됩니다. 예를 들어 gcdlcm(3,12) 가 입력되면, [3, 12]를 반환해주면 됩니다.
 */

#include<vector>
#include<iostream>
using namespace std;
vector<int> gcdlcm(int a,int b)
{
	vector<int> answer;

	return answer;
}

int main()
{
	int a=3, b=12;
	vector<int> testAnswer = gcdlcm(a,b);

	cout<<testAnswer[0]<<" "<<testAnswer[1];
}
