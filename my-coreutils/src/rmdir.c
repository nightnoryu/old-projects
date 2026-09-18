/*
 * rmdir: delete an empty directory
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct args_type {
  char dirname[256];
};

static struct args_type *
parse_args(int argc, char **argv)
{
  if (argc != 2) {
    fprintf(stderr, "error: expected 1 argument, got %d\n", argc - 1);
    fprintf(stderr, "usage: %s <directory path>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  struct args_type *args = malloc(sizeof(struct args_type));
  strcpy(args->dirname, argv[1]);

  return args;
}

static int
my_rmdir(char const *dirname)
{
  return rmdir(dirname) == 0;
}

int
main(int argc, char **argv)
{
  int ok = 1;

  struct args_type *args = parse_args(argc, argv);

  if (!my_rmdir(args->dirname)) {
    fprintf(stderr, "error: failed to remove directory '%s': %s\n", args->dirname, strerror(errno));
  }

  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
