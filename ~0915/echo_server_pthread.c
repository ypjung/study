#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>

#define PORT 9000
#define BACKLOG 5


void *do_echo(void *);
void except(int fd, char *message); 

int main(int argc, char *argv[]) {

  int connSock, listenSock;
  struct sockaddr_in s_addr, c_addr;
  int len;
 
  pthread_t pthread1;
  int thr_id;

  listenSock = socket(PF_INET, SOCK_STREAM, 0);

  memset(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);

  if(bind(listenSock, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1) {
    except(listenSock, "bind()"); 
  }
  
  if(listen(listenSock, BACKLOG) == -1) {
    except(listenSock, "listen()"); 
  }

  while(1) {
    len = sizeof(c_addr);
    connSock = accept(listenSock, (struct sockaddr *)&c_addr, &len);
    
    thr_id = pthread_create(&pthread1, NULL, do_echo, (void *)connSock);
    printf("thr_id = %d\n", thr_id);

  }


  close(connSock);
  return 0;
}

void *do_echo(void *data) {

  int n;
  char recvBuffer[BUFSIZ];
  int connSock = (int)data;
  
  while((n = read(connSock, recvBuffer, sizeof(recvBuffer))) != 0) {
    write(connSock, recvBuffer, n);
  } 
}


void except(int fd, char *message) {
  
  printf("%d error\n", message);
  close(fd);
  exit(-1);
}

