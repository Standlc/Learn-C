#include <stdio.h>
#include <stdlib.h>

// STRINGS
#include <string.h>

int stringLength(const char *string)
{
    int length = 0;
    int i = 0;

    while (string[i] != '\0')
    {
        i++;
        length++;
    }

    return length;
}

int main(void)
{
    char string1[50] = "Romeo";
    char string2[] = "hello";

    // int nameLength = stringLength(name);
    int nameLength = strlen(string1);

    // STRING FUNCTIONS
    // strlwr(string1);
    // strupr(string1);
    // strcat(string1, string2);
    // strncat(string1, string2, 1); //number of characters from second string that are appended to first ones
    // strcpy(string1, string2);
    // sprintf(string1, "salut toi");
    // strncpy(string1, string2, 4); //number of characters from second string that are copied to first ones
    // strrev(string1); //reverse string
    // strset(string1, '$'); //sets all characters to $
    // strset(string1, '?', 3); // sets first n charcaters with given string

    string1[1] = 'y'; // must be simple quotes not " "

    int comparison = strcmp(string1, string2);
    int comparison2 = strncmp(string1, string2, 1);

    printf("%s", string1);
    // printf("%d\n", nameLength);
}