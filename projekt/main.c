///////////////////////////
//       REZOLUTOR       //
//rachunku zerowego rzędu//
///////////////////////////

//PLIKI:
//-baza - funkcje budujące bazę wiedzy
//-glob - funkcje pomocnicze i globalne flagi
//-wyjscie - obsługa formatu wyjścia
//-szukanie

//kody wyjscia:
//7 - niepowodzenie alokacji pamieci
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "glob.h"
#include "baza.h"
#include "wyjscie.h"
#include "szukanie.h"
#include "siec.h"


//OPCJE (PRZELACZNIKI)
//int we_z_pliku=0;
//int wy_do_pliku=0;

int ludzki_format=0;
int drzewo=0;

lit pam[DUZY_BUFOR];
lit * pampoz=pam;//koniec danych w pamieci glownej (globalny)
int liczbazdan=0;

void zrzut(lit * w, int n)
{


    for(int i=0; i<n;i++){
            char z= ( (w[i]!=0)?( abs(w[i]) ):('0') ), n=(w[i]<0)?('-'):(' ');
            printf("%c%c ", n,z);
    }
}
void tekst_pomocy()
{
}


int main(int argc, char *argv[])
{
    //OBSLUGA ARGUMENTOW
    int argind=0;//indeks/licznik
    char * nazwawe=NULL;
    char * nazwawy=NULL;
    plikwejsciowy = NULL;//domylsnie
    przeslanki_w_dowodzie = jak_leci;//domyslnie
    if(argc>0)
    {

        for(argind=1; argind<argc; argind++)
        {
            printf("%s ", argv[argind]);
            if(strcmp(argv[argind], "--help")==0 )
            {
               tekst_pomocy();
               exit(0);
            }
            //PLIK WYJSCIOWY
            if(strcmp(argv[argind], "-o")==0 || strcmp(argv[argind], "do")==0)
            {
                argind++;
                if(! (argind<argc) ) //nie ma po tym nazwy pliku
                {
                    perror("BLEDNE ARGUMENTY: brak nazwy za 'do' lub '-o' Zobacz --help\n");
                    exit(4);
                }
                else
                {
                    nazwawy = argv[argind];
                    wy_do_pliku=1;

                    if(!plikwyjsciowy){plikwyjsciowy = fopen(nazwawy, "w");}
                    else{perror("PRÓBA OTWARCIA DWOCH PLIKOW WYJSCIOWYCH"); exit(9);}
                    if(!plikwyjsciowy){perror("blad otwierania pliku"); exit(8);}

                    DEBUG_PRINT("plik wyjsciowy: %s\n", nazwawy);
                    //WYJSCIE("WYJSCIE PROGRAMU REZOLUTOR%f\n", 3.14);
                    //WYJSCIE("DUPAdd%f", 7.14);

                    continue;
                }
            }

            //PLIK WEJSCIOWY
            if(strcmp(argv[argind], "-i")==0 || strcmp(argv[argind], "z")==0 )
            {
                argind++;
                if(! (argind<argc) ) //nie ma po tym nazwy pliku
                {
                    perror("BLEDNE ARGUMENTY: brak nazwy za 'Z' Zobacz --help\n");
                    exit(4);
                }
                else
                {
                    nazwawe = argv[argind];
                    we_z_pliku=1;

                    if(!plikwejsciowy){plikwejsciowy = fopen(nazwawe, "r"); }
                    else{perror("PRÓBA OTWARCIA DWOCH PLIKOW WYJSCIOWYCH"); exit(9);}
                    if(!plikwejsciowy){perror("blad otwierania pliku"); exit(8);}

                    printf("plik wejsciowy: %s\n", nazwawe);
                    continue;
                }
            }
            if(strcmp(argv[argind], "-qai")==0 ){przeslanki_w_dowodzie=jak_leci; DEBUG_PRINT("przeslanki jak leci\n");}
            if(strcmp(argv[argind], "-qrp")==0 ){przeslanki_w_dowodzie=wystepujace_na_poczatku; DEBUG_PRINT("przeslanki wystepujace - na poczatku\n");}
            if(strcmp(argv[argind], "-qap")==0 ){przeslanki_w_dowodzie=wszystkie_na_poczatku; DEBUG_PRINT("przeslanki wszystkie - na poczatku\n");}
            else if(argv[argind][0]=='-')
            {
                char * opcje=argv[argind];
                while(*(++opcje) )
                {
                    switch(*opcje)
                    {
                        case 'h': ludzki_format=1; break;
                        case 't': drzewo=1; break;
                    }
                }
            }
            else
            {
                perror("BLEDNE ARGUMENTY: Zobacz --help\n");exit(4);
            }
        }
    }
    if(!plikwejsciowy){plikwejsciowy=stdin; DEBUG_PRINT("\n wejscie standardowe");}
    if(!plikwyjsciowy){plikwyjsciowy=stdout; DEBUG_PRINT("\n wyjscie standardowe\n");}



    char t[MALY_BUFOR];
    char fmt_zdan_uzytk[MALY_BUFOR];
    char cdz;
    format_zdan("%n: %N <-%P %L , %R (%l i %r)");
    //PISZ_ZDANIE(0,4);
    //PISZ_ZDANIE(0,8);

    //lit * poz1 = pam+txt_do_lit("{p,q}",pam); lit_do_txt(pam, t); printf("%s\n", t);
    char buftxt[MALY_BUFOR];//jedna linia
    lit buflit[MALY_BUFOR];//jedno zdanie
    int dlwej=0;
    wezel wezwej={0,0,0,0,0};

    wezwej.lewy=NULL;
    wezwej.prawy=NULL;
    wezwej.usuniety=0;
    wezwej.pocz=buflit;

    if(1)
    {
        printf("\n>");
        //while(fscanf(plikwejsciowy, "%[^\n]%*c", buftxt))
        while(fgets(buftxt, MALY_BUFOR, plikwejsciowy))
        {
        if(buftxt[0]=='q'){break;}
        dlwej = txt_do_lit(buftxt,buflit);
        wezwej.dlugosc = dlwej;
        if(buftxt[0]=='?' && buftxt[1]!='\0')
        {
            printf("..." );
            szukaj_dowodu_na(&wezwej, graf, iloscgrafu);
            printf("\n>");
            continue;//???????
            //goto k_ciala_petli;
        }
        if(buftxt[0]=='@')
        {
            DEBUG_PRINT("\nnapotkano @");
            szukaj_dowodu_na(NULL, graf, iloscgrafu);
            printf("\n>");
            continue;//???????
            //goto k_ciala_petli;
        }
        if(sscanf(buftxt, "$fmt=\"%[^\"]s\"", fmt_zdan_uzytk, &cdz))
        {
            DEBUG_PRINT("zmiana formatu zdań na '%s'\n", fmt_zdan_uzytk);
            format_zdan(fmt_zdan_uzytk);
            printf("\n>");
            continue;
        }

        //printf("dlwej:%d\n", dlwej);
        //printf("dodajZd(&graf[%d], %p, %d, %d);",iloscgrafu, &wezwej, NULL, 0);
        if(strlen(buftxt)>1)
        {
            dodajZd(&graf[iloscgrafu], &wezwej, NULL, 0);
        }
            //printf("%s", buftxt);
            //dlwej = txt_do_lit(buftxt,buflit);

            //dodajZdanie(pampoz, buflit, 0, 0,0);
            //printf("\n>");
            printf("\n>");
        }
        //pisz_graf();
        k_ciala_petli:
        return 0;
    }

    return 0;
}
