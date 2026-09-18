/*
 * sort: print sorted lines from standard input
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 512

static void
check_args(int argc)
{
  if (argc != 1) {
    fprintf(stderr, "error: too many arguments; please provide the standard input\n");
    fprintf(stderr, "usage: sort\n");
    exit(EXIT_FAILURE);
  }
}

static void
swap(char **a, char **b)
{
  char *t = *a;
  *a = *b;
  *b = t;
}

static int
partition(int low, int high, char **lines)
{
  char *pivot = lines[high];
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (strcmp(lines[j], pivot) < 0) {
      i++;
      swap(&lines[i], &lines[j]);
    }
  }
  swap(&lines[i + 1], &lines[high]);
  return i + 1;
}

static void
quick_sort(int low, int high, char **lines)
{
  if (low < high) {
    int pi = partition(low, high, lines);
    quick_sort(low, pi - 1, lines);
    quick_sort(pi + 1, high, lines);
  }
}

static void
sort(void)
{
  int count = 0;
  char line[LINESIZE];
  char **lines = NULL;
  char **more_lines = NULL;

  while (fgets(line, LINESIZE, stdin)) {
    count++;
    more_lines = realloc(lines, count * sizeof(char *));

    if (more_lines == NULL) {
      fprintf(stderr, "error: failed to allocate memory\n");
      break;
    }

    lines = more_lines;
    lines[count - 1] = malloc(LINESIZE * sizeof(char));
    strcpy(lines[count - 1], line);
  }

  quick_sort(0, count - 1, lines);
  for (int i = 0; i < count; i++) {
    printf("%s", lines[i]);
  }

  for (int i = 0; i < count; i++) {
    free(lines[i]);
  }
  free(lines);
}

int
main(int argc, char **argv)
{
  check_args(argc);

  sort();

  return EXIT_SUCCESS;
}
