#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 9000 
#define IPADDR "127.0.0.1"


int main(void) {

  int c_socket;
  struct sockaddr_in c_addr;
  int len;
  int n;

  char recvBuffer[BUFSIZ];

  c_socket = socket(PF_INET, SOCK_STREAM, 0);

  memset(&c_addr, 0, sizeof(c_addr));
  c_addr.sin_addr.s_addr = inet_addr(IPADDR);
  c_addr.sin_family = AF_INET;
  c_addr.sin_port = htons(PORT);
  
  if(connect(c_socket, (struct sockaddr *)&c_addr, sizeof(c_addr)) == -1) {

    printf("!connect()\n");
    close(c_socket);
    return 0;
  }

  if((n = read(c_socket, recvBuffer, sizeof(recvBuffer))) == -1 ) {
    return 0;
  }

  recvBuffer[n] = '\0';

  printf("recvBuffer = %s\n", recvBuffer);

  close(c_socket);

  return 0;
}
