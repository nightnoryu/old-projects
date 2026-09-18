/*
 * tail: print last 10 lines in a file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAIL_LINES 10

typedef unsigned int uint;

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

static uint
get_total_lines(FILE* file)
{
  long pos = ftell(file);
  rewind(file);

  char ch;
  uint line = 0;

  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\n') {
      line++;
    }
  }

  fseek(file, pos, SEEK_SET);

  return line;
}

static void
tail(FILE* file)
{
  uint total_lines = get_total_lines(file);

  char ch;

  if (total_lines > TAIL_LINES) {
    uint line = 0;

    while ((ch = fgetc(file)) != EOF) {
      if (ch == '\n') {
        line++;
      }

      if (line >= total_lines - TAIL_LINES) {
        break;
      }
    }
  }

  while ((ch = fgetc(file)) != EOF) {
    putchar(ch);
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

  tail(file);

  free(args);
  fclose(file);

  return EXIT_SUCCESS;
}
