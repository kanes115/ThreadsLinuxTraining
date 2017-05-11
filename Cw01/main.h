#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <fcntl.h>

#include <pthread.h>

int TEXT_MAXSIZE = 255;

#define BLOCK_SIZE 1024
#define BLOCK_TEXT_SIZE 1020


struct block{
  int id;
  char text[BLOCK_TEXT_SIZE];
};
