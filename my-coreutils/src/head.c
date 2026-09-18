/*
 * head: print first 10 lines in a file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HEAD_LINES 10

struct args_type {
  char filename[256];
};

static struct args_type *
parse_args(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "error: expected 1 argument, got %d\n", argc - 1);
    fprintf(stderr, "usage: %s <filename>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  struct args_type *args = malloc(sizeof(struct args_type));
  strcpy(args->filename, argv[1]);

  return args;
}

static void
head(FILE* file)
{
  char ch;
  unsigned int line = 0;
  while ((ch = fgetc(file)) != EOF && line < HEAD_LINES) {
    putchar(ch);
    if (ch == '\n')
      line++;
  }
}

int
main(int argc, char **argv)
{
  struct args_type *args = parse_args(argc, argv);

  FILE *file = fopen(args->filename, "r");
  if (file == NULL) {
    fprintf(stderr, "error: failed to open file '%s' for reading\n", args->filename);
    free(args);
    exit(EXIT_FAILURE);
  }

  head(file);

  free(args);
  fclose(file);

  return EXIT_SUCCESS;
}
