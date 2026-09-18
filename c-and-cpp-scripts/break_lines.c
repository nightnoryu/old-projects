/*
 * This program breaks the lines from input that exceed the specified amount
 * of symbols or (if not provided) DEFAULT_LIMIT
 */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE       1000
#define DEFAULT_LIMIT 79

/* Get the line from stdin and return it's length */
int mygetline(char line[], int length);

/* Insert linebreaks if the line exceeds 'limit' characters */
void fixline(char line[], int limit);


int main(int argc, char **argv)
{
  int len, limit;
  char line[MAXLINE];

  /* Check the input arguments */
  if (argc > 1)
    limit = atoi(argv[1]);
  else
    limit = DEFAULT_LIMIT;

  while ((len = mygetline(line, MAXLINE)) > 0) {
    if (len > limit)
      fixline(line, limit);
    printf("%s", line);
  }

  return EXIT_SUCCESS;
}


int mygetline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

void fixline(char s[], int lim)
{
  int i, linec;

  for (i = 0, linec = 1; s[i] != '\0'; ++i, ++linec)
    if (linec > lim && linec % lim < lim && (s[i] == ' ' || s[i] == '\t')) {
      s[i] = '\n';
      linec = 1;
    }
}
