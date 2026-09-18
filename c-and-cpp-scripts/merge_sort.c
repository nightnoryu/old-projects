/*
 * This program demonstrates the merge sort algorithm
 */
#include <stdio.h>

/* Performs merge sort of the array */
void merge_sort(int *array, int start_index, int end_index);

/* Prints the array in one line with no linebreaks at the end */
void print_array(int *array, int array_size);


int main(void)
{
  int array[] = { 12, 11, 13, 5, 6, 7 };
  int array_size = sizeof(array) / sizeof(array[0]);

  printf("Inital array: ");
  print_array(array, array_size);
  putchar('\n');

  merge_sort(array, 0, array_size - 1);

  printf("Sorted array: ");
  print_array(array, array_size);
  putchar('\n');

  return 0;
}


void merge(int *arr, int s, int m, int e)
{
  int i, j, k;
  int n1 = m - s + 1;
  int n2 = e - m;

  /* Split the array into right and left */
  int left[n1], right[n2];
  for (i = 0; i < n1; ++i)
    left[i] = arr[s + i];
  for (j = 0; j < n2; ++j)
    right[j] = arr[m + 1 + j];

  /* Merge and perform sorting */
  i = j = 0;
  k = s;
  while (i < n1 && j < n2) {
    if (left[i] < right[j]) {
      arr[k] = left[i];
      ++i;
    } else {
      arr[k] = right[j];
      ++j;
    }
    ++k;
  }

  /* Copy the remainig elements */
  while (i < n1) {
    arr[k] = left[i];
    ++i;
    ++k;
  }
  while (j < n2) {
    arr[k] = right[j];
    ++j;
    ++k;
  }
}

void merge_sort(int *arr, int s, int e)
{
  int m;
  if (s < e) {
    /* Same as (s + e) / 2 to avoid overflow */
    m = s + (e - s) / 2;

    merge_sort(arr, s, m);
    merge_sort(arr, m + 1, e);

    merge(arr, s, m, e);
  }
}

void print_array(int *arr, int s)
{
  int i;
  for (i = 0; i < s; ++i) {
    printf("%d ", arr[i]);
  }
}
