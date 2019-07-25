// ============================================================================
// File: alloc_array.h (Spring 2019)
// ============================================================================

#ifndef ALLOC_ARRAY_H
#define ALLOC_ARRAY_H

// #include files
#include    "alloc_int.h"
#include    "alloc_char.h"
#include    "alloc_double.h"

// macros (use token-pasting operator to map function calls here...)
#define AllocArray(type, numElems) Alloc_##type##Array(numElems)
#define InitArray(type, baseAddr, numElems, value) Init_##type##Array(baseAddr, numElems, value)
#define DispArray(type, baseAddr, numElems) Disp_##type##Array(baseAddr, numElems)

#endif  // ALLOC_ARRAY_H
