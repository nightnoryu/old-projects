/*
 * This program prints a nice pyramid :)
 */
#include <stdio.h>

int main(void)
{
  int rows;
  int offset;

  /* Input the rows count */
  printf("Enter the rows count: ");
  scanf("%d", &rows);

  /* Check the value */
  if (rows < 1) {
    printf("Invalid rows amount. Must be a positive integer");
    return 1;
  }

  /* Draw the pyramid */
  offset = rows - 1;
  /* Rows loop */
  for (int i = rows; i > 0; --i) {
    /* Print the offset */
    for (int k = 0; k < offset; ++k) {
      printf(" ");
    }
    
    /* One row elements loop */
    for (int j = rows; j >= i; --j) {
      printf("* ");
    }
    
    /* Start new row and change the offset */
    printf("\n");
    --offset;
  }

  return 0;
}
