#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>

void finish_with_error(MYSQL *con);

int main(int argc, char *argv[]) {
 
  MYSQL *con = mysql_init(NULL);
  char *strBuf[BUFSIZ];

/*
  if(argc < 4) {
    printf("Usage: s d s d"); 
    exit(-1);
  }
*/
  if(con == NULL) {
    fprintf(stderr, "%s\n", mysql_error);
    exit(-1);
  } 

  if(sprintf(strBuf, "CREATE TABLE %s VALUES(%d, %s, %d)", 
             argv[1], atoi(argv[2]), argv[3], atoi(argv[4]))) {
    printf("%s\n", strBuf);
  }

  if(mysql_real_connect(con,"localhost", "root", "root_passwd", 0, NULL, 0) == NULL){
    finish_with_error(con);
  }
 
  if(mysql_query(con, "DROP TABLE IF EXISTS Cars")) {
    finish_with_error(con);
  }

  if(mysql_query(con, "CREATE TABLE Cars(Id INT, Name TEXT, Price INT")) {
    finish_with_error(con);
  }

  if(mysql_query(con, "INSERT INTO Cars VALUES(3, 'Skoda', 9000)")) {
    finish_with_error(con);
  }

  if(mysql_query(con, "INSERT INTO Cars VALUES(10, 'Audi', 21000)")) {
    finish_with_error(con);
  }

}

void finish_with_error(MYSQL *con) {

  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
} 
