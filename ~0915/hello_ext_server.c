#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>


#define PORT 9000

char buffer[BUFSIZ] = "test server";
char rBuffer[BUFSIZ];


int main() {


  int s_socket, c_socket;
  struct sockaddr_in s_addr, c_addr;
  int n;

  char *temp;
  int length, len;


  s_socket = socket(PF_INET, SOCK_STREAM, 0); 

  memset(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);

  if(bind(s_socket, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1) {
    printf("!bind()\n");
    return 0;
  } 

  if(listen(s_socket, 5) == -1) {
    printf("!listen()\n");
    return 0;
  }  

  while(1) {

    len = sizeof(c_addr); 
    c_socket = accept(s_socket, (struct sockaddr *)&c_socket, &len);

    length = 0;
    temp = rBuffer;

    while((n = read(c_socket, temp, 1)) > 0) {
      if(*temp == '\r') continue;
      if(*temp == '\0') break;
      if(*temp == '\n') break;

      if(length == BUFSIZ) break;
      
      temp++; length++;

    }

    rBuffer[length] = '\0';

    if(!strcmp(rBuffer, "print")) {
      n = strlen(buffer);
      write(c_socket, buffer, n);
    }

    close(c_socket);
  }


  close(c_socket); 
 
  return 0;
}
