#include <stdio.h>

void xor_swap();
void xor_find_missing();
void xor_find_duplicate();


int main(void)
{
  xor_swap();
  putchar('\n');
  xor_find_missing();
  putchar('\n');
  xor_find_duplicate();
  putchar('\n');

  return 0;
}


void xor_swap()
{
  printf("Swapping two variables\n");
  int a = 12, b = 24;
  printf("%d, %d\n", a, b);
  a ^= b;
  b ^= a;
  a ^= b;
  printf("%d, %d\n", a, b);
}

void xor_find_missing()
{
  printf("Finding the missing number in the sequence of n integers\n");
  int n = 4;
  int numbers[] = {1, 3, 4, 5};
  int missing_number = 0;
  for (int i = 1; i <= n + 1; i++)
    missing_number ^= i;
  for (int i = 0; i < n; i++)
    missing_number ^= numbers[i];
  printf("%d\n", missing_number);
}

void xor_find_duplicate()
{
  printf("Finding the duplicate item in the sequence of n integers\n");
  int n = 6;
  int numbers[] = {1, 2, 3, 4, 4, 5};
  int duplicate = 0;
  for (int i = 1; i < n; i++)
    duplicate ^= i;
  for (int i = 0; i < n; i++)
    duplicate ^= numbers[i];
  printf("%d\n", duplicate);
}
