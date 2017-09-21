#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <dirent.h>
#include <string.h>


#define PORT 9000
#define BACKLOG 5


char err_1[] = "Directory Error";
char rBuffer[BUFSIZ];

int main() {

  int c_socket, s_socket;
  struct sockaddr_in s_addr, c_addr;
  int len, length;
  int n, i;
  char *temp;

  DIR *dp;
  struct dirent *dir;
  
  s_socket = socket(PF_INET, SOCK_STREAM, 0);
  
  memset(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  s_addr.sin_family = AF_INET;
  s_addr.sin_port = htons(PORT);

  if(bind(s_socket, (struct sockaddr *)&s_addr, sizeof(s_addr)) == -1 ) {
    printf("!bind()\n");
    close(s_socket);
    return 0;    
  }
 
  if(listen(s_socket, 5) == -1) {
    printf("!listen()\n");
    close(s_socket);
    return 0;
  }

  while(1) {
    len = sizeof(c_addr);
    c_socket = accept(s_socket, (struct sockaddr*)&c_addr, &len);
    
    length = 0;
    temp = rBuffer;
    while((n = read(c_socket, temp, 1)) > 0) {
      if(*temp == '\r') continue;
      if(*temp == '\0') break;
      if(*temp == '\n') break;
    
      if(length == BUFSIZ) break; 
      temp++; length++;
    }
    rBuffer[length] = '\0';
 
    // read data from accept() 
    if(!strcmp(rBuffer, "ls")) { 
      if((dp = opendir(".")) == NULL) {
          write(c_socket, err_1, strlen(err_1)); 
      } else {
          while((dir = readdir(dp)) != NULL) {
            if(dir->d_ino == 0) continue;

            write(c_socket, dir->d_name, strlen(dir->d_name));
            write(c_socket, " ", 1);
          }        
      closedir(dp);
      }
    
    closedir(dp); 
    }

  }
  close(s_socket);
  return 0;
}
