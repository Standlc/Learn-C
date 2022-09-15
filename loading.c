#include <stdio.h>
#include <stdlib.h>

int main()
{
    char progress[] = "-\\|/";
    int i = 0;
    int index = 0;

    while (1)
    {
        printf("[%c]\r", progress[index]);
        i++;

        if (!(i % 400000))
            index == 3 ? index = 0 : index++;
    }
}