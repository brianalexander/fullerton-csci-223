#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
  if(argc != 2) {
    puts("Usage: cb <number> [h]");
    exit(EXIT_SUCCESS);
  }

  int stringLength;
  int inputVal;
  
  // get the length of users input
  stringLength = strlen(argv[1]);

  if(argv[1][stringLength-1] == 'h') { // if inputVal ends in 'h'
    argv[1][stringLength-1] = 0; // remove h from the end of the number 
    sscanf(argv[1], "%x", &inputVal); // convert string to hex-int
    printf("%d\n", inputVal); // display value as decimal
  } else { //if inputVal ends in anything except 'h'
    for(int i = 0; i < stringLength; i++) { 
      if(!isdigit(argv[1][i])) { // if any of chars aren't numbers, display error and exit
        puts("Invalid input...");
        exit(EXIT_FAILURE);
      }
    }
    // we haven't exited, so they're all numbers
    sscanf(argv[1], "%d", &inputVal); // convert string to decimal-int
    printf("%Xh\n", inputVal); // display inputVal as hex
  }
}
