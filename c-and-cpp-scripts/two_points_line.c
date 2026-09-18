/*
 * This program forms a line equation based on 2 points
 * (y-y2)/(y1-y2) = (x-x2)/(x1-x2)
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x, y;
} Point;

/* Prompts user for the poinst coordinates */
void input_point(Point *p);

/* Returns the lowest commod denominator of the numbers.
   If some of the numbers < 0, then the lcd is < 0 too */
int get_lcd(int number1, int number2);

/* Prints the equation considering the signs and ones */
void print_equation(int x_coef, int y_coef, int free_coef);


int main(void)
{
  Point p1, p2;

  printf("First point:\n");
  input_point(&p1);
  printf("Second point:\n");
  input_point(&p2);

  int y_divisor = p1.y - p2.y;
  int x_divisor = p1.x - p2.x;

  int lcd = get_lcd(x_divisor, y_divisor);
  int y_denominator = lcd / y_divisor;
  int x_denominator = lcd / x_divisor;

  /* Coefficients considering the swap to the left */
  int y_coef = y_denominator,
      y_free = -(y_denominator * p2.y),
      x_coef = -x_denominator,
      x_free = x_denominator * p2.x;

  /* Resulting free coefficient */
  int total_free = x_free + y_free;

  /* Make the equation prettier */
  if (x_coef < 0) {
    x_coef = -x_coef;
    y_coef = -y_coef;
    total_free = -total_free;
  }

  print_equation(x_coef, y_coef, total_free);
  putchar('\n');

  return EXIT_SUCCESS;
}


void input_point(Point *p)
{
  printf("  X = ");
  scanf("%d", &p->x);
  printf("  Y = ");
  scanf("%d", &p->y);
}

int get_lcd(int n1, int n2)
{
  int product = n1 * n2;
  if (n1 < 0 || n2 < 0) {
    product = -product;
    n1 = abs(n1);
    n2 = abs(n2);
  }

  while (n1 != n2) {
    if (n1 > n2)
      n1 -= n2;
    else
      n2 -= n1;
  }

  return product / n1;
}

void print_equation(int x_coef, int y_coef, int free_coef)
{
  if (x_coef == 1)
    printf("x ");
  else if (x_coef == -1)
    printf("- x ");
  else
    printf("%dx ", x_coef);

  if (y_coef == 1)
    printf("+ y ");
  else if (y_coef == -1)
    printf("- y ");
  else if (y_coef < 0)
    printf("- %dy ", -y_coef);
  else
    printf("+ %dy ", y_coef);
  
  if (free_coef < 0)
    printf("- %d", -free_coef);
  else
    printf("+ %d", free_coef);

  printf(" = 0");
}
