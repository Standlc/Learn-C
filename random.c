#include <stdio.h>
#include <stdlib.h>
#include <time.h> //must be included

int main()
{
    srand(time(0)); // seed
    int MIN = 50;
    int MAX = 100;
    int RANGE = MAX - MIN;

    int randomNumber1 = (rand() % RANGE) + MIN;
    int randomNumber2 = (rand() % RANGE) + MIN;
    int randomNumber3 = (rand() % RANGE) + MIN;

    printf("%d\n", randomNumber1);
    printf("%d\n", randomNumber2);
    printf("%d\n", randomNumber3);
}