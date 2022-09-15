#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int absDiff(int n)
{
    int diff = 51 - abs(n);
    return n > 51 ? diff * 3 : diff;
}

bool check30(int a, int b)
{
    int sum = a + b;
    if (sum == 30 || a == 30 || b == 30)
        return true;
    return false;
}

bool checkWithin10(int a)
{
    if (abs(100 - a) <= 10 || abs(200 - a) <= 10)
        return true;
    return false;
}

int checkMultiple(int a)
{
    if (!(a % 3) || !(a % 7))
        return 1;
    return 0;
}

int checkRange(int a, int b, int c)
{
    return (a >= 20 && a <= 50) || (b >= 20 && b <= 50) || (c >= 20 && c <= 50);
}

int checkNearest(int a, int b)
{
    int diffA = abs(100 - a);
    int diffB = abs(100 - b);

    if (diffA > diffB)
        return b;
    if (diffA < diffB)
        return a;
    return 0;
}

int checkLastDigit(int a, int b)
{
    int diff = abs(a - b);

    return !(diff % 10);

    // return abs(a % 10) == abs(b % 10)
}

int getPairsOf5(int array[], int size)
{
    int pairs = 0;

    for (int i = 0; i < size - 1; i++)
    {
        if (array[i] == 5 && array[i + 1] == 5)
        {
            pairs++;
            i++;
        }
    }

    return pairs;
}

int checkTriples(int array[], int size)
{
    for (int i = 0; i < size - 2; i++)
    {
        if (array[i] == array[i + 1] && array[i] == array[i + 2])
            return 1;
    }
    return 0;
}

int checkNInARow(int n, int arr[], int size)
{
    int count = 0;
    int countCopy = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] == n)
        {
            count++;
            countCopy = count;
        }
        else
            count = 0;
    }

    return countCopy;
}

void shiftZeros(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == 0)
        {
            for (int j = i; j > 0; j--)
            {
                if (arr[j - 1] > 0)
                {
                    arr[j] = arr[j - 1];
                    arr[j - 1] = 0;
                }
            }
        }
    }
}

void shiftEvenNumbers(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (!(arr[i] % 2))
        {
            for (int j = i; j > 0; j--)
            {
                if ((arr[j - 1] % 2))
                {
                    int temp = arr[j];
                    arr[j] = arr[j - 1];
                    arr[j - 1] = temp;
                }
            }
        }
    }
}

typedef struct
{
    int i;
    int size;
} Index;

int findIndexFor1(int arr[], int size)
{
    Index ones[20];
    int onesCount = -1;

    for (int i = 0; i < size; i++)
    {
        if (i && arr[i] && !arr[i - 1] || !i && arr[i])
        {
            onesCount++;
            ones[onesCount].i = i;
            ones[onesCount].size = 0;
            ones[onesCount].size++;
        }
        if (i && arr[i] && arr[i - 1])
            ones[onesCount].size++;
    }

    int index = 0;
    int maxOnes = 0;

    for (int i = 0; i < onesCount + 1; i++)
    {
        if (ones[i].i + ones[i].size + 1 == ones[i + 1].i && ones[i].size + ones[i + 1].size + 1 > maxOnes)
        {
            index = ones[i].i + ones[i].size;
            maxOnes = ones[i].size + ones[i + 1].size + 1;
        }
    }

    printf("%d\n", index);

    return onesCount;
}

void weirdArrangement(int arr[], int size)
{
    int copy[size];
    for (int i = 0; i < size; i++)
    {
        copy[arr[i]] = i;
    }

    for (int i = 0; i < size; i++)
        printf("%d", copy[i]);
}

void surpasserCount(int arr[], int size)
{
    int copy[size];

    for (int i = 0; i < size - 1; i++)
    {
        copy[i] = 0;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] < arr[j])
            {
                copy[i]++;
            }
        }
    }

    for (int i = 0; i < size; i++)
        printf("%d ", copy[i]);
}

void maxProductSubArr(int arr[], int size)
{
    int subArr[size];
    int subArrSize = 1;
    int product = 0;

    for (int i = 0; i < size - 1; i++)
    {
        int currentProduct = arr[i];
        for (int j = i + 1; j < size; j++)
        {
            currentProduct *= arr[j];

            if (!currentProduct)
                j = size;
            else if (currentProduct > product)
            {
                product = currentProduct;

                subArr[0] = arr[i];
                for (int k = 0; k <= j - i; k++)
                    subArr[k] = arr[k + i];
                subArrSize = j - i + 1;
            }
        }
    }

    for (int i = 0; i < subArrSize; i++)
        printf("%d ", subArr[i]);
}

void trappingRainWater(int arr[], int size)
{
    int heighestN = arr[0], heighestNIndex = 0;
    int nextHeighestN = 0, nextHeighestNIndex = 0;
    int maxTrappedWatter = 0;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] > heighestN)
        {
            heighestN = arr[i];
            heighestNIndex = i;
        }

        if (arr[i] > nextHeighestN && arr[i] < heighestN)
        {
            nextHeighestN = arr[i];
            nextHeighestNIndex = i;
        }
    }

    for (int i = heighestNIndex + 1; i < nextHeighestNIndex; i++)
    {
        maxTrappedWatter += nextHeighestN - arr[i];
    }

    printf("\n%d", maxTrappedWatter);
}

int main()
{
    // int array[] = {0, 4, 3, 5, 5, 0, 2, 2, 0, 2, 5, 5, 5, 0};
    // int arr[] = {0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1};
    // int arr[] = {2, 50, 4, 2, 0, 4, 8, 10, 0, 200, 10};
    int arr[] = {7, 0, 4, 2, 5, 0, 6, 4, 0, 5};

    // printf("%d\n", absDiff(52));

    // printf("%d\n", check30(15, 15));

    // printf("%d\n", checkWithin10(190));

    // printf("%d\n", checkMultiple(21));

    // printf("%d\n", checkRange(10, 30, 60));

    // printf("%d\n", checkNearest(50, 50));

    // printf("%d\n", checkLastDigit(55, -45));

    // printf("%d\n", getPairsOf5(arr, sizeof(arr) / sizeof(arr[0])));

    // printf("%d\n", checkTriples(arr, sizeof(arr) / sizeof(arr[0])));

    // printf("%d\n", checkNInARow(2, arr, sizeof(arr) / sizeof(arr[0])));

    // shiftZeros(arr, sizeof(arr) / sizeof(arr[0]));

    // shiftEvenNumbers(arr, sizeof(arr) / sizeof(arr[0]));

    // for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
    //     printf("%d ", arr[i]);
    // findIndexFor1(arr, sizeof(arr) / sizeof(arr[0]));
    // printf("%d\n", );

    // weirdArrangement(arr, sizeof(arr) / sizeof(arr[0]));

    // surpasserCount(arr, sizeof(arr) / sizeof(arr[0]));

    // maxProductSubArr(arr, sizeof(arr) / sizeof(arr[0]));

    trappingRainWater(arr, sizeof(arr) / sizeof(arr[0]));
}