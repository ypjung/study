#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>


#define PORT 9000
#define IPADDR "127.0.0.1"

char buffer[BUFSIZ];

int main() {

  int c_socket;
  struct sockaddr_in c_addr;
  int length;
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

  scanf("%s", &buffer);
  
  write(c_socket, buffer, strlen(buffer)+1);
  
  if((n = read(c_socket, recvBuffer, sizeof(recvBuffer))) < 0) {
    //close(c_socket);
    return 0;
  }

  recvBuffer[n] = '\0'; 

  printf("recvBuffer = %s\n", recvBuffer);

  return 0;
}
