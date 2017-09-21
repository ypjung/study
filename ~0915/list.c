#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>


int main() {

  DIR *dp;
  struct dirent *dir;

  if((dp = opendir(".")) == NULL) {
    fprintf(stderr, "directory open error\n");
    //return 0; 
    exit(0);
  } 	

  while((dir = readdir(dp)) != NULL) {
    if(dir->d_ino == 0) continue;

    printf("%s\n", dir->d_name);
  } 


  closedir(dp);

  return 0;
}
