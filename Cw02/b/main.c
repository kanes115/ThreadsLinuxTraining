#include "main.h"
#include <signal.h>
//Globals
int threads = 5;
pthread_t *threadIDs;
//---

//PARSER
void errorLog(char* msg){
  fprintf(stderr, "Error appeared: %s\n", msg);
  perror(msg);
  exit(-1);
}
//---

void* makeZeroDiv(void* unused){

  sleep(3);
  int a = 9 / 0;
  (void) a;
  sleep(3);

  pthread_exit(NULL);
  return NULL;
}

void* noZeroDiv(void* unused){

  sleep(6);
  pthread_exit(NULL);
  return NULL;
}

void signalHandler(int signum){
  printf("Signal %d came (Dividing by zero). PID: %d, TID: %ld\n", signum, getpid(), pthread_self());
}


int main(int argc, char *argv[]) {
  //main program
  signal(SIGFPE, signalHandler);

  //running threads
  threadIDs = malloc(threads * sizeof(pthread_t));
  for(int i = 0; i < threads - 1; i++){
    if(pthread_create(&(threadIDs[i]), NULL, &noZeroDiv, NULL) != 0)
      errorLog("while creating thread");
  }
  if(pthread_create(&(threadIDs[threads - 1]), NULL, &makeZeroDiv, NULL) != 0)
    errorLog("while creating thread");

  for(int i=0; i < threads; i++)
    pthread_join(threadIDs[i], NULL);


  return 0;
}
