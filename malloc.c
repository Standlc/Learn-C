#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *allocation = NULL;
    allocation = malloc(sizeof(int));

    if (allocation == NULL)
    {
        exit(0);
    }

    free(allocation);
}