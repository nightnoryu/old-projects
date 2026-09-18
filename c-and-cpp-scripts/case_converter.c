/*
 * This program converts the case of the inputed text according to the selected 
 * parameters
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

/* Prints program's help and usage info */
void print_help();

/* Converts the text from stdin to lowercase and prints it out */
void lower_input();

/* Converts the text from stdin to uppercase and prints it out */
void upper_input();

/* Capitalizes the text from stdin and prints it out */
void capitalize_input();


int main(int argc, char **argv)
{
  int opt;
  opterr = 0;

  /* Parse the parameters */
  while ((opt = getopt(argc, argv, "hluc")) != -1) {
    switch (opt) {
      case 'h':
        print_help();
        break;
      case 'l':
        lower_input();
        break;
      case 'u':
        upper_input();
        break;
      case 'c':
        capitalize_input();
        break;
      case '?':
        fprintf(stderr, "Unknown option: -%c\n", optopt);
        exit(EXIT_FAILURE);
    }
  }

  return EXIT_SUCCESS;
}


void print_help()
{
  printf("Convert the case of the text from stdin.\n\n"
         "Usage: case_converter [OPTION]\n\n"
         "Options: \n"
         "  -h   show this message\n"
         "  -l   convert text to lowercase\n"
         "  -u   convert text to uppercase\n"
         "  -c   capitalize text\n");
}

void lower_input()
{
  /* Current character */
  char c;

  while ((c = getchar()) != EOF)
    putchar(tolower(c));
}

void upper_input()
{
  /* Current character */
  char c;

  while ((c = getchar()) != EOF)
    putchar(toupper(c));
}

void capitalize_input()
{
  /* Current and previous char */
  char c, pc;

  pc = '\0';
  while ((c = getchar()) != EOF) {
    /* Properly handle apostrophes */
    if (!isalpha(pc) && pc != '\'')
      c = toupper(c);

    /* Print the char & update the previous one */
    putchar(c);
    pc = c;
  }
}
