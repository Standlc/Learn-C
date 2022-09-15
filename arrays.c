#include <stdio.h>
#include <stdlib.h>

int findElement(int arr[], int n, int key);
int deleteElement(int arr[], int n, int key);

int insertSorted(int *arr, int n, int key, int capacity)
{
    if (n >= capacity)
        return n;

    *(arr + n) = key;
    return (n + 1);
}

int main()
{
    int arr[20] = {8, 5, 6, 9, 0, 7};
    int capacity = sizeof(arr) / sizeof(arr[0]);
    int n = 6;
    int i, key = 2;

    n = insertSorted(arr, n, key, capacity);

    for (i = 0; i < n; i++)
        printf("%d  ", arr[i]);
}

int deleteElement(int arr[], int n, int key)
{
    int pos = findElement(arr, n, key);
    if (pos == -1)
    {
        printf("Element not found");
        return n;
    }

    for (int i = pos; i < n - 1; i++)
        arr[i] = arr[i + 1];

    return n - 1;
}

int findElement(int arr[], int n, int key)
{
    for (int i = 0; i < n; i++)
        if (arr[i] == key)
            return i;

    return -1;
}