#include<stdio.h>
#include<stdlib.h>

#include "glob.h"

void * mallocspr(size_t rozm)
{
    void * wsk = malloc(rozm);
    if(!wsk)
    {
        perror("NIE DOSTALEM PAMIECI - konczenie");
        exit(7);
    }
    return wsk;
}
