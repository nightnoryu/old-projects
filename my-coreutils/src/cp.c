/*
 * cp: copy a file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct args_type {
  char sourceFilename[256];
  char destinationFilename[256];
};

static struct args_type *
parse_args(int argc, char **argv)
{
  if (argc != 3) {
    fprintf(stderr, "error: expected 2 arguments, got %d\n", argc - 1);
    fprintf(stderr, "usage: %s <source file> <destination file>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (strcmp(argv[1], argv[2]) == 0) {
    fprintf(stderr, "error: source and destination file names are equivalent\n");
    exit(EXIT_FAILURE);
  }

  struct args_type *args = malloc(sizeof(struct args_type));
  strcpy(args->sourceFilename, argv[1]);
  strcpy(args->destinationFilename, argv[2]);

  return args;
}

static void
cp(FILE *destination, FILE *source)
{
  char ch;
  while ((ch = fgetc(source)) != EOF) {
    fputc(ch, destination);
  }
}

int
main(int argc, char **argv)
{
  struct args_type *args = parse_args(argc, argv);

  FILE *source = fopen(args->sourceFilename, "rb");
  if (source == NULL) {
    fprintf(stderr, "error: cannot open input file '%s' for reading\n", args->sourceFilename);
    free(args);
    exit(EXIT_FAILURE);
  }

  FILE *destination = fopen(args->destinationFilename, "wb");
  if (destination == NULL) {
    fprintf(stderr, "error: cannot open output file '%s' for writing\n", args->destinationFilename);
    free(args);
    fclose(source);
    exit(EXIT_FAILURE);
  }

  cp(destination, source);

  free(args);
  fclose(source);
  fclose(destination);

  return EXIT_SUCCESS;
}
