#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

  char *strBuf[BUFSIZ];

  if(argc < 4) {
    printf("Usage: name s d s d\n");
    exit(-1); 
  }

  sprintf(strBuf, "[ID: %s]\n[NO: %d]\n[PASSWD: %s]\n", argv[1], atoi(argv[2]), argv[3]);

  printf("%s\n", strBuf);



  return 0;
}
