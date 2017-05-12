#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <pthread.h>

int TEXT_MAXSIZE = 255;

#define BLOCK_SIZE 1024
#define BLOCK_TEXT_SIZE (BLOCK_SIZE - sizeof(int))

void printWordDec(char* word);
