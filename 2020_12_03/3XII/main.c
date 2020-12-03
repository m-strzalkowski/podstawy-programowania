#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#include "intlista.h"



int miesiac(struct tm * tm)
{
    return tm->tm_mon;
}

int rok(struct tm * tm)
{
    return tm->tm_year;
}

void printprettytime(time_t rawtime)
{
    struct tm * timeinfo;
    timeinfo = localtime (&rawtime);
    printf ("Current local time and date: %s", asctime(timeinfo));
}

void printBinary(long long x)
{


    int i=0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}


int main()
{

    time_t rawtime;
    time (&rawtime);
    printprettytime(rawtime);
    printBinary(1+2+4+8+32);

    lelem_t * pocz = NULL;//poczatek listy
    //pocz = stworzListe(7);
    wsadzWListe(&pocz, 4);
    wsadzWListe(&pocz, 3);
    wsadzWListe(&pocz, 9);
    wypiszListe(pocz);
    printf("%d\n", zdejmZListy(&pocz));
    wypiszListe(pocz);
    printf("dlugosc listy:%d", mapujFunkcjeNaListe(akumulujDlugoscListy, pocz));


    return 0;
}
