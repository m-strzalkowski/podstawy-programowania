//W TYM PLIKU SIEDZI MEHCANIZM SZUKANIA (DOWODZENIA)
#ifndef SZUKANIE_H
#define SZUKANIE_H

#include "glob.h"
#include "wyjscie.h"
#include "baza.h"

typedef struct kolejkowicz{
    wezel * wez;
    struct kolejkowicz * lewy;//rodzic
    struct kolejkowicz * prawy;

    struct kolejkowicz * nastepny;
    struct kolejkowicz * poprzedni;

    int nr;
}kolejkowicz;

typedef struct kolejka{
    kolejkowicz * pierwszy;
    kolejkowicz * ostatni;
    kolejkowicz * kurs;
    int wielkosc;
}kolejka;

typedef enum {
    jak_leci,
    wystepujace_na_poczatku,
    wszystkie_na_poczatku
}Przeslanki_w_dowodzie;
extern Przeslanki_w_dowodzie przeslanki_w_dowodzie;


int szukaj_dowodu_na(wezel * szukane, wezel * graf, int wielkosc_grafu);

#endif // SZUKANIE_H

