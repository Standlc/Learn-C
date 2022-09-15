#include <stdio.h>
#include <stdlib.h>
#include <math.h> //lib for calculations

int main(void)
{
    int a = 5;
    int b = 2;
    float result;

    result = a / (float)b; // convert to floating number to get correct result
    result = 5.0 / 2.0;

    printf("%.1f", result);

    // MATH FUNCTIONS
    int A = sqrt(9);
    int B = pow(2, 3);
    int C = round(3.14);
    int D = ceil(3.14);
    int E = floor(3.14);
    int F = fabs(3.14);
    int G = cos(45);
    int H = sin(45);
    int I = tan(45);
}