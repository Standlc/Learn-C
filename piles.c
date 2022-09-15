#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Element Element;
struct Element
{
    int value;
    Element *next;
};

typedef struct Pile Pile;
struct Pile
{
    Element *first;
};

void add(Pile *pile, int value)
{
    Element *new = malloc(sizeof(*new));

    new->value = value;
    new->next = pile->first;
    pile->first = new;
}

void addToIndex(Pile *pile, int value, int index)
{
    Element *new = malloc(sizeof(*new));
    Element *prev = pile->first;

    for (int i = 2; i <= index; i++)
        if (prev->next != NULL)
            prev = prev->next;

    new->value = value;

    if (index)
    {
        new->next = prev->next;
        prev->next = new;
    }
    else
    {
        new->next = pile->first;
        pile->first = new;
    }
}

void showPile(Pile *pile)
{
    Element *currentElement = pile->first;

    while (currentElement != NULL)
    {
        printf("%d -> ", currentElement->value);
        currentElement = currentElement->next;
    }
    printf("NULL\n");
}

void deleteFirst(Pile *pile)
{
    Element *firstElement = pile->first;
    pile->first = firstElement->next;
    free(firstElement);
}

void delete (Pile *pile)
{
    Element *currentEl = pile->first;

    while (currentEl != NULL)
    {
        free(currentEl);
        currentEl = currentEl->next;
    }

    free(pile);
}

void sort(Pile *pile)
{
    Element *current = pile->first;

    while (current != NULL)
    {
        Element *index = pile->first;

        while (index->next != NULL)
        {
            if (index->value > index->next->value)
            {
                int temp = index->next->value;
                index->next->value = index->value;
                index->value = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}

void addInOrder(Pile *pile, int value)
{
    Element *new = malloc(sizeof(*new));
    new->value = value;

    Element *current = pile->first;
    Element *prev = pile->first;

    while (current != NULL && current->value < new->value)
    {
        if (current != prev)
            prev = prev->next;

        current = current->next;
    }

    bool valueIsSmallerThanFirstEl = new->value < prev->value;

    if (valueIsSmallerThanFirstEl)
    {
        new->next = pile->first;
        pile->first = new;
    }
    else
    {
        new->next = current;
        prev->next = new;
    }
}

int main(void)
{
    Pile *myPile = NULL;
    myPile = malloc(sizeof(*myPile));

    if (myPile == NULL)
        exit(0);

    add(myPile, 5);
    add(myPile, 15);
    add(myPile, 45);
    add(myPile, 54);
    add(myPile, 55);

    addToIndex(myPile, 100, 0);
    addToIndex(myPile, 69, 3);

    sort(myPile);

    addInOrder(myPile, 55);

    // deleteFirst(myPile);
    // deleteFirst(myPile);

    showPile(myPile);

    free(myPile);
}