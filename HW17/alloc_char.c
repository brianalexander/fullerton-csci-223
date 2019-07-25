#include    <stdio.h>
#include    <stdlib.h>
#include    "alloc_char.h"

char*   Alloc_charArray(int  numElems) {
  return malloc(sizeof(char) * numElems);
};

void    Init_charArray(char  *ptr, int  numElems, char  initVal) {
  for(int i = 0; i < numElems; i++) {
    ptr[i] = initVal;
  }
};

void    Disp_charArray(char  *ptr, int  numElems) {
  for(int i = 0; i < numElems; i++) {
    printf("Array[%d] = %c\n", i, ptr[i]);
  }
};