/*
 * time: measure command's running time.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct args_type {
  char *command;
};

static struct args_type *
parse_args(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "error: expected 1 or more arguments, got %d\n", argc - 1);
    fprintf(stderr, "usage: %s <command> <argument 1> ...\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  struct args_type *args = malloc(sizeof(struct args_type));

  int cmd_length = 0;
  for (int i = 1; i < argc; i++) {
    cmd_length += strlen(argv[i]);
    if (i < argc - 1) {
      cmd_length++;
    }
  }

  args->command = malloc(cmd_length * sizeof(char));
  args->command[0] = '\0';

  for (int i = 1; i < argc; i++) {
    strcat(args->command, argv[i]);
    if (i < argc - 1) {
      strcat(args->command, " ");
    }
  }

  return args;
}

void
_time(char const *command)
{
  size_t start, finish, delta;

  start = time(NULL);
  system(command);
  finish = time(NULL);
  delta = finish - start;

  printf("\nTIMING '%s'\n", command);
  printf("  %ds\n", delta);
}

int
main(int argc, char **argv)
{
  struct args_type *args = parse_args(argc, argv);

  _time(args->command);

  free(args->command);
  free(args);

  return EXIT_SUCCESS;
}
