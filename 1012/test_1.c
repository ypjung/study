/*
 * =====================================================
 * Q.1
 *
 * 자연수 N이 주어지면, N의 각 자릿수의 합을 구해서 return 하는 solution 함수를 만들어 주세요.
 * 예를들어 N = 123이면 1 + 2 + 3 = 6을 return 하면 됩니다.
 *
 * 제한사항
 * N의 범위 : 100,000,000 이하의 자 연 수
 * -----------------------------------------------------
 * 입출력 예
 * N	answer
 * 123	6
 * 987	24
 * 입출력 예 설명
 * 입출력 예 #1
 * 문제의 예시와 같습니다.
 *
 * 입출력 예 #2
 * 9 + 8 + 7 = 24이므로 24를 return 하면 됩니다.
 *
 * =====================================================
 * */


#include <stdio.h>
#include <string.h>

int main(int n, char *argv[]) {

  if(n < 2) {
    printf("Usage: [%s] [Number]\n", argv[0]);  
    return 0;
  }

  int num = atoi(argv[1]);
  int answer = 0; 

  if(num < 100000000) {
    while(num>0) {
      answer += num%10;
      num = num/10;
    }       
  }

  printf("answer: %d\n", answer);

  return 0;
}
