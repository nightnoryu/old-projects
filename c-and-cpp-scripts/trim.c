/*
 * This program removes all trailing spaces from the lines in stdin
 */
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

/* trim: removes trailing blanks and tabs returns the length of the resulting string */
int trim(char s[]);


int main(void)
{
  char line[MAXLINE];

  while (gets(line) != NULL) {
    trim(line);
    puts(line);
  }
  return 0;
}


int trim(char s[])
{
  int i;

  for (i = strlen(s) - 1; i >= 0; --i)
    if (s[i] != ' ' && s[i] != '\t')
      break;
  s[i+1] = '\0';
  return i;
}
