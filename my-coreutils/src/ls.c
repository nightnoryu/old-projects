/*
 * ls: display the contents of the directory
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

struct args_type {
  char dirName[256];
};

static struct args_type *
parse_args(int argc, char **argv)
{
  if (argc > 2) {
    fprintf(stderr, "error: expected 1 or 0 arguments, got %d\n", argc - 1);
    fprintf(stderr, "usage: %s [<directory>]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  struct args_type *args = malloc(sizeof(struct args_type));

  if (argc == 2) {
    strcpy(args->dirName, argv[1]);
  } else {
    strcpy(args->dirName, "./");
  }

  return args;
}

static int
ls(char const *path)
{
  DIR *dp;
  struct dirent *ep;
  dp = opendir(path);

  if (dp == NULL) {
    fprintf(stderr, "error: failed to open directory '%s'\n", path);
    return 0;
  }

  while ((ep = readdir(dp))) {
    if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {
      puts(ep->d_name);
    }
  }

  closedir(dp);
  return 1;
}

int
main(int argc, char **argv)
{
  int ok;
  struct args_type *args = parse_args(argc, argv);

  ok = ls(args->dirName);
  free(args);
  
  return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
