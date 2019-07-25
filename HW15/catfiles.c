#include <stdio.h>
#include <stdlib.h>

void checkFileWasOpenedOrError(FILE* fileToCheck, char* fileName);

int main(int argc, char* argv[]) {
  auto FILE* inFile;
  auto FILE* outFile;
  auto char charVal;

  if(argc < 3) {
    printf("Usage: %s <output filename> [filename1 filename2 filename3...]\n",
                  argv[0]);
    exit(EXIT_FAILURE);
  }

  inFile = fopen(argv[1], "w");
  checkFileWasOpenedOrError(inFile, argv[1]);

  for(int i = 2; i < argc; i++) {
    outFile = fopen(argv[i], "r");
    checkFileWasOpenedOrError(outFile, argv[i]);

    while(EOF != (charVal = fgetc(outFile))) {
      fputc(charVal, inFile);
    }

    fclose(outFile);
  } 

  fclose(inFile);
}

void checkFileWasOpenedOrError(FILE* fileToCheck, char* fileName) {
  if(fileToCheck == NULL) {
    printf("Failed to open %s for reading...\n", fileName);
    exit(EXIT_FAILURE);
  }
}
