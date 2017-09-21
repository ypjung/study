//dbServer_thread.c

#include "commonFunc.h"
#include "sock_thread.c"

extern void init_except_log(char *err_t, char *msg);
extern void *th_clnt_main(void *c_sock);
extern int sock_thread(char *argv);


int main(int argc, char *argv[]) {

  int sock_ret;

  if(argc < ARGC) {
    printf("Usage: ./[File_Name] [Port_Number]\n");
    exit(-1);
  } 

  if((sock_ret = sock_thread(argv[1])) != 1) {
    init_except_log("ERROR", "(main)Socket Thread error");
    //exit(-1);
  }


 
 
  return 0;
}




