/*
 * This program calculates the BMI in both metric and imperial units
 */
#include <stdio.h>
#include <stdlib.h>

/* Calculates the BMI in metric units */
double calc_bmi(double mass, double height);

/* Calculates the BMI in imperial units */
double calc_bmi_imperial(double mass, double height);


int main(void)
{
  double mass, height, bmi;
  int choice;

  /* Choose the units */
  printf("What units do you prefer?\n1. Metric\n2. Imperial\n>");
  scanf("%d", &choice);

  if (choice == 1) {
    /* Input the values */
    printf("Enter your mass (kg): ");
    scanf("%lf", &mass);
    printf("Enter your height (m): ");
    scanf("%lf", &height);

    /* Calculate the BMI */
    bmi = calc_bmi(mass, height);
  } else if (choice == 2) {
    /* Input the values */
    printf("Enter your mass (lbs): ");
    scanf("%lf", &mass);
    printf("Enter your height (in): ");
    scanf("%lf", &height);

    /* Calculate the BMI */
    bmi = calc_bmi_imperial(mass, height);
  } else {
    /* Handle invalid choice of units */
    printf("Invalid choice: %d\n", choice);
    exit(EXIT_FAILURE);
  }

  /* Print the result */
  printf("Your BMI is %.2f\n", bmi);
  return EXIT_SUCCESS;
}


double calc_bmi(double m, double h)
{
  return (m / (h * h));
}

double calc_bmi_imperial(double m, double h)
{
  return (703 * calc_bmi(m, h));
}
