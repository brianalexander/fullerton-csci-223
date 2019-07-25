// ============================================================================
// File: matching_bytes.c (Spring 2019)
// ============================================================================
// This is a small exercise dealing with void pointers. Arrays are allocated
// off the stack so that they contain random values. Then their contents are
// displayed to stdout as individual bytes. The user is then prompted for a 
// target search byte, and the number of matching bytes for an array is 
// displayed.
// ============================================================================

#include    <stdio.h>
#include    <stdint.h>
#include    <stdlib.h>

// defined constants
#define MAX_WIDTH       20
#define NUMELEMS        50

// type definitions
typedef	unsigned char	Byte;

// function prototypes
void DispBytes (void* arr, int numBytes);
int CountMatchBytes (void* arr, int numBytes, Byte targ);


// ==== main ==================================================================
//
// ============================================================================

int     main(void)
{
    auto    double          myDoubles[NUMELEMS];
    auto    int             myInts[NUMELEMS];
    auto    char            myChars[NUMELEMS];
    auto    Byte            target;
    auto    int             numMatches;

    // char array
    puts("Here's the array of chars as bytes: ");
    DispBytes(myChars, sizeof(myChars));
    printf("Enter the target byte as a hex value: ");
    if (1 != scanf("%hhx", &target))
        {
        puts("Error reading hexadecimal value...");
        exit(EXIT_FAILURE);
        }

    numMatches = CountMatchBytes(myChars, sizeof(myChars), target);
    printf("There %s %d matching byte%s.\n\n", (1 == numMatches ? "is" : "are")
                                             , numMatches
                                             , (1 == numMatches ? "" : "s"));
    // int array
    puts("Here's the array of ints as bytes: ");
    DispBytes(myInts, sizeof(myInts));
    printf("Enter the target byte as a hex value: ");
    if (1 != scanf("%hhx", &target))
        {
        puts("Error reading hexadecimal value...");
        exit(EXIT_FAILURE);
        }

    numMatches = CountMatchBytes(myInts, sizeof(myInts), target);
    printf("There %s %d matching byte%s.\n\n", (1 == numMatches ? "is" : "are")
                                             , numMatches
                                             , (1 == numMatches ? "" : "s"));
    // double array
    puts("Here's the array of doubles as bytes: ");
    DispBytes(myDoubles, sizeof(myDoubles));
    printf("Enter the target byte as a hex value: ");
    if (1 != scanf("%hhx", &target))
        {
        puts("Error reading hexadecimal value...");
        exit(EXIT_FAILURE);
        }

    numMatches = CountMatchBytes(myDoubles, sizeof(myDoubles), target);
    printf("There %s %d matching byte%s.\n\n", (1 == numMatches ? "is" : "are")
                                             , numMatches
                                             , (1 == numMatches ? "" : "s"));

    return  0;

}  // end of "main"

void DispBytes (void* arr, int numBytes) {
    Byte* myByte = arr;

    for(int i = 0; i < numBytes; i++) {
        if(i != 0 && i % 20 == 0) {
            puts("");
        }
        printf("%02X ", myByte[i]);
    }
    puts("");

}


int CountMatchBytes (void* arr, int numBytes, Byte targ) {
    int count = 0;
    Byte* myByte = arr;

    for(int i = 0; i < numBytes; i++) {
        if (myByte[i] == targ) {
            count++;
        }
    }
    return count;
}