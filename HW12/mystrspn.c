#include <stdio.h>

int mystrspn(const char* str, const char* accept); 

typedef enum { false, true } bool;

int main(void) {
  printf("%d\n", mystrspn("abcxyz", "abc")); // returns 3
  printf("%d\n", mystrspn("abcxyz", "xyz")); //  returns 0
  printf("%d\n", mystrspn("abcxyz", "baa")); //  returns 2
  printf("%d\n", mystrspn("xyz", "xyzabc")); //  returns 3
  printf("%d\n", mystrspn("xyz", "abcxyz")); //  returns 3 
}

int mystrspn(const char* str, const char* accept) {
  int count = 0;
  bool matched;

  for(int i = 0; str[i] != '\0'; i++) {
    matched = false;

    // Loop over each of the characters
    // in str
    for(int j = 0; accept[j] != '\0'; j++) {

      // compare character at index i
      // to character j in the acceptable
      // character array
      if(str[i] == accept[j]) {
        // If they are a match, set matched flag to true
        // increase count by 1
        matched = true;
        count++;
      }

      // Break if a character is found to be a match
      if(matched) {
        break;
      }
    }

    // If character was not matched, the prefix count is finished.
    // break out of  loop
    if(!matched) {
      break;
    }
  }

  return count;
}