#ifndef BAZA_H
#define BAZA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//#include "wyjscie.h"

#define MAX_LICZBA_LITERALOW 127//maksymalna bo signed char
#define MALY_BUFOR 4096
#define DUZY_BUFOR 32768

#define NIE '-'

typedef signed char literal;
typedef signed char lit;

typedef struct wezel{
    lit * pocz;//pocz±tek obszaru danych
    struct wezel * lewy;//wska¼nik na lewego rodzica
    struct wezel * prawy;//wska¼nik na prawego rodzica (je¶li istnieje)
    unsigned char dlugosc;//dlugosc i tak nie przekroczy 254
    lit usuniety;//usuniêty w wyniku rezolucji rodziców litera³ komplementarny
}wezel;
//TABLICA ZACHOWUJĄCA STRUKTURĘ ZDAŃ
wezel graf[DUZY_BUFOR];
extern int iloscgrafu;

void printlit(lit * tab);

//dwie funkcje konwertujące
int txt_do_lit(char * tekst, lit * zdanie);

void lit_do_txt(lit * zdanie, char * tekst);

int szukajKomplementarnych(wezel * prawy, wezel * lewy, lit * tab);

int zwinpowtorki(lit * pocz, int ilosc);

wezel * dodajZd(wezel * nwezel, wezel * rlewy, wezel * rprawy, lit usuwany);

void pisz_graf();

int czy_to_przeslanka(wezel * z);

#endif // BAZA_H
