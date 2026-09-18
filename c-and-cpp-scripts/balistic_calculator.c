/*
 * This program computes the characteristics of the balistic movement
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define G  9.80665
#define PI 3.14159

/* Returns squared number */
double sqr(double number);

/* Converts angle from degrees to radians */
double deg_to_rad(double angle);

/* Calculates overall movement time */
double calc_time(double angle, double speed);

/* Calculates overall distance (on OX axis) */
double calc_distance(double angle, double speed);

/* Calculates max height */
double calc_height(double angle, double speed);


int main(void)
{
  double angle, speed;
  
  /* Input the values */
  printf("Enter the movement angle (deg): ");
  scanf("%lf", &angle);
  printf("Enter the starting speed (m/s): ");
  scanf("%lf", &speed);
  
  /* Print results */
  printf("Movement time: %.5f\n", calc_time(speed, angle));
  printf("Horizontal distance: %.5f\n", calc_distance(speed, angle));
  printf("Max height: %.5f\n", calc_height(speed, angle));
  
  return EXIT_SUCCESS;
}


double sqr(double n)
{
  return (n * n);
}

double deg_to_rad(double a)
{
  return (a * PI / 180);
}

double calc_time(double a, double u)
{
  return (2 * u * sin(deg_to_rad(a)) / G);
}

double calc_distance(double a, double u)
{
  return (sqr(u) * sin(2 * deg_to_rad(a)) / G);
}

double calc_height(double a, double u)
{
  return (sqr(u) * sqr(sin(deg_to_rad(a))) / (2 * G));
}
