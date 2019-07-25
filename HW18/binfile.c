// ============================================================================
// File: binfile.c (Spring 2019)
// ============================================================================
// This program reads a binary file of records containing phone numbers and
// corresponding room numbers. It derives the number of records contained in
// the binary file and allocates an array of structures of that size. Then it
// opens the binary file and reads all the data into the dynamic array with a 
// single call to "fread". Once the data has been read, the user is prompted 
// for a filename, which is used to create a text file, and the records are 
// written to the output file formatted for human consumption.
// ============================================================================

#include    <ctype.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>


// defined constants
#define BUFLEN          256
#define DAT_FNAME       "records.dat"


// structure declarations
typedef struct  PhoneRoom
{
    int         phone;
    int         room;

} PhoneRoom;



// function prototypes
void    WriteRecs(const PhoneRoom  recs[], int  numRecs, FILE*  fPtr);


// ==== main ==================================================================
// 
// ============================================================================

int     main(void)
{

    // open the input file that contains the binary records
    auto FILE *binaryRecords;
    binaryRecords = fopen("records.dat", "a+");

    // calculate the number of records stored in the file and display the total
    // to stdout
    auto int numOfRecords = 0;
    auto int numOfBytes = 0;
    // move to end of file
    fseek(binaryRecords, 0, SEEK_END); 
    // numOfRecords = total num of bytes / size of a PhoneRoom object
    numOfBytes = ftell(binaryRecords);
    numOfRecords = numOfBytes / sizeof(PhoneRoom);
    printf("There is a total of %d  records in the \"records.dat\" file...\n", numOfRecords);


    // allocate an array of records large enough to hold all of the data
    auto PhoneRoom *PRArray = malloc(numOfBytes);

    // read all the file records into the allocated buffer
    fseek(binaryRecords, 0, SEEK_SET);
    fread(PRArray, sizeof(PhoneRoom), numOfRecords, binaryRecords);


    // get the name of the output file from the user and open it
    char fileName[BUFLEN];
    printf("Enter the name of the output file: ");
    scanf("%s", fileName);
    auto FILE *outputFile;
    outputFile = fopen(fileName, "w");

    // call WriteRecs to write out the records in formatted text
    WriteRecs(PRArray, numOfRecords, outputFile);

    // close the files and release allocated memory
    printf("%d records written to %s\n", numOfRecords, fileName);
    fclose(outputFile);
    fclose(binaryRecords);
    free(PRArray);

    return 0;

}  // end of "main"



// ==== WriteRecs =============================================================
// 
// This function writes the contents of the PhoneNum array to the output stream
// pointed to by the fPtr parameter. The binary data is formatted for human 
// eyes as the records are written to the output stream. The total number of
// records written is returned to the caller.
// 
// Input:
//      recs        -- the base address of an array of PhoneNum records
// 
//      numRecs     -- the number of elements in the array
// 
//      fPtr        -- a pointer to the output stream to which the records
//                     are written
// 
// Output:
//      Nothing.
// 
// ============================================================================

void    WriteRecs(const PhoneRoom  recs[], int  numRecs, FILE*  fPtr)
{
    for(int i = 0; i < numRecs; i++) {
        auto int first3 = recs[i].phone / 10000;
        auto int last4 = recs[i].phone % 10000;
        fprintf(fPtr, "Phone: %d-%d  Room#: %d\n", first3, last4, recs[i].room);
    }
}  // end of "WriteRecs"
