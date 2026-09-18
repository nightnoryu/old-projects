/*
 * rm: delete a file
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXFILENAME 256

struct args_type {
  int fileAmount;
  char **filenames;
};

static struct args_type *
parse_args(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "error: expected 1 or more arguments, got 0\n");
    fprintf(stderr, "usage: %s <input file 1> [<input file 2>] ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  struct args_type *args = malloc(sizeof(struct args_type));
  args->fileAmount = argc - 1;
  args->filenames = malloc((argc - 1) * sizeof(char *));
  for (int i = 0; i < args->fileAmount; i++) {
    args->filenames[i] = malloc(MAXFILENAME * sizeof(char));
  }

  for (int i = 1; i < argc; i++) {
    strcpy(args->filenames[i - 1], argv[i]);
  }

  return args;
}

static int
rm(char const *filename)
{
  return remove(filename) == 0;
}

int
main(int argc, char **argv)
{
  int ok = 1;

  struct args_type *args = parse_args(argc, argv);

  for (int i = 0; i < args->fileAmount; i++) {
    if (!rm(args->filenames[i])) {
      fprintf(stderr, "error: failed to delete file '%s': %s\n", args->filenames[i], strerror(errno));
      ok = 0;
      break;
    }
  }

  free(args);

  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
