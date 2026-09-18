#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

/* Displays help message */
void display_help(void);

/* Initializes random numbers generator */
void rand_init(void);

/* Suspend for an amount of miliseconds */
void sleep_ms(unsigned int miliseconds);

/* Returns random number between 0 and 2 */
int choose(void);

/* Generates a letter */
char gen_letter(char first_letter);

/* Generates a number from 0 to 9 */
int gen_number(void);


int main(int argc, char* argv[]) {
  rand_init();
  int length = 6;

  /* Parse input parameters */
  if (argc > 1)
    length = atoi(argv[1]);

  /* Check proper length */
  if (length < 1 || length > 30) {
    printf("Invalid length.\n");
    return EXIT_FAILURE;
  }

  int i;
  for (i = 0; i < length; ++i) {
    switch (choose()) {
      case 0:
        printf("%c", gen_letter('a'));
        break;
      case 1:
        printf("%c", gen_letter('A'));
        break;
      case 2:
        printf("%d", gen_number());
        break;
    }
    sleep_ms(500);
  }

  return EXIT_SUCCESS;
}


void rand_init(void) {
  srand(time(NULL));
}

int choose(void) {
  int num = rand() % 3;
  return num;
}

void sleep_ms(unsigned int ms) {
#ifdef _WIN32
  Sleep(ms);
#else
  sleep(ms / 1000);
#endif
}

char gen_letter(char a) {
  char letter = (char) (rand() % 27);
  letter += a;
  return letter;
}

int gen_number(void) {
  int number = rand() % 10;
  return number;
}
