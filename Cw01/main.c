#include "main.h"

//Globals
int filedes, readRecords;
char* searched;
//---

//PARSER
int onlyDigits(const char* s){
  int i;
  for(i=0;s[i]!='\0' && s[i]!=' ' && s[i]!='\n';i++){
    if(s[i]<'0' || s[i]>'9')return 0;
  }
  return 1;
}

void parse(int argc, char *argv[], int* threads, char* filename, int* readRecords, char* searched, int* version){
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
  *readRecords = atoi(argv[3]);
  strcpy(filename, argv[2]);
  strcpy(searched, argv[4]);
  *version = atoi(argv[5]);
}

void printWordDec(char* word){
  int i = 0;
  while(word[i] != '\0'){
    printf("%d:", (char) word[i]);
    i++;
  }
  printf("%d\n", '\0');
}

void errorLog(char* msg){
  fprintf(stderr, "Error appeared: %s\n", msg);
  perror(msg);
  exit(-1);
}
//---

int isWordHere(char buf[BLOCK_TEXT_SIZE + 1]){
  for(int i = 0; i < BLOCK_TEXT_SIZE + 1 && buf[i] != '\0'; i++){
    int j = i;
    int s_ind = 0;
    while(buf[j] == searched[s_ind] && buf[j]){
      j++;
      s_ind++;
      if(j > i && searched[s_ind] == '\0' && (buf[j] == ' ' || buf[j] == '\0'))
        return 1;
    }
  }
  return 0;
}

void* findWord(void* unused){
  printf("Startuje wątek\n");
  char buf[BLOCK_SIZE];
  char text[BLOCK_TEXT_SIZE + 1];
  for(int i = 0; i < readRecords; i++){
    int read_res;
    if( (read_res = read(filedes, buf, BLOCK_SIZE)) < 0)
      errorLog("findWord");
    if(read_res == 0)
      return NULL;

    printWordDec(buf);
    char* buf_ptr = buf;
    int block_id = (int) (buf_ptr);
    buf_ptr += 4;
    strcpy(text, buf_ptr);
    text[BLOCK_TEXT_SIZE] = '\n';
    if(isWordHere(text)){
      printf("my id: %ld, id of block: %d\n", (long) pthread_self(), block_id);
    }
  }
}




int main(int argc, char *argv[]) {
  //Parsing
  int threads;
  char* filename = (char*) malloc(TEXT_MAXSIZE * sizeof(char));
  searched = (char*) malloc(TEXT_MAXSIZE * sizeof(char));
  int version;
  parse(argc, argv, &threads, filename, &readRecords, searched, &version);
  //main program

  //opening destination file
  filedes = open(filename, O_RDONLY);
  if(filedes == -1)
  errorLog("while opening file");

  //running threads
  pthread_t p_id;
  for(int i = 0; i < threads; i++){
    pthread_create(&p_id, NULL, &findWord, NULL);
  }

  close(filedes);


  return 0;
}
