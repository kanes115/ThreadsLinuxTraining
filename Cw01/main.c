#include "main.h"

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
  strcpy(filename, argv[4]);
  *version = atoi(argv[5]);
}
//---------------------------



int main(int argc, char *argv[]) {
  //Parsing
  int threads, readRecords;
  char* filename = (char*) malloc(TEXT_MAXSIZE * sizeof(char));
  char* searched = (char*) malloc(TEXT_MAXSIZE * sizeof(char));
  int version;
  parse(argc, argv, &threads, filename, &readRecords, searched, &version);
  //main program

  FILE* file = fopen(filename, "a+");
  struct block b;
  b.id = 104;
  b.text = "To jest tekst";
  fwrite(&b, sizeof(b), 1, file);




  return 0;
}
