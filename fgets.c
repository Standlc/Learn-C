#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
        c = getchar();
}

int input(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    if (fgets(chaine, longueur, stdin) == NULL)
    {
        viderBuffer();
        return 0;
    }

    positionEntree = strchr(chaine, '\n');

    if (positionEntree != NULL)
        *positionEntree = '\0';
    else
        viderBuffer();

    return 1;
}