#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 9200


void except(char *message, int fd);

int main(int argc, char *argv[]) {

  int sd;
  struct sockaddr_in s_addr, c_addr;
  char sndBuffer[BUFSIZ];
  int n, n_send;
  int addr_len;

  sd = socket(AF_INET, SOCK_DGRAM, 0);

  bzero(&s_addr, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);
  s_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

  while(1) {
    fprintf(stderr, "waiting...\n");

    if((n = read(0, sndBuffer, BUFSIZ)) > 0) {
      sndBuffer[n] = '\0';
      if(!strcmp(sndBuffer, "quit\n")) break;
      
      printf("original Data : %s", sndBuffer);
      
      if((n_send = sendto(sd, sndBuffer, strlen(sndBuffer), 0, (struct sockaddr *)&s_addr, sizeof(s_addr))) < 0) {
        except("sendto()", sd); 
      }

      addr_len = sizeof(s_addr);
      if((n = recvfrom(sd, sndBuffer, sizeof(sndBuffer), 0, NULL, NULL)) < 0) {
        except("recvfrom()", sd); 
      }
    }

    if(memcmp(



    sndBuffer[n] = '\0';
    printf("echoed Data : %s", sndBuffer);  
 } 
  close(sd);
  return 0;
}



void except(char *message, int fd) {

  printf("%s Error!\n", message);
  close(fd);
  exit(-1); 
}
