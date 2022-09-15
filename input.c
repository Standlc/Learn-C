#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char input1[30];
    char input2[30];

    // printf("first input");

    // scanf("%s", input1); // does not read white spaces

    // printf("second input");

    // fgets(input2, 30, stdin);          // reads white spaces and enter key at the end
    // input2[strlen(input2) - 1] = '\0'; // removes enter key

    // printf("hello, %s", input1);

    int age;

    scanf("%d", &age);

    printf("your age is : %d", age);
}