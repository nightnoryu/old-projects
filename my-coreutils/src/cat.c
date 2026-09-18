/*
 * cat: print contents of a file to the standard output.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFILENAME 256

struct args_type {
  int fileAmount;
  char **inputFilenames;
};

static struct args_type *
parse_args(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "error: expected 1 or more arguments, got %d\n", argc - 1);
    fprintf(stderr, "usage: %s <input file 1> [<input file 2>] ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  struct args_type *args = malloc(sizeof(struct args_type));
  args->fileAmount = argc - 1;
  args->inputFilenames = malloc((argc - 1) * sizeof(char *));
  for (int i = 0; i < args->fileAmount; i++) {
    args->inputFilenames[i] = malloc(MAXFILENAME * sizeof(char));
  }

  for (int i = 1; i < argc; i++) {
    strcpy(args->inputFilenames[i - 1], argv[i]);
  }

  return args;
}

static void
cat(FILE *input)
{
  char ch;
  while ((ch = fgetc(input)) != EOF) {
    putchar(ch);
  }
}

int
main(int argc, char **argv)
{
  int ok = 1;

  struct args_type *args = parse_args(argc, argv);
  FILE *file;

  for (int i = 0; i < args->fileAmount; i++) {
    file = fopen(args->inputFilenames[i], "r");

    if (file == NULL) {
      fprintf(stderr, "error: failed to open input file '%s' for reading\n", args->inputFilenames[i]);
      ok = 0;
      break;
    }

    cat(file);
    fclose(file);
  }

  for (int i = 0; i < args->fileAmount; i++) {
    free(args->inputFilenames[i]);
  }
  free(args->inputFilenames);
  free(args);

  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
