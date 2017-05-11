#include "main.h"

//Globals
int filedes, readRecordsNo, threads;
char* searched;
pthread_t *threadIDs;
//---

//PARSER
int onlyDigits(const char* s){
  int i;
  for(i=0;s[i]!='\0' && s[i]!=' ' && s[i]!='\n';i++){
    if(s[i]<'0' || s[i]>'9')return 0;
  }
  return 1;
}

void parse(int argc, char *argv[], int* threads, char* filename, int* readRecordsNo, char* searched, int* version){
  if(argc != 6){
    fprintf(stderr, "%s\n", "Invalid number of arguments");
    exit(-1);
  }
  if(onlyDigits(argv[1]) == 0 || onlyDigits(argv[3]) == 0){
    fprintf(stderr, "%s\n", "Argument 1 and 3 must be an integer");
    exit(-1);
  }
  if(strcmp(argv[5], "1") != 0 && strcmp(argv[5], "2") != 0 && strcmp(argv[5], "3") != 0){
    fprintf(stderr, "%s\n", "version argument must be either 1 or 2 or 3");
    exit(-1);
  }

  *threads = atoi(argv[1]);
  *readRecordsNo = atoi(argv[3]);
  sprintf(filename,"%s", argv[2]);
  sprintf(searched,"%s", argv[4]);
  *version = atoi(argv[5]);
}

void printWordDec(char* word){
  int i = 0;
  while(word[i] != '\0'){
    printf("%d(%c):", (int) word[i], (char) word[i]);
    i++;
  }
  printf("(%d)\n", '\0');
}

void errorLog(char* msg){
  fprintf(stderr, "Error appeared: %s\n", msg);
  perror(msg);
  exit(-1);
}
//---

void copy(char* dest, char* source, int n){
  for(int i = 0; i < n; i++)
    dest[i] = source[i];
}

int isWordHere(char *buf, int size){
  for(int i = 0; i < size; i++){
    int j = i;
    int s_ind = 0;
    printf("comparing: %c with %c\n", buf[j], searched[s_ind]);
    while(buf[j] == searched[s_ind] && j < size){
      j++;
      s_ind++;
      if(searched[s_ind] == '\0')
        return 1;
    }
  }
  return 0;
}

void* findWord(void* unused){
  int realReadSize = BLOCK_SIZE * readRecordsNo;
  printf("Thread starts...\n");
  /*if(version == 1 || version == 3)*/pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  char buf[realReadSize];
  char text[BLOCK_TEXT_SIZE + 1];
  while(1){
    int read_res;
    if( (read_res = read(filedes, buf, realReadSize)) < 0)
      errorLog("findWord");
    if(read_res == 0)
      return NULL;
    for(int i = 0; i < readRecordsNo; i++){
      char* buf_ptr = buf;
      int block_id = (int) (*buf_ptr);
      buf_ptr += 4;
      copy(text, buf_ptr, BLOCK_TEXT_SIZE);
      buf_ptr += BLOCK_TEXT_SIZE;
      text[BLOCK_TEXT_SIZE] = '\0';
      // printf("buf(%d): \n", block_id);
      // printWordDec(text);
      if(isWordHere(text, BLOCK_TEXT_SIZE + 1)){
        printf("my id: %ld, id of block: %d\n", (long) pthread_self(), block_id);
        for(int j = 0; j < threads; j++){
          pthread_cancel(threadIDs[j]);
        }
        pthread_exit(NULL);
      }
    }
  pthread_exit(NULL);
  return NULL;
  }
}




int main(int argc, char *argv[]) {
  //Parsing
  char* filename = (char*) malloc(TEXT_MAXSIZE * sizeof(char));
  searched = (char*) malloc(TEXT_MAXSIZE * sizeof(char));
  int version;
  parse(argc, argv, &threads, filename, &readRecordsNo, searched, &version);
  //main program

  //opening destination file
  filedes = open(filename, O_RDONLY);
  if(filedes == -1)
    errorLog("while opening file");

  //running threads
  threadIDs = malloc(threads * sizeof(pthread_t));
  for(int i = 0; i < threads; i++){
    if(pthread_create(&(threadIDs[i]), NULL, &findWord, NULL) != 0)
      errorLog("while creating thread");
  }

  for(int i=0; i < threads; i++)
    pthread_join(threadIDs[i], NULL);

  close(filedes);


  return 0;
}
