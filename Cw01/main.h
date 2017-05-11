#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <pthread.h>

int TEXT_MAXSIZE = 255;

#define BLOCK_SIZE 1024
#define BLOCK_TEXT_SIZE (BLOCK_SIZE - 4)


struct block{
  int id;
  char text[BLOCK_TEXT_SIZE];
};


void printWordDec(char* word);
