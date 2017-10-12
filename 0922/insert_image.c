#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <string.h>

#define HOST "localhost"
#define USER "root"
#define PASSWD "passwd"
#define DB_NAME "testdb"


void finish_with_error(MYSQL *con);


int main(int argc, char *argv[]) {

  FILE *fp = fopen("123.jpg", "wb");
  MYSQL *con = mysql_init(NULL);
  MYSQL_RES *result;


  if(fp == NULL) {
    fprintf(stderr, "cannot open image file\n");
    exit(1);
  }
  
  if(con == NULL) {
    fprintf(stderr, "mysql_init() failed\n");
    exit(1);
  }

  if(mysql_real_connect(con, HOST, USER, PASSWD, DB_NAME, 0, NULL, 0) == NULL ) {
    finish_with_error(con);
  }

  if(mysql_query(con, "SELECT Data FROM Images WHERE Id = 1")) {
    finish_with_error(con);
  }

 
  result = mysql_store_result;

  if(result == NULL) {
    finish_with_error(con);
  }

  fwrite(row[0], lengths[0], 1, fp);

  if(ferror(fp)) {
    fpritnf(stderr, "fwrite() failed\n");
    mysql_free_result(result);
    mysql_close(con);

    exit(-1);
  }

  if(r == EOF) {
    fprintf(stderr, "cannot close file handler\n");
  }

  mysql_free_result(result);

  mysql_close(con);

  return 0;
}
