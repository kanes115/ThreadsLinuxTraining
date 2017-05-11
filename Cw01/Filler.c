#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#define panTLen 600

int main(int argc, char* argv[]){
  srand(time(NULL));
  int N=atoi(argv[1]), M=1024,i,j;
  const int lettersNo='z'-'a'+'Z'-'A'+4;
	char letters[lettersNo];

	for(i=0;i<lettersNo/2-1;i++)
		letters[i]='a'+i;
	for(j=0;i<lettersNo-2;i++,j++)
		letters[i]='A'+j;
  //letters[j++]=' ';
  letters[j]='a';//'\n';


  char tmp[M-sizeof(int)];
  //FILE* panT = fopen("pantadeusz.txt", "r");

  for(i=0;i<N;i++){
    FILE* binaryfiledes=fopen("records.txt","ab");
    int c=i+1;
    fwrite(&c,1,sizeof(int),binaryfiledes);
    fclose(binaryfiledes);
    int filedes=open("records.txt",O_WRONLY | O_APPEND);
    //fseek(panT, rand()%panTLen, SEEK_SET);
    for(j=0;j<M-1-sizeof(int);j++){
      tmp[j]=letters[rand()%lettersNo];
    }
    tmp[j]='\0';
    write(filedes,tmp,M-sizeof(int));
    close(filedes);
  }
}
