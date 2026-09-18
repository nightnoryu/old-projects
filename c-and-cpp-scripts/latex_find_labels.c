/*
 * This program finds and prints all labels in a LaTeX file
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1000
#define LABEL_KEYWORD "\\label"

extern int errno;

/* Finds the labels in file & prints them if they were found.
   Returns the amount of labels. */
int find_labels(FILE *fp);

/* Returns contents of the label without anything unnecessary */
char *get_label_text(const char *label);


int main(int argc, char **argv)
{
  /* Check the input arguments */
  if (argc != 2) {
    fprintf(stderr, "USAGE: latex-get-refs [LaTeX file]\n");
    exit(EXIT_FAILURE);
  }

  /* Open the file */
  FILE *fp;
  fp = fopen(argv[1], "r");
  /* Check for errors */
  if (fp == NULL) {
    fprintf(stderr, "An error occurred while opening file %s: %s.\n", argv[1], strerror(errno));
    exit(EXIT_FAILURE);
  }

  /* Find the labels */
  int occurs = find_labels(fp);
  /* Check the amount */
  if (!occurs) {
    printf("No labels were found.\n");
  }

  /* Gracefully exit */
  fclose(fp);
  return EXIT_SUCCESS;
}


int find_labels(FILE *fp)
{
  char str[MAXLINE], label_text[MAXLINE]; /* Current line and label text */
  char *pos;             /* Occurrence position */
  int line, col, occurs; /* Occurrence line, column; overall occurrences amount */
  char *text;            /* Text of the label */
  line = occurs = 0;

  /* Loop through the lines */
  while (fgets(str, MAXLINE, fp) != NULL) {
    ++line;
    pos = strstr(str, LABEL_KEYWORD);
    /* If the keyword was found */
    if (pos != NULL) {
      ++occurs;
      col = pos - str;
      /* Get the label text and get rid of brackets & newline */
      strcpy(label_text, pos + strlen(LABEL_KEYWORD));
      text = get_label_text(label_text);
      /* Print the result */
      printf("%d:%d %s\n", line, col, text);
      free(text);
    }
  }

  return occurs;
}

char *get_label_text(const char *l)
{
  int i, j;
  /* Subtract 2 because we omit '{' and '}' */
  char *text = calloc(strlen(l) - 2, sizeof(char));

  /* Skip the '{' */
  for (i = 1, j = 0; l[i] != '}'; ++i)
      text[j++] = l[i];
  text[j] = '\0';
  return text;
}
