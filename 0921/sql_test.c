#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>

/*
#define HOST    "localhost"
#define USER    "root"
#define PASSWD  "passwd" 
*/

#define DB_NAME "testdb"

void finish_with_error(MYSQL *conn);


int main(int argc, char *argv[]) {


  MYSQL *conn = mysql_init(NULL);
  int status = 0;

  if(argc < 4) {
    printf("Usage: P_NAME HOST USER PASSWD\n");
    exit(-1);
  }

  if(conn == NULL) {
    fprintf(stderr, "mysql_init() failed\n");
    exit(-1);
  }

  if(mysql_real_connect(conn, argv[1], argv[2], argv[3], DB_NAME, 0, NULL, CLIENT_MULTI_STATEMENTS) == NULL) {
    finish_with_error(conn);
  }
  
  if(mysql_query(conn, "SELECT *FROM Cars WHERE Id=2;")) {
    finish_with_error(conn);
  }


  mysql_close(conn); 

  return 0;
}


void finish_with_error(MYSQL *conn) {

  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(-1);
}
