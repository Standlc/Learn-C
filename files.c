#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000

int main(int argc, char *argv[])
{
    FILE *fichier = NULL;
    fichier = fopen("test.txt", "w"); // "a" append, "w" write, r+ append + write

    if (fichier != NULL)
    {
        // WRITE
        fputc('A', fichier);                                                      // Écriture du caractère A, seulement pour un caractère
        fprintf(fichier, "\nyoyoy\n");                                            // write string
        fputs("Salut les développeurs\nBienvenue sur OpenClassrooms !", fichier); // write string

        // PRINT FILE CONTENT
        char content[MAX_LEN];
        while (fgets(content, MAX_LEN, fichier) != NULL)
            printf("%s", content);

        // DELETE, RENAME
        //  remove("test.txt");
        //  rename("test.txt", "new_name.txt");
        fclose(fichier);
    }
    else
        printf("Impossible d'ouvrir le fichier test.txt");
}