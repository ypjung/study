#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>

#define ID      "root"
#define PASSWD  "passwd" 


void finish_with_error(MYSQL *con);

int main(int argc, char *argv[]) {

  MYSQL *conn = mysql_init(NULL);
  int i;


  if(conn = NULL) {
    fprintf(stderr, "mysql_init() failed\n");
    exit(-1);
  }

  if(mysql_real_connect(con, "localhost", ID, PASSWD, "testdb", 0, NULL, 0) == NULL) { 
    finish_with_error(con);
  }

  if(mysql_query(con, "SELECT *FROM Cars")) {
    finish_with_error(con);
  }

  MYSQL_RES *result = mysql_store_result(con);
 
  if(result == NULL) {
    finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  
  while((row = mysql_fetch_row(result))) {
    
    for(i = 0; i < num_fields; i++) {
      printf("%s", row[i]?row[i]:NULL);
    }
      printf("\n");
  }

  mysql_free_reslut(result);
  mysql_close(con);

  return 0;
}


void finish_with_error(MYSQL *con) {
 
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
 
}
