/*
 * touch: create an empty file if it does not exist.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int
file_exists(char const *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    return 0;
  }
  fclose(file);
  return 1;
}

int
main(int argc, char **argv)
{
  struct args_type *args = parse_args(argc, argv);

  if (!file_exists(args->filename)) {
    FILE *file = fopen(args->filename, "w");
    fclose(file);
  }

  free(args);

  return EXIT_SUCCESS;
}
