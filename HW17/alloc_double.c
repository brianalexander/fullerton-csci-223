#include    <stdio.h>
#include    <stdlib.h>
#include    "alloc_double.h"

double*   Alloc_doubleArray(int  numElems) {
  return malloc(sizeof(double) * numElems);
};

void    Init_doubleArray(double  *ptr, int  numElems, double  initVal) {
  for(int i = 0; i < numElems; i++) {
    ptr[i] = initVal;
  }
};

void    Disp_doubleArray(double  *ptr, int  numElems) {
  for(int i = 0; i < numElems; i++) {
    printf("Array[%d] = %f\n", i, ptr[i]);
  }
};