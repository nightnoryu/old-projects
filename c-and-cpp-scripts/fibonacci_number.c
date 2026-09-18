/*
 * This program prints the fibonacci number of the specified index
 */
#include <stdio.h>
#include <stdlib.h>

/* Fills the fibs with fibonacci numbers according to index */
void generate_fibs(long int *fibs, int index);


int main(int argc, char **argv)
{
  int index;
  
  if (argc > 1) {
    /* Get the index through input parameters */
    index = (int) strtol(argv[1], NULL, 10);
  } else {
    /* Otherwise get the index from stdin */
    printf("Enter the fibonacci number's index: ");
    scanf("%d", &index);
  }

  /* Some common cases */
  if (index <= 0) {
    printf("Invalid index.\n");
    exit(EXIT_FAILURE);
  }
  if (index < 3) {
    printf("1\n");
    exit(EXIT_SUCCESS);
  }

  /* Other *serious* cases */
  long int *fibs = calloc(index, sizeof(long int));
  generate_fibs(fibs, index);

  /* Print the result */
  printf("%d\n", fibs[index-1]);

  /* Gracefully exit */
  free(fibs);
  return EXIT_SUCCESS;
}


void generate_fibs(long int *fibs, int index)
{
  int i;
  fibs[0] = fibs[1] = 1;
  for (i = 2; i < index; ++i) {
    fibs[i] = fibs[i-1] + fibs[i-2];
  }
}
