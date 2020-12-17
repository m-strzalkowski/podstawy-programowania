#include <stdio.h>
#include <stdlib.h>
#include "intlista.h"

int main()
{
    lelem_t * lista=NULL;
    wypiszListe(lista);
    dopiszprzedWLiscie(&lista, 7);
    wypiszListe(lista);
    dopiszprzedWLiscie(&lista, 3);
    wypiszListe(lista);
    dopiszzaWLiscie(&lista,1);
    wypiszListe(lista);
    printf("dlugosc listy:%d\n", dlListy(lista));
    return 0;
}
