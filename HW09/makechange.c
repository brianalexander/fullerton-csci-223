#include <stdio.h>
#include <stdlib.h>

void MakeChange(int *dollars, 
                int *halfDollars, 
                int *quarters, 
                int *dimes, 
                int *nickels, 
                int *pennies); 
char Pluralize(int amount);

int main(void) {
  auto int dollars, 
          halfDollars, 
          quarters, 
          dimes, 
          nickels, 
          pennies;
  auto int result;

  // Get user input
  printf("enter number of pennies: ");
  result = scanf("%d", &pennies);
  if( result == EOF || result == 0 || pennies < 0) {
    printf("Please enter a non-negative integer...\n");
    exit(1);
  }

  // Convert pennies
  MakeChange(&dollars, 
            &halfDollars,
            &quarters,
            &dimes,
            &nickels,
            &pennies);

  // Print Results
  printf("Here is the currency equivalent:\n");
  printf("\t%d dollar%c\n", dollars, Pluralize(dollars));
  printf("\t%d half dollar%c\n", halfDollars, Pluralize(halfDollars));
  printf("\t%d quarter%c\n", quarters, Pluralize(quarters));
  printf("\t%d dime%c\n", dimes, Pluralize(dimes));
  printf("\t%d nickel%c\n", nickels, Pluralize(nickels));
  printf("\t%d pennie%c\n", pennies, Pluralize(pennies));
}

char Pluralize(int amount) {
  return (amount == 1) ? '\0' : 's';
}


void MakeChange(int *dollars, 
                int *halfDollars, 
                int *quarters, 
                int *dimes, 
                int *nickels, 
                int *pennies) {
  *dollars = *pennies / 100; // get num dollars
  *pennies = *pennies % 100; // calc remaining pennies

  *halfDollars = *pennies / 50;
  *pennies = *pennies % 50;

  *quarters = *pennies / 25;
  *pennies = *pennies % 25;

  *dimes = *pennies / 10;
  *pennies = *pennies % 10;

  *nickels = *pennies / 5;
  *pennies = *pennies % 5;
}