#ifndef COMMONFUNC_H_
#define COMMONFUNC_H_ 
#endif  

int sock_thread(char *argv) {

  int serv_sock, clnt_sock;
  struct sockaddr_in serv_addr, clnt_addr;
  int addr_len; 
 
  pthread_t th_clnt;
  void *tmp;

  if((serv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
    init_except_log("ERROR", "Can't Create Socket."); 
  }

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(atoi(argv));

  if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
    init_except_log("ERROR", "Can't Bind Socket."); 
  }
 
  if(listen(serv_sock, BACKLOG) == -1) {
    init_except_log("ERROR", "Can't Listen Socket."); 
  }

  while(1) {

    addr_len = sizeof(clnt_addr);

    if((clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr, &addr_len)) != -1) {
      pthread_create(&th_clnt, NULL, th_clnt_main, (void *)clnt_sock);
      return 1;
    }
 
    else {
      init_except_log("ERROR", "Cant' Accept Client.");       
      //break;
    }
  }

  close(serv_sock); 
}


