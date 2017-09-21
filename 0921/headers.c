#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>

#define HOST    "localhost"
#define USER    "root"
#define PASSWD  "passwd"
#define DB_NAME "testdb"


void finish_with_error(MYSQL *con);

int main(int argc, char *argv[]) {

  MYSQL *con = mysql_init(NULL);
  int i;

  if(con == NULL) {
    fprintf(stderr, "mysql_init() failed\n");
    exit(1);
  }
  
  if(mysql_real_connect(con, HOST, USER, PASSWD, DB_NAME, NULL, 0, NULL) == NULL) {
    finish_with_error(con);
  }

  if(mysql_query(con, "SELECT *FROM Cars LIMIT 3")) {
    finish_with_error(con);
  }

  MYSQL_RES *result = mysql_store_result(con);
 
  if(result == NULL) {
    finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  MYSQL_FIELD *field;

  while((row = mysql_fetch_row(result))) {
    for(i = 0; i < num_fields; i++) {
      if(i == 0) {
        while(field = mysql_fetch_field(result)) {
          printf("%s ", field->name);
        }
        printf("\n");
      }
      printf("%s ", row[i] ? row[i] : "NULL");
      
    }
  }
  printf("\n");
   
  mysql_free_result(result);
  mysql_close(con); 

  return 0;
}

void finish_with_error(MYSQL *con) {

  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}
