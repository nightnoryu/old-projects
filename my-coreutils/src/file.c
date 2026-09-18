/*
 * file: print information about a file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

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
is_binary(FILE *file)
{
  char ch;
  int is_binary = 0;
  while ((ch = fgetc(file)) != EOF) {
    if (ch == '\0') {
      is_binary = 1;
      break;
    }
  }

  return is_binary;
}

static void
print_file_info(char const *filename, FILE* file, const struct stat *filestat)
{
  printf("file '%s': %s\n", filename, is_binary(file) ? "binary" : "text");
  printf("  size (in bytes): %ld\n", filestat->st_size);
  printf("  modfication date: %s\n", ctime(&filestat->st_mtime));
}

int
main(int argc, char **argv)
{
  struct args_type *args = parse_args(argc, argv);

  struct stat filestat;
  FILE *file = fopen(args->filename, "rb");

  if (stat(args->filename, &filestat) || file == NULL) {
    fprintf(stderr, "error: cannot open file '%s'\n", args->filename);
    free(args);
    exit(EXIT_FAILURE);
  }

  print_file_info(args->filename, file, &filestat);

  fclose(file);
  free(args);

  return EXIT_SUCCESS;
}
