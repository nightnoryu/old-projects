/*
 * This program calculates the GCD of two numbers
 */
#include <stdio.h>
#include <stdlib.h>

/* Calculates the gcd using Euclidean algorithm */
int get_gcd(int n1, int n2);


int main(int argc, char **argv)
{
  int n1, n2;

  if (argc > 2) {
    /* Get the data through parameters */
    n1 = atoi(argv[1]);
    n2 = atoi(argv[2]);
  } else {
    /* Otherwise, get the data through stdin */
    printf("First number: ");
    scanf("%d", &n1);
    printf("Second number: ");
    scanf("%d", &n2);
  }

  /* Print the result */
  printf("gcd(%d, %d) = %d\n", n1, n2, get_gcd(n1, n2));
  return EXIT_SUCCESS;
}


int get_gcd(int n1, int n2)
{
  while (n1 != n2) {
    if (n1 > n2) {
      n1 -= n2;
    } else {
      n2 -= n1;
    }
  }
  return n1;
}
