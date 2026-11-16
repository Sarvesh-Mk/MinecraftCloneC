#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io/array.h>
#include <render/shader.h>
#include <types.h>

void initArray(Array *a, size_t initialSize) {
  a->chArray = malloc(initialSize * sizeof(char));
  a->iArray = malloc(initialSize * sizeof(u32));
  a->fArray = malloc(initialSize * sizeof(f32));
  a->used = 0;
  a->size = initialSize;
}


void insertArrayChar(Array *a, char element) {
  // a->used is the number of used entries, because a->chArray[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->chArray = realloc(a->chArray, a->size * sizeof(char));
  }
  a->chArray[a->used++] = element;
}

void insertArrayFloat(Array *a, f32 element){
  if (a->used == a->size) {
    a->size *= 2;
    a->fArray = realloc(a->fArray, a->size * sizeof(f32));
  }
  a->fArray[a->used++] = element;
}

void insertArrayU32(Array *a, u32 element){
  if (a->used == a->size) {
    a->size *= 2;
    a->iArray = realloc(a->iArray, a->size * sizeof(u32));
  }
  a->iArray[a->used++] = element;
}

int findElement(Array *a, u32 Element){
  for(int x=0;x<a->size;x++){
    if(a->iArray[x] == Element){
      return x;
    }
  }
  return -1;
}

void freeArray(Array *a){
  free(a->chArray);
  free(a->fArray);
  free(a->iArray);
  a->chArray = NULL;
  a->iArray = NULL;
  a->fArray = NULL;
  a->used = a->size = 0;
}

void ReadFile(const char *path, Array * a){
    initArray(a, 1);
    FILE * ptr;
    char ch;

    ptr = fopen(path, "r");

    if(ptr == NULL) {printf("file can't be opened \n");}

    while (!feof(ptr)) {
        ch = fgetc(ptr);
        insertArrayChar(a,ch);
    }

}