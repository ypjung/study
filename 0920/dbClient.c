//dbClient_thread.c

#include "commonFunc.h"


int main(int argc, char *argv[]) {

  int serv_sock;
  int conn;
  struct sockaddr_in serv_addr;
  

  if(argc < ARGC_CLI) {
    printf("Usage: ./[File_Name] [Server_IP] [Server_Port]\n");
    exit(-1);
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(atoi(argv[2]));

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_addr.s_addr = inet_addr(haddr);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);i

  if(serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP) == -1) {
    init_except_log("ERROR", "Socket error");
  }

  if(connect(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    init_except_log("ERROR", "connect error");
  }




  return 0;
}
