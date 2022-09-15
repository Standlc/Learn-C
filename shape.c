#include <stdio.h>
#include <stdlib.h>

void triangles(int HEIGHT, const char SYMBOL[], const char SYMBOL2[])
{
    for (int i = 0; i <= HEIGHT / 2; i++)
    {
        printf("%s", SYMBOL);

        for (int j = 0; j < i; j++)
            printf("%s", SYMBOL);

        for (int j = 0; j <= HEIGHT - (2 * i); j++)
            printf("%s", SYMBOL2);

        for (int j = 0; j <= i; j++)
            printf("%s", SYMBOL);

        printf("\n");
    }

    for (int i = HEIGHT / 2; i > 0; i--)
    {
        printf("%s", SYMBOL);

        for (int j = 0; j < i - 1; j++)
            printf("%s", SYMBOL);

        for (int j = -2; j <= HEIGHT - (2 * i); j++)
            printf("%s", SYMBOL2);

        for (int j = 0; j < i; j++)
            printf("%s", SYMBOL);

        printf("\n");
    }
}

void cross(int HEIGHT, const char SYMBOL[], const char SYMBOL2[])
{
    for (int i = 0; i <= HEIGHT / 2; i++)
    {
        for (int j = 0; j < i; j++)
            printf(" ");

        for (int j = 0; j <= HEIGHT / 3; j++)
            printf("%s", SYMBOL);

        for (int j = 0; j <= HEIGHT - (2 * i); j++)
            printf("%s", SYMBOL2);

        for (int j = 0; j <= HEIGHT / 3; j++)
            printf("%s", SYMBOL);

        printf("\n");
    }

    for (int i = HEIGHT / 2; i > 0; i--)
    {
        for (int j = 1; j < i; j++)
            printf(" ");

        for (int j = 0; j <= HEIGHT / 3; j++)
            printf("%s", SYMBOL);

        for (int j = -2; j <= HEIGHT - (2 * i); j++)
            printf("%s", SYMBOL2);

        for (int j = 0; j <= HEIGHT / 3; j++)
            printf("%s", SYMBOL);

        printf("\n");
    }
}

int main()
{
    const char SYMBOL[] = "+";
    const char SYMBOL2[] = " ";
    const int HEIGHT = 20;

    triangles(HEIGHT, SYMBOL, SYMBOL2);

    printf("\n");

    cross(HEIGHT, SYMBOL, SYMBOL2);
}