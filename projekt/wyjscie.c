#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "baza.h"
#include "wyjscie.h"

#define PODST_REPR_PRZESL "PRZESLANKA"
char * reprezentacja_przeslanki = PODST_REPR_PRZESL;
#define PODST_REPR_NIEISTN "nil"
char * reprezentacja_nieistniejacego = PODST_REPR_NIEISTN;

int we_z_pliku=0;
int wy_do_pliku=0;

FILE * plikwyjsciowy=NULL;
FILE * plikwejsciowy=NULL;

enum typ_akc{nic=0,
                    tekst,
                    nowe, nowe_nr,//%N %n
                    prawe, prawe_nr,//%R %r
                    lewe, lewe_nr,//%L %l
                    przesl_slaba, przesl_mocna};//%P i %p (roznica jest taka, ze %P jesli okaze sie prawda, konczy wypisywanie)

struct akc{
    enum typ_akc typ;
    char * wsk;
};

struct akc tabfmt[64]={{0,NULL}};

void czyscfmt()
{
    for(int i=0; i<64; i++)
    {
        tabfmt[i].typ=0;
        tabfmt[i].wsk=NULL;
    }
}
void piszfmt()
{
    for(int i=0; i<64; i++)
    {
        printf("[%d]: %d %s\n", i, tabfmt[i].typ, (tabfmt[i].typ==tekst && tabfmt[i].wsk!=NULL)?(tabfmt[i].wsk):("nico"));
    }
}

int format_zdan(char * fmt)
{
    czyscfmt();
    int tablen=0;
    char * p=fmt;//poczatek
    char * k=fmt;//koniec (i kursor)
    while(*k!='\0')
    {
        p=k;
        //przesun sie do następnego procenta (lub wartownika)
        while(*k!='%' && *k!='\0'){k++;}
        //tekst
        if(k-p>0)
        {
            //wpisz czesc stringu
            tabfmt[tablen].typ=tekst;
            tabfmt[tablen].wsk=malloc(k-p+1);//dodatkowy bajt na wartownika
            if(tabfmt[tablen].wsk == NULL)
            {
                perror("BLAD ALOKACJI");
                exit(7);
            }
            memcpy(tabfmt[tablen].wsk, p, k-p);
            *(tabfmt[tablen].wsk+(k-p) )='\0';//wartownik
            //printf("%s", tabfmt[tablen].wsk);
            tablen++;
        }
        //format
        if(*k=='%')
        {
            k++;
            switch(*k)
            {
                case 'N': tabfmt[tablen].typ=nowe; break;
                case 'n': tabfmt[tablen].typ=nowe_nr; break;
                case 'L': tabfmt[tablen].typ=lewe; break;
                case 'l': tabfmt[tablen].typ=lewe_nr; break;
                case 'R': tabfmt[tablen].typ=prawe; break;
                case 'r': tabfmt[tablen].typ=prawe_nr; break;
                case 'p': tabfmt[tablen].typ=przesl_slaba; break;
                case 'P': tabfmt[tablen].typ=przesl_mocna; break;
                default:
                    perror("NIEZNANA OPCJA FORMATUJACA ");WYJSCIE("%c", *k);
                    exit(11);
            }
            k++;
            tablen++;
        }

    }
    //piszfmt();
    return 0;
}

//miejsce na tekstowe reprezentacje zdan
char zdn[MALY_BUFOR];
char zdl[MALY_BUFOR];
char zdp[MALY_BUFOR];

static inline void auxprn(wezel * z, char * buf)
{
    if(z && z->pocz)
    {
        lit_do_txt(z->pocz, buf);
        WYJSCIE(buf);
    }
    else WYJSCIE(reprezentacja_nieistniejacego);
}


int PISZ_ZDANIE(wezel * zdanie, int num/*numer*/, int lnum, int rnum)
{
    if(!zdanie){return 0;}
    /*lit_do_txt(nwezel->pocz, t); WYJSCIE("%d: %s",iloscgrafu, t);//samo zdanie
    WYJSCIE(" <- ");
    if(nwezel->lewy){lit_do_txt(rlewy->pocz, t); WYJSCIE("%s", t);}
    else{WYJSCIE(" nil ");}
    if(nwezel->prawy){lit_do_txt(rprawy->pocz, t); WYJSCIE(",%s ",t);}
    else{WYJSCIE(" nil ");}
*/

    //lit_do_txt(zdanie->lewy->pocz, zdl);
    //lit_do_txt(zdanie->prawy->pocz, zdp);
    //jezeli wypisane zostanie pole %P, to dalej nie pisze juz %l %L %r %R
    int byla_przeslanka=0;

    struct akc a;
    for(int i=0; (a=tabfmt[i]).typ!=0;i++)
    {
        //printf("[%d", i);
        if(a.typ==tekst)
        {
            if(a.wsk==NULL){perror("wewnetrznie niespojny format wyjsciowy"); exit(21);}
            else{
                    WYJSCIE("%s", a.wsk);
            }
        }
        if(a.typ==nowe)
        {
            auxprn(zdanie, zdn);
        }
        if(a.typ==nowe_nr)
        {
            WYJSCIE("%d", num);
        }
        if(a.typ==przesl_slaba || a.typ==przesl_mocna)
        {
            if(czy_to_przeslanka(zdanie))
            {
                WYJSCIE(reprezentacja_przeslanki);
                if(a.typ==przesl_mocna) {WYJSCIE("\n");return 0;}
                else byla_przeslanka=1;
            }
        }
        if(!byla_przeslanka)
        {
            if(a.typ==lewe)
            {
                auxprn(zdanie->lewy, zdl);
            }
            if(a.typ==prawe)
            {
                auxprn(zdanie->prawy, zdp);
            }
            if(a.typ==lewe_nr)
            {
                //WYJSCIE("%d", num-(zdanie - (zdanie->lewy)) );
                WYJSCIE("%d", lnum );
            }
            if(a.typ==prawe_nr)
            {
                WYJSCIE("%d", rnum );
            }
        }
        //printf("]");
    }
    WYJSCIE("\n");

    return 0;
}

