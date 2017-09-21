#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define PORT 9000


void *do_keyboard(void *);
void *do_socket(void *);

char quit[] = "exit";

pthread_t pid[2];


int main(int argc, char *argv[]) {

  int thr_id;
  int status;

  int listenSock, connSock;
  struct sockaddr_in client_addr, server_addr;

  int len;

  if(argc < 2) { 
    printf("Usage: talk_server port_num \n");
    return(0);
  }  

  if((listenSock = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
    printf("Server: can't open socket\n");
    return -1;
  }

  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[1]));
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if(bind(listenSock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("talk server can't bind\n");
    return -1;
  }

  listen(listenSock, 1);
  len = sizeof(client_addr);
 
  if((connSock = accept(listenSock, (struct sockaddr *)&client_addr, &len)) < 0) {
    printf("Talk server failed in accepting\n");
    return -1;
  }   

  printf("talk server accept new request\n");
  thr_id = pthread_create(&pid[0], NULL, do_keyboard, (void *)connSock);
  thr_id = pthread_create(&pid[1], NULL, do_socket, (void *)connSock);   

  close(listenSock);
  close(connSock);

}


void *do_keyboard(void *data) {

  int n;
  char sbuf[BUFSIZ];
  int connSock = (int)data;
  
  while((n = read(0, sbuf, BUFSIZ)) > 0) {
    if(write(connSock, sbuf, n) != n) {
      printf("talk server fail in sending\n");
    }

    if(strncmp(sbuf, quit, 4) == 0) {
      pthread_kill(pid[1], SIGINT);
      break;
    }
  }
}

void *do_socket(void *data) {

  int n;
  char rbuf[BUFSIZ];
  int connSock = (int)data;
 
  while(1) {
    if((n = read(connSock, rbuf, BUFSIZ)) > 0) {
      rbuf[n] = '\0';
      printf("%s", rbuf);

      if(strncmp(rbuf, quit, 4) > 0) {
        pthread_kill(pid[0], SIGINT);
        break;
      }
    }
  }
}
