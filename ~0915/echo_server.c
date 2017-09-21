#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 9000
#define BACKLOG 5


int main() {
  
  int c_socket, s_socket;
  struct sockaddr_in s_addr, c_addr;
  int len;

  int n;
  char recvBuffer[BUFSIZ];

  s_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  memset(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);
  
  if(bind(s_socket, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1) {
    printf("!bind()\n");
    return 0;
  }

  if(listen(s_socket, BACKLOG) == -1) {
    printf("listen Fail\n");
    return 0;
  }  
  
  while(1) {
    len = sizeof(c_addr);
    c_socket = accept(s_socket, (struct sockaddr *)&c_addr, &len);

    while((n = read(c_socket, recvBuffer, sizeof(recvBuffer))) != 0) {
      recvBuffer[n] = '\0'; 
      printf("%s", recvBuffer);
      write(c_socket, recvBuffer, n);
    }
    close(c_socket);
  }

  close(s_socket);

  return 0;
}
