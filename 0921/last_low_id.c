#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>

#define ID     "root"
#define PASSWD "passwd"


void finish_with_error(MYSQL *con);

int main(int argc, char *argv) {

  MYSQL *con = mysql_init(NULL);

  if(con == NULL) {
    fprintf(stderr, "mysql_init()failed\n");
    exit(1);
  }

  if(mysql_real_connect(con, "localhost", ID, PASSWD, 
                        "testdb", NULL, 0, NULL)) {
    finish_with_error(con);
  }
  
  if(mysql_query(con, "DROP TABLE IF EXISTS Writers")) {
    finish_with_error(con);
  }

  char *sql = "CREATE TABLE Writers(Id INT PRIMARY KEY AUTO_INCREMENT, Name TEXT);

  if(mysql_query(con, sql)) {
    finish_with_error(con);
  }
 
  if(mysql_qury(con, "INSERT INTO Writes(Name) VALUES('Leo Tolstoy')")) {
    finish_with_error(con);
  }
 
  if(mysql_query(con, "INSERT INTO Writes(Name) VALUES('Jack London')")) {
    finish_with_error(con);
  }

  int id = mysql_insert_id(con);

  printf("The last inserted row id is: %d\n", id);

  mysql_close(con);
  return 0;
}
