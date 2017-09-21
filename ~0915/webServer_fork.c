
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/resource.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/stat.h>

#define CODE200 200
#define CODE404 404

#define PHRASE200 "OK"
#define PHRASE404 "FILE NOT FOUND"

char documentRoot[] = "/usr/iocal/apache/htdocs";

void do_web(int);
void web_log(int, char[], char[], int);

int log_fd;

int main(argc, char*argv[]) {

  struct sockaddr_in s_addr, c_addr;
  int s_sock, c_sock;
  int len, len_out;
  unsigned short port;
  int status;
  struct rlimit resourceLimit;
  int i;

  int pid;

  if(argc != 2) {
    printf("usage: webServer port_number");
    return -1; 
  }
 
  if(fork() != 0)
    return 0;

  (void)signal(SIGCLD, SIG_IGN);
  (void)signal(SIGHUP, SIG_IGN);
 
  resourceLimit.rlim_max = 0;
  status = getrlimit(RLIMIT_NOFILE, &resourceLimit);
  
  for(i = 0; i< resourceLimit.rlim_max; i++) {
    close(i);
  }
 
  web_log(LOG, "STATUS", "web server start", getpid());

  if((s_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
    web_log(ERROR, "SYSCALL", "web server listen socket open error", s_sock);
  }

  port = atoi(argv[1]);
  
  if(port > 600000)
    web_log(ERROR, "ERROR", "invalid port number", port);

  memset(&s_addr, 0, sizeof(s_addr));
  s_addr.sin_family = AF_INET;
  s_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  s_addr.sin_port = htons(port);

  if(bind(s_sock, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0)
    web_log(ERROR, "ERROR", "server cannot bind", 0);

  listen(s_sock, 10);

  while(1) {
    len = sizeof(c_addr);

    if((c_sock = accept(s_sock, (struct sockaddr *)&c_addr, &len)) < 0) 
      web_log(ERROR, "ERROR", "server accept error", 0);
   
    if(pid = fork() < 0) {
      web_log(ERROR, "ERROR", "server fork error", 0);
    }
   
    else if(pid == 0) {
      close(s_sock);
      do_web(c_sock);  
    }

    else 
      close(c_sock);    
  }

}


void do_web(int c_sock) {

  char uri[100], c_type[20];
  int len;

  int len_out;
  int n, i;
  char *p;
  char method[10], f_name[20];
  char phrase[20] = "OK";

  int code = 200;
  int fd;
  
  char file_name[20];
  char ext[20];
  
  struct stat sbuf;

  struct {
      char *ext;
      char *filetype;
  } extensions [] = {
      {"gif", "image/gif"},
      {"jpg", "image/jpg"},
      {"jpeg", "image/jpeg"},
      {"png", "image/png"},
      {"zip", "image/zip"},
      {"gz", "image/gz"},
      {"tar", "image/tar"},
      {"htm", "text/html"},
      {"html", "text/html"},
      {0,0}  };

  
  memset(recvBuf, 0, sizeof(recvBuf));
  
  if((n = read(c_sock, recvBuf, BUFSIZ)) <=0) 
    web_log(ERROR, "ERROR", "can not receive data from web browser", n);

  web_log(LOG, "REQUEST", recvBuf, n);

  p = strtok(recvBuf, " ");
  
  if(strcmp(p, "GET") && strcmp(p, "get"))
    web_log(ERROR, "ERROR", "only get method can supoort", 0);
  
  p = strtok(NULL, " ");

  if(!strcmp(p, "/"))
    sprintf(uri, "%s/index.html", documentRoot);
  
  else
    sprintf(uri, "%s%s", documentRoot, p);

  strcpy(c_type, "text/plain");
 
  for(i=0; extension[i].ext != 0; i++) {
    len = strlen(extensions[i].ext);
    
    if(!strncmp(uri+strlen(uri)-len, extenstions[i].ext, len)) {
      strcpy(c_type, extensions[i].filetype);
      break;
    }
  }

  if((fd = open(uri, O_RDONLY)) < 0) {
    code = CODE404;
    ctrcpy(phrase, PHRASE404);
  }

  p = strtok(NULL, "\r\n ");

  sprintf(sndBuf, "HTTP/1.0 %d %s \r\n", code, phrase);
  n = write(c_sock, sndBuf, strlen(sndBuf));
  web_log(LOG, "RESPONSE", sndBuf, getpid());

  sprintf(




}
