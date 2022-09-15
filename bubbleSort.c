#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int array[], int size);
void showArray(int array[], int size);
void selectionSort(int array[], int size);
void insertionSort(int array[], int size);

int main()
{
    int array[] = {9, 10, 8, 4, 1, 2, 7, 6, 3, 5};
    int size = 10;

    // bubbleSort(array, size);
    // selectionSort(array, size);
    insertionSort(array, size);

    showArray(array, size);
}

void insertionSort(int array[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int current = array[i];

        showArray(array, size);

        for (int j = i - 1; j >= 0; j--)
        {
            if (array[j] > current)
            {
                array[j + 1] = array[j];
                array[j] = current;
            }
        }
    }
}

void selectionSort(int array[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;

        // showArray(array, size);

        for (int j = i + 1; j < size; j++)
        {
            if (array[j] < array[minIndex])
            {
                minIndex = j;
            }
        }

        printf("\n");
        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
    }
}

void bubbleSort(int array[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int y = 0; y < size - 1; y++)
        {
            if (array[y] > array[y + 1])
            {
                int temp = array[y + 1];
                array[y + 1] = array[y];
                array[y] = temp;
            }
        }
    }
}

void showArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}