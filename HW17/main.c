// ============================================================================
// File: main.c (Spring 2019)
// ============================================================================
// This is the main module for the "AllocArray" macro assignment. This file 
// just exercises calls to the macros.
// 
// Output:
//      array[0] = 77           <-- dynamic array of ints
//      array[1] = 77
//      array[2] = 77
//      array[3] = 77
//      array[4] = 77
//      array[0] = R            <-- dynamic array of chars
//      array[1] = R
//      array[2] = R
//      array[3] = R
//      array[4] = R
//      array[0] = 34.290000    <-- dynamic array of doubles
//      array[1] = 34.290000
//      array[2] = 34.290000
//      array[3] = 34.290000
//      array[4] = 34.290000
// 
// ============================================================================

#include    <stdio.h>
#include    <stdlib.h>
#include    "alloc_array.h"


#define NUMELEMS        5


// ==== main ==================================================================
// 
// ============================================================================

int     main(void)
{
    auto    char        *charPtr;
    auto    double      *doublePtr;
    auto    int         *intPtr;
    
    // allocate the array of ints
    intPtr = AllocArray(int, NUMELEMS);
    if (NULL == intPtr)
        {
        puts("Sorry, unable to allocate the array...");
        exit(EXIT_FAILURE);
        }
    else
        {
        // initialize, display and free the array
        InitArray(int, intPtr, NUMELEMS, 77);
        DispArray(int, intPtr, NUMELEMS);
        free(intPtr);
        }

    // allocate the array of chars
    charPtr = AllocArray(char, NUMELEMS);
    if (NULL == charPtr)
        {
        puts("Sorry, unable to allocate the array...");
        exit(EXIT_FAILURE);
        }
    else
        {
        // initialize, display and free the array
        InitArray(char, charPtr, NUMELEMS, 'R');
        DispArray(char, charPtr, NUMELEMS);
        free(charPtr);
        }

    // allocate the array of doubles
    doublePtr = AllocArray(double, NUMELEMS);
    if (NULL == doublePtr)
        {
        puts("Sorry, unable to allocate the array...");
        exit(EXIT_FAILURE);
        }
    else
        {
        // initialize, display and free the array
        InitArray(double, doublePtr, NUMELEMS, 34.29);
        DispArray(double, doublePtr, NUMELEMS);
        free(doublePtr);
        }

    return  0;

}  // end of "main"
