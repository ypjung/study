#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>

#define PORT 9200

void except(char *message, int fd);

int main(int argc, char *argv[]) {
 
  int sd;
  struct sockaddr_in s_addr, c_addr;
  char buff[BUFSIZ];
  int n, n_recv;
  int addr_len;
  
  sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  
  bzero(&s_addr, sizeof(s_addr));
  s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);

  if(bind(sd, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1) {

    except("bind()", sd);
/*    printf("!bind()\n");
    close(sd);
    exit(-1); */
  }

  while(1) {
    fprintf(stderr, "waiting\n");

    addr_len = sizeof(c_addr);
    if((n_recv = recvfrom(sd, buff, sizeof(buff), 0, (struct sockaddr *)&c_addr, &addr_len)) < 0) {
      fprintf(stderr, "recvfrom() error");
      exit(-1);
    }
     
    if((n = sendto(sd, buff, n_recv, 0, (struct sockaddr *)&c_addr, sizeof(c_addr))) < 0) {
      fprintf(stderr, "sendto() error");
      exit(-1);
    }
  }
  
  close(sd); 
  return 0;
}



void except(char *message, int fd) {

  printf("%s Error!\n", message);
  close(fd);
  exit(-1); 
}
