/*
 * This program encodes and decodes the rot13 cipher
 */
#include <stdio.h>
#include <ctype.h>

int main(void)
{
  char c, start_letter;

  while ((c = getchar()) != EOF) {
    if (isalpha(c)) {
      // Distinguish upper and lower case
      if (isupper(c))
        start_letter = 'A';
      else
        start_letter = 'a';

      if (c >= start_letter + 13)
        c -= 13;
      else
        c += 13;
    }
    putchar(c);
  }

  return 0;
}
