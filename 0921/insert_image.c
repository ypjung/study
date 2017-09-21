#include <stdio.h>
#include <stdlib.h>
#include <my_global.h>
#include <mysql.h>
#include <string.h>


#define HOST   "localhost"
#define USER   "root"
#define PASSWD "passwd"
#define DB_NAME "testdb"


void finish_with_error(MYSQL *conn);
void handler_error(int r);



int main(int argc, char *argv[]) {

  FILE *fp = fopen("test.jpg", "rb");

  int r;
  int flen;

  char data[flen+1];
  int size;
  char chunk[2*size+1];
  char *st;
  size_t st_len;
  char query[st_len +2*size+1];
  int len;


  if(fp == NULL) {
    fprintf(stderr, "cannot open image file\n");
    exit(-1);
  }	  

  fseek(fp, 0, SEEK_END);

  if(ferror(fp)) {
    fprintf(stderr, "seek() failed\n");
   r = fclose(fp);

    handler_error(r); 
    }

    exit(-1);
  }

  flen = ftell(fp);

  if(flen == -1) {
    perror("error occurred");
    r = fclose(fp);

    handler_error(r); 
    }
  
    exit(-1);
  }

  fseek(fp, 0, SEEK_SET);
  
  if(ferror(fp)) {
    fprintf(stderr, "fseek() failed\n"); 
    r = fclose(fp);

    handler_error(r); 
    }

    exit(-1);
  }

  size = fread(data, 1, flen, fp);

  if(ferror(fp)) {
    fprintf(stderr, "fread() failed\n");
    r = fclose(fp);

    handler_error(r);
  }
  
  exit(-1);
  }

  r = flose(fp);

  handler_error(r);


  // MYSQL 
  MYSQL *con = mysql_init(NULL);


  if(con == NULL) {
    fprintf(stderr, "mysql_init() failed\n");
    exit(1);
  }

  if(mysql_real_connect(con, HOST, USER, PASSWD, DB_NAME, 0, NULL, 0) == NULL) {
    finish_with_error(con);
  }

  mysql_real_excape_string(con, chunk, data, size);

  st = "INSERT INTO Images(Id, Data) VALUES(1, '%s')";
  st_len = strlen(st);

  len = snprintf(query, st_len + 2*size+1, st, chunk);

  if(mysql_real_query(con, query, len)) {
    finish_with_error(con);
  }

  mysql_close(con);

  return 0;
}


void finish_with_error(MYSQL *conn) {

  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}


void handler_error(int r) {

    if(r == EOF) {
      fprintf(stderr, "cannot close file handler\n");
    }

}

