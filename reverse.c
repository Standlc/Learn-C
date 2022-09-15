#include <stdio.h>
#include <stdlib.h>

void print(int array[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);

    printf("\n");
}

void reverse(int array[], int size)
{
    for (int i = 0; i < size / 2; i++)
    {
        int temp = array[i];
        array[i] = array[size - i - 1];
        array[size - i - 1] = temp;
    }
}

int main()
{
    int array[12] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1};
    int size = sizeof(array) / sizeof(array[0]);

    print(array, size);

    reverse(array, size);

    print(array, size);
}
