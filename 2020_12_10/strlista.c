#include <stdio.h>
#include <stdlib.h>
#include "strlista.h"

/*typedef int dane;

typedef struct lelem{//listy element
    dane wart;//wartosc
    struct lelem * nast;
}lelem_t;
*/
lelem_t * stworzListe(dane d)
{
    lelem_t * pocz = NULL;//poczatek listy
    pocz = (lelem_t *)malloc(sizeof(lelem_t));
    if(!pocz){exit(1);}
    pocz->wart = d;
    pocz->nast = NULL;
    return pocz;
}

void dopiszprzedWLiscie(lelem_t ** l, dane d)
{
    lelem_t * nowy = (lelem_t *)malloc(sizeof(lelem_t));
    if(!nowy){exit(3);}
    nowy->wart = d;
    nowy->nast = *l;
    *l = nowy;
}

void dopiszzaWLiscie(lelem_t ** l, dane d)
{
    lelem_t * nowy = (lelem_t *)malloc(sizeof(lelem_t));
    if(!nowy){exit(3);}
    nowy->wart=d;
    if(*l)
    {
        nowy->nast = (*l)->nast;
        (*l)->nast=nowy;

    }
    else{
    nowy->nast=NULL;
    *l=nowy;

    }
}

lelem_t * znajdzWLiscie(lelem_t * lista, dane d)
{
    lelem_t * k = lista;
    while(k != NULL && k->wart!=d)
    {
        k=k->nast;
    }
    return k;
}

dane wyjmZListy(lelem_t ** l)
{
    if(*l)
    {
        lelem_t * usuwany = *l;
        dane d =usuwany->wart;
        *l=(*l)->nast;
        free(usuwany);
        return d;
    }
    else{exit(3);}
}
unsigned int dlListy(lelem_t * l)
{
    lelem_t * wsk=l;
    unsigned int dlugosc=0;
    while(wsk)
    {
        dlugosc++;
        wsk=wsk->nast;
    }
    return dlugosc;
}


int akumulujDlugoscListy_akumulator=0;
int akumulujDlugoscListy(lelem_t * el)
{
    static int akumulator=0;
    static int byl_wlasnie_ostatni=1;
    if(byl_wlasnie_ostatni){akumulator=0; byl_wlasnie_ostatni=0;}
    akumulator++;
    akumulujDlugoscListy_akumulator = akumulator;
    if(el->nast==NULL){byl_wlasnie_ostatni=1;}
    return akumulator;
}


int piszElementListy(lelem_t * el)
{
    printf(" %d,", el->wart);
    if(el->nast==NULL){printf("\n");}
    return 0;
}

dane mapujFunkcjeNaListe( int(funkcja)(lelem_t *), lelem_t * l )
{
    lelem_t * wsk = l;
    dane zwrot=NULL;
    while(wsk)
    {
        zwrot = funkcja(wsk);
        wsk = wsk->nast;
    }
    return zwrot;
}

void wypiszListe(lelem_t *l)
{
    mapujFunkcjeNaListe( piszElementListy, l);
}



