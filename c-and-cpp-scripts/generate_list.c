/*
 * This program generates a nice-looking list using the lines from stdin
 */
#include <stdio.h>

/* get_padding: returns an amount of space for padding for the list items */
int get_padding();

/* reset_stdin: resets the cursor in stdin to 0 */
void reset_stdin();

/* count_lines: returns an amount of the lines in stdin */
int count_lines();


int main(int argc, char **argv)
{
  /* Current character, number of the list, amount of lines and padding */
  char c;
  int n, nl, pad;

  /* Get the line amount & padding for proper formatting */
  nl = count_lines();
  pad = get_padding();

  /* Print the first number */
  printf("%*d. ", pad, 1);

  /* Main processing loop */
  n = 2;
  while ((c = getchar()) != EOF)
    /* Do not print the number on the last line */
    if (c == '\n' && n <= nl) {
      printf("\n%*d. ", pad, n);
      ++n;
    } else {
      putchar(c);
    }

  return 0;
}

int get_padding()
{
  char c;
  int nl, pad;
  reset_stdin();

  /* Get the lines count */
  nl = count_lines();

  /* Calculate the padding */
  pad = 0;
  while (nl > 0) {
    ++pad;
    nl /= 10;
  }

  reset_stdin();
  return pad;
}

void reset_stdin()
{
  fseek(stdin, 0, SEEK_SET);
}

int count_lines()
{
  char c;
  int nl;
  reset_stdin();

  /* Count the lines */
  nl = 0;
  while ((c = getchar()) != EOF)
    if (c == '\n')
      ++nl;

  reset_stdin();
  return nl;
}
