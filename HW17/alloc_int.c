#include    <stdio.h>
#include    <stdlib.h>
#include    "alloc_int.h"

int*   Alloc_intArray(int  numElems) {
  return malloc(sizeof(int) * numElems);
};

void    Init_intArray(int  *ptr, int  numElems, int  initVal) {
  for(int i = 0; i < numElems; i++) {
    ptr[i] = initVal;
  }
};

void    Disp_intArray(int  *ptr, int  numElems) {
  for(int i = 0; i < numElems; i++) {
    printf("Array[%d] = %d\n", i, ptr[i]);
  }
};