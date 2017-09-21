#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

void do_keyboard(int);
void do_socket(int);

char quit[] = "exit";

pid_t pid;

int main(int argc, char *argv[]) {

  int listenSock, connSock;
  struct sockaddr_in client_addr, server_addr;

  int len;

  if(argc < 2)  {
    printf("Usage: talkServer port_num ");
    return -1;
  }

  if((listenSock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Server: Can't open Socket\n");
    return -1;
  }

  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[1]));
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  if(bind(listenSock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("talkserver can't bind\n");
    return -1;
  } 
 
  listen(listenSock, 1);

  len = sizeof(client_addr);

  if((connSock = accept(listenSock, (struct sockaddr *)&client_addr, &len)) < 0) {
    printf("talk server failed in accepting\n");
    return -1;
  } 
   
  printf("talk server accept new request\n");

  if((pid = fork()) < 0) {
    printf("fork error\n");
    return -1;
  }

  else if(pid > 0) {
    do_keyboard(connSock);
  }
  else if(pid == 0) {
    do_socket(connSock);
  }
  
  close(listenSock);
  close(connSock);
}

void do_keyboard(int connSock) {

  int n;
  char sbuf[BUFSIZ];
  while((n = read(0, sbuf, BUFSIZ)) > 0) {
    if(write(connSock, sbuf, n) != n) {
      printf("talk serer fail in sending\n");
   }
    if(strncmp(sbuf, quit, 4) == 0){
      kill(pid, SIGQUIT);
      break;
    }  
  } 
}

void do_socket(int connSock) {

  int n;
  char rbuf[BUFSIZ];
  
  while(1) {
    if((n = read(connSock, rbuf, BUFSIZ)) > 0) {
      rbuf[n] = '\0';
      printf("%s", rbuf);

      if(strncmp(rbuf, quit, 4) == 0) { 
        kill(getppid(), SIGQUIT);
        break; 
      }

    }
  }
}

