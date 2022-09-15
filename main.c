#include <stdio.h>
#include <stdlib.h>

// RUN PROGRAM
//  (clang OR gcc) (main.c OR -o main.out main.c)
//  make <file name>

// INCLUDE
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600
#define NOMBRE_PIXELS (LARGEUR_FENETRE * HAUTEUR_FENETRE)

#ifndef DEF_NOMDUFICHIER // Si la constante n'a pas été définie le fichier n'a jamais été inclus
#define DEF_NOMDUFICHIER // On définit la constante pour que la prochaine fois le fichier ne soit plus inclus

/* Contenu de votre fichier .h (autres include, prototypes, define...) */

#endif

char assignFeeling(int number)
{
    char feeling = 'n';

    if(number == 1)
    {
        feeling = 'good';
    }
    if(number == 2)
    {
        feeling = 'b';
    }

    return feeling;
}

// int main()
// {
//     int number = 0;

//     printf("how are you ? \n 1: good \n 2: bad\n");
// scanf("%d", &number);

//     printf("%c\n", assignFeeling(number));

// }

// int *monPointeur = NULL;
// static int resultat = 0;

// void build_array( int array_variable[], int length_of_array )
// {
//     for (int i=0; i<length_of_array; i++)
//       {
//         array_variable[i] = i;
//       }
// }

// int main()
// {
//   int values[50];

//   printf("the value at location 7 starts as %d\n", values[7]);
//   build_array(values, 50);
//   printf("the value at location 7 is now %d\n", values[7]);
//   return 0;
// }

int main(void)
{
    printf("hello");
}