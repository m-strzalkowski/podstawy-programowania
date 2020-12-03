#ifndef INTLISTA_H
#define INTLISTA_H
typedef int dane;

typedef struct lelem{//listy element
    dane wart;//wartosc
    struct lelem * nast;
}lelem_t;

lelem_t * stworzListe(dane d);

void wsadzWListe(lelem_t ** l, dane d);

dane zdejmZListy(lelem_t ** l);

unsigned int dlListy(lelem_t * l);//normalny sposób liczenia dlugosci

int akumulujDlugoscListy_akumulator;//nienormalny sposób liczenia dlugosci listy
int akumulujDlugoscListy(lelem_t * el);



int piszElementListy(lelem_t * el);

dane mapujFunkcjeNaListe( int(funkcja)(lelem_t *), lelem_t * l );

void wypiszListe(lelem_t *l);

#endif /* INTLISTA_H*/
