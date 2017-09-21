#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int ncount;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *do_sum1(void *data);
void *do_sum2(void *data);


int main(int argc, char *argv[]) {

  int thr_id;
  pthread_t p_thread[2];
  int status;
  
  int a;

  ncount = 1;

  a = 9;
  thr_id = pthread_create(&p_thread[0], NULL, do_sum1, (void *)&a);
  sleep(1);

  a = 10;
  thr_id = pthread_create(&p_thread[1], NULL, do_sum2, (void *)&a); 
  
  pthread_join(p_thread[0], (void **)&status);
  pthread_join(p_thread[1], (void **)&status);

  status = pthread_mutex_destroy(&mutex);
  printf("programing is end\n");
 
  return 0;
}


void *do_sum1(void *data) {
  
  int i;
  int n = *((int *)data);
  
  for(i = 0; i < n; i++) {
    printf("sum1 : %d\n", ncount);

    pthread_mutex_lock(&mutex);
    ncount ++;
    pthread_mutex_unlock(&mutex);
    sleep(1);
  } 
}

void *do_sum2(void *data) {

  int i;
  int n = *((int *)data);

  for(i=0; i < n; i++) {
    printf("sum2 : %d]n", ncount);
   
    pthread_mutex_lock(&mutex);
    ncount ++;
    pthread_mutex_unlock(&mutex);
    sleep(1); 
  }
}
