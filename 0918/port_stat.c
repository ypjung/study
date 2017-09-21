#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#define PORT 9000
#define BACKLOG 5


void except(char *message, int sd);

int main() {

  int sd;
  struct sockaddr_in s_addr, c_addr;
  int c_len;
  int c_socket;
  char greeting[] = "TCP test";


  sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  memset(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);

  if(bind(sd, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1) {
    except("bind()", sd);
  }

  if(listen(sd, BACKLOG) == -1) {
    except("listen()", sd);
  }

  while(1) {

   c_len = sizeof(c_addr); 
   c_socket = accept(sd, (struct sockaddr *)&c_addr, &c_len);
   
   write(c_socket, greeting, strlen(greeting));
    
  }

  return 0;
}

void except(char *message, int sd) {

  printf("%s error\n", message);
  close(sd);
  exit(-1);
}
