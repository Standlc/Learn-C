#include <stdio.h>
#include <stdlib.h>

// POINTERS

void triplePointeur(int *pointeurSurNombre);
int multiply(int numbre);

// int main(void)
// {
//     int nombre = 5;

//     triplePointeur(&nombre); // multiplies number
//     multiply(nombre);        // does not
//     printf("%d\n", multiply(nombre));
// }

// void triplePointeur(int *pointeurSurNombre)
// {
//     *pointeurSurNombre *= 3;
// }

// int multiply(int numbre)
// {
//     return numbre * 3;
// }

// ARRAY SUM

int sum(int *array, int arrayLength);

int main(void)
{
    int array[5] = {3, 2, 5, 3, 6};

    // ARRAY POINTER
    int* pArray = array; 
    // array[i] == *(array + i)
    // &array[i] == array + i

    char character = 'A';

    // POINTER
    char *pCharacter = NULL; // good practice
    pCharacter = &character;

    printf("%c\n", *pCharacter);
    printf("%p\n", pCharacter);
    printf("%c\n", character);

    // printf("%d\n", sum(array, 5));
}

int sum(int *array, int arrayLength)
{
    int sum = 0;

    for (int i = 0; i < arrayLength; i++)
    {
        sum += array[i];
    }

    return sum;
}
