//commonFunc.h
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <pthread.h>


#define BACKLOG              10
#define ARGC                  2
#define ARGC_CLI              3
#define FILE_MODE          "a+"
#define LOCAL_PATH  "./log.txt"
#define TH_CLNT_MX            5          // thread_client_max


extern void init_except_log(char *err_t, char *msg) {
  
  FILE *fd;
  time_t l_time;
  
  
  if((fd = fopen(LOCAL_PATH, FILE_MODE)) >= 0) {
   
    time(&l_time);


    // %.19s : remove '\n' 
    if(!strcmp(err_t, "ERROR")) {
      fprintf((FILE *)fd, "[%.19s] <ERROR> %s\n", ctime(&l_time), msg);
    }
        
    else if(!strcmp(err_t, "WARNING")) {
      fprintf((FILE *)fd, "[%.19s] <WARNING> %s\n", ctime(&l_time), msg);
    }

    else
      fprintf((FILE *)fd, "[%.19s] <UNKNOWN> %s\n", ctime(&l_time), msg);
  }

  else
    printf("<ERROR> Can't read file. Exit...\n");

  //exit(-1);
}


extern void *th_clnt_main(void *c_sock) {

  printf("thread\n");

}


