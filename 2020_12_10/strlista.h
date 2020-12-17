
#ifndef INTLISTA_H
#define INTLISTA_H
typedef char * dane;

typedef struct lelem{//listy element
    dane wart;//wartosc
    struct lelem * nast;
}lelem_t;

lelem_t * stworzListe(dane d);

void dopiszprzedWLiscie(lelem_t ** l, dane d);
void dopiszzaWLiscie(lelem_t ** l, dane d);


lelem_t * znajdzWLiscie(lelem_t * lista, dane d);

dane wyjmZListy(lelem_t ** l);

unsigned int dlListy(lelem_t * l);//normalny sposób liczenia dlugosci

int akumulujDlugoscListy_akumulator;//nienormalny sposób liczenia dlugosci listy
int akumulujDlugoscListy(lelem_t * el);
dane mapujFunkcjeNaListe( int(funkcja)(lelem_t *), lelem_t * l );

int piszElementListy(lelem_t * el);

void wypiszListe(lelem_t *l);

#endif /* INTLISTA_H*/

