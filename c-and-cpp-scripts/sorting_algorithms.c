#include <stdio.h>
#include <windows.h>
#include <process.h>

void sleep_sort(int *arr, int n);

void bubble_sort(int *arr, int n);

void gnome_sort(int *arr, int n);

void selection_sort(int *arr, int n);

void insertion_sort(int *arr, int n);

/* Utility functions */
void print_array(int *arr, int n);

void swap(int *a, int *b);


int main(void)
{
  int arr[] = {64, 34, 25, 12, 22, 11, 90};
  int n = sizeof(arr) / sizeof(arr[0]);
  print_array(arr, n);

  insertion_sort(arr, n);
  print_array(arr, n);
  
  return 0;
}


void print_array(int *arr, int n)
{
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  putchar('\n');
}

void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void routine(void *a)
{
  int n = *((int *) a);
  Sleep(n);
  printf("%d ", n);
}

void sleep_sort(int *arr, int n)
{
  HANDLE threads[n];

  for (int i = 0; i < n; i++)
    threads[i] = (HANDLE) _beginthread(&routine, 0, &arr[i]);

  WaitForMultipleObjects(n, threads, TRUE, INFINITE);
}

void bubble_sort(int *arr, int n)
{
  for (int i = 0; i < n-1; i++)
    for (int j = 0; j < n-i-1; j++)
      if (arr[j] > arr[j+1])
        swap(&arr[j], &arr[j+1]);
}

void gnome_sort(int *arr, int n)
{
  int i = 0;
  while (i < n) {
    if (i== 0)
      i++;
    if (arr[i] >= arr[i-1])
      i++;
    else {
      swap(&arr[i], &arr[i-1]);
    }
  }
}

void selection_sort(int *arr, int n)
{
  int minimum_index;
  for (int i = 0; i < n-1; i++) {
    minimum_index = i;
    for (int j = i+1; j < n; j++)
      if (arr[j] < arr[minimum_index])
        minimum_index = j;
    swap(&arr[minimum_index], &arr[i]);
  }
}

void insertion_sort(int *arr, int n)
{
  int j, key;
  for (int i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key) {
      arr[j+1] = arr[j];
      j--;
    }
    arr[j+1] = key;
  }
}
