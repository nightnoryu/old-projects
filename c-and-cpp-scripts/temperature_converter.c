/*
 * This program converts temperature units between each other (celsius, fahrenheit and kelvin)
 */
#include <stdio.h>
#include <stdlib.h>

#define ABS_ZERO 273.15

/* Celsius to fahrenheit */
double c_to_f(double t);

/* Fahrenheit to celsius */
double f_to_c(double t);

/* Celsius to kelvin */
double c_to_k(double t);

/* Kelvin to celsius */
double k_to_c(double t);

/* Farenheit to kelvin */
double f_to_k(double t);

/* Kelvin to fahrenheit */
double k_to_f(double t);


int main(int argc, char** argv) {
  /* Check input parameters */
  if (argc != 4) {
    printf("USAGE: %s [f|c|k] [c|k|f] [value]", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  /* Parse the parameters */
  char from, to;
  from = argv[1][0];
  to   = argv[2][0];
  /* Parse the value */
  double value;
  value = atof(argv[3]);
  
  /* Sort out the parameters and convert */
  double result;
  if (from == 'c' && to == 'f') {
    result = c_to_f(value);
  } else if (from == 'f' && to == 'c') {
    result = f_to_c(value);
  } else if (from == 'c' && to == 'k') {
    result = c_to_k(value);
  } else if (from == 'k' && to == 'c') {
    result = k_to_c(value);
  } else if (from == 'f' && to == 'k') {
    result = f_to_k(value);
  } else if (from == 'k' && to == 'f') {
    result = k_to_f(value);
  } else {
    printf("Unsupported or similar temperature units.\n");
    return 1;
  }
  
  /* Print the result */
  printf("%.3f\n", result);
  
  return EXIT_SUCCESS;
}


double c_to_f(double t)
{
  return (9 * t / 5 + 32);
}

double f_to_c(double t)
{
  return ((t - 32) * 5 / 9);
}

double c_to_k(double t)
{
  return (t + ABS_ZERO);
}

double k_to_c(double t)
{
  return (t - ABS_ZERO);
}

double f_to_k(double t)
{
  return (f_to_c(t) + ABS_ZERO);
}

double k_to_f(double t)
{
  return c_to_f(t - ABS_ZERO);
}
