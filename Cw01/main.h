#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <pthread.h>

int TEXT_MAXSIZE = 255;


struct block{
  int id;
  char text[10];
};
