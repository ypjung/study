#include <stdio.h>
#include <my_global.h>
#include <mysql.h>

int main(int argc, char *argv[]) {

  printf("MySQL client version: %s\n", mysql_get_client_inf());

  return 0;
  
}
