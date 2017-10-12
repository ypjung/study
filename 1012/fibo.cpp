/* 피보나치 수는 F(0) = 0, F(1) = 1일 때, 2 이상의 n에 대하여 F(n) = F(n-1) + F(n-2) 가 적용되는 점화식입니다. 2 이상의 n이 입력되었을 때, fibonacci 함수를 제작하여 n번째 피보나치 수를 반환해 주세요. 예를 들어 n = 3이라면 2를 반환해주면 됩니다.
 */

#include<iostream>
using namespace std;

long long fibonacci(int n) {

  if(n < 2)
    return n;	

  else
    return fibonacci(n-1) +fibonacci(n-2);
}

int main()
{
	int testCase = 10;
	long long testAnswer = fibonacci(testCase);

	cout<<testAnswer<<endl;
}
