#include <stdio.h>
#include "./disphex.h"
#include "./dispoct.h"

int main(void) {
  auto int userInput;
  auto int scanfResult;
  printf("Please enter a base ten integer: ");
  scanfResult = scanf("%d", &userInput);
  if (scanfResult == EOF) {
    puts("\nEnd of file reached..");
    return 1;
  } else if (scanfResult == 0) {
    puts("That's not a base ten integer..");
    return 1;
  }

  DispOct(userInput);
  DispHex(userInput);
  return 0;
}