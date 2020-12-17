#ifndef DRZEWO_H
#define DRZEWO_H

typedef int drzdane;
typedef enum{LEWY,PRAWY}ktorypotomek;
typedef struct drzelem
{
    drzdane wart;//wartosc
    struct drzelem * rodzic;
    struct drzelem * lewy;
    struct drzelem * prawy;
}drzelem;

void dodajdodrzewa(drzelem ** drzewo, ktorypotomek kt);
void usunzdrzewa(drzelem ** wezel);
drzelem * szukajwdrzewie(drzelem * drzewo, drzdane wartosc);

#endif // DRZEWO_H
