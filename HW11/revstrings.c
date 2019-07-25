#include <stdio.h>
#include <stdlib.h>

#define MAX_STRINGS 100
#define MAX_CHARS 250
#define TRUE 1

int main(void) {
  auto int i = 0; 
  char* arr[MAX_STRINGS];

  while(i < MAX_STRINGS) {
    // create char
    char* buf = malloc(MAX_CHARS*sizeof(char));

    // get user input using fgets
    arr[i] = fgets(buf, MAX_CHARS, stdin);

    // exit if only newline
    if(*buf == '\n') {
      break;
    }
    // increment i
    // increment after break to avoid adding the \n to char* array
    i++;
  }

  // adjust i for off-by-one
  i--;

  while(i >=0) {
    // display
    if( arr[i] != NULL) {
      printf("%s", arr[i]);
    }

    // deallocate memory
    free(arr[i]);

    // decrement i
    i--;
  }
}