#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define PORT 9000
#define IPADDR "127.0.0.1"

char buffer[BUFSIZ];

int main() {

  int c_socket;
  struct sockaddr_in c_addr;
  int len;

  char recvBuffer[BUFSIZ];
  char *temp;
  int length = 0;

  int n;

  c_socket = socket(PF_INET, SOCK_STREAM, 0);
  
  memset(&c_socket, 0, sizeof(c_addr)); 
  c_addr.sin_addr.s_addr = inet_addr(IPADDR);
  c_addr.sin_family = AF_INET;
  c_addr.sin_port = htons(PORT);


  //connect(c_socket, (struct sockaddr *)&c_addr, sizeof(c_addr));

  if(connect(c_socket, (struct sockaddr *)&c_addr, sizeof(c_addr)) == -1) {
    printf("!connect()\n");
    close(c_socket);
    return 0; 
  }   

  scanf("%s", buffer);
  buffer[strlen(buffer)] = '\0';
  // fail
  if((n = write(c_socket, &buffer, sizeof(buffer)+1)) == -1) {
    printf("!write()\n");
    close(c_socket);
    return 0;    
  }
 
  // sucess
  temp = recvBuffer;
  while(n = read(c_socket, temp, 1) == -1) {
    if(length == BUFSIZ) break;
    length++, temp++; 
  }
  
  recvBuffer[length] = '\0';

  printf("recvBuffer = %s\n", recvBuffer);

  close(c_socket); 

  return 0;
}
