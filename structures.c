#include <stdio.h>
#include <stdlib.h>

// STRUCTURES
typedef struct
{
    char nom[100];
    char prenom[100];
    char adresse[1000];
    int age;
    int etudiant;
} User;

typedef struct Coordinates Coordinates;
struct Coordinates
{
    int x;
    int y;
};

// ENUM

typedef enum Volume Volume;
enum Volume
{
    FAIBLE = 10,
    MOYEN = 50,
    FORT = 100
};

void initializeCoordinates(Coordinates *point);

int main(void)
{
    Coordinates point;

    initializeCoordinates(&point);

    printf("%d, %d", point.x, point.y);
}

void initializeCoordinates(Coordinates *point)
{
    (*point).x = 5;
    // OR
    point->y = 10;
}