/*
 * This program encodes the text with Caesar's cipher
 */
#include <stdio.h>
#include <stdlib.h>

/* Returns encoded character, using case_letter as the base */
char encode(char c, char case_letter, int key);


int main(int argc, char **argv)
{
  /* Check the input arguments */
  if (argc != 2) {
    printf("USAGE: %s [key]", argv[0]);
    return 1;
  }

  /* Get the key and check it */
  int key = atoi(argv[1]);
  key %= 26;
  if (key == 0) {
    printf("Invalid key: it must not be divisible by 26.");
    exit(EXIT_FAILURE);
  }

  /* Main processing loop */
  int c;
  while ((c = getchar()) != EOF) {
    /* Encode the character if it's alphabetical */
    if (c >= 'a' && c <= 'z')
      c = encode(c, 'a', key);
    else if (c >= 'A' && c <= 'Z')
      c = encode(c, 'A', key);

    /* Print the character */
    putchar(c);
  }

  return EXIT_SUCCESS;
}


char encode(char c, char cs, int key)
{
  return (c - cs + key) % 26 + cs;
}
