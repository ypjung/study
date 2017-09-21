#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>



 main() {
 
  int tcpSd;
  struct sockaddr_in s_addr;
 
  if((tcpSd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    perror("socket()");
    exit(-1);
  }
 
  bzero((char *)&s_addr, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  inet_aton("123.456.789.012", &s_addr.sin_addr.s_addr);
  s_addr.sin_port = htons(7);
 
  printf("ip(dotted decial) = %s\n", inet_ntoa( s_addr.sin_addr.s_addr));
  printf("ip(binary) = %x\n", ntohl(s_addr.sin_addr.s_addr));
  printf("port no = %d\n", ntohs(s_addr.sin_port));
 

  close(tcpSd);
}
