/*
 * This program replaces tabs with the specified amount of spaces
 */
#include <stdio.h>
#include <stdlib.h>

#define TABSTOP 2

/* Returns an amount of spaces according to tabstop */
char *generate_tabstop(int tabstop);


int main(void)
{
  int c;
  char *spaces;

  while ((c = getchar()) != EOF)
    if (c == '\t') {
      spaces = generate_tabstop(TABSTOP);
      printf("%s", spaces);
      free(spaces);
    }
    else
      putchar(c);

  return EXIT_SUCCESS;
}


char *generate_tabstop(int tabstop)
{
  /* Extra byte for the null terminator */
  char *spaces = calloc(tabstop + 1, sizeof(char));
  int i;

  for (i = 0; i < tabstop; ++i)
    spaces[i] = ' ';
  spaces[i] = '\0';
  return spaces;
}
