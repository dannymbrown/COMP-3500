/**
@file   simple.c

@author Danny Brown (dmb0057)
@version 08-31-2016 00:07

@section DESCRIPTION

Prints the square roots of a predefined array of integers.

Limited outside resources were used and are documented where relevant as line
comments.

*/

#include <stdio.h>
#include <math.h>

int main() {
  int numbers[10] = {1, 4, 9, 16, 25, 36, 49, 64, 81, 100};
  int squared_int = 0;
  int index = 0;
  for (index; index < 10; index++) {
    squared_int = sqrt(numbers[index]);
    printf("%d\n", squared_int);
  }
  return 0;
}
