#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "glob.h"
#include "wyjscie.h"

#include "baza.h"

int iloscgrafu=0;
void printlit(lit * tab)
{
    while(tab){printf("%c%c,", (*tab<1)?('-'):(' '), abs(*tab) ); tab++;}
    return;
}

int txt_do_lit(char * tekst, lit * zdanie)
{
    lit * zdkurs=zdanie;
    char * txtkurs=tekst;
    int wewnatrz=0;
    char zn;
    int dodajlit=0, skoncz=0, zanegowany=0, nrlit=0;
    lit nowylit=0;

    while( (zn=*txtkurs) !='\0')
    {

        if(zn=='{')
            {
                if(!wewnatrz)
                {
                    wewnatrz=1;
                    //printf("@%c:", zn);
                    zn=*(++txtkurs);
                }
                else
                {
                    perror("BLAD: NAPOTKANO { WEWNATRZ ZDANIA");
                    exit(3);
                }
            }
        //printf("@%c:", zn);
        if(wewnatrz)
        {
            switch(zn)
            {
                case ' ': break;//ignoruj spacje
                case ',': dodajlit=1; break;//przecinek rozdziela litera³y
                case '}': dodajlit=1; skoncz=1; break;//nawias zamyka zdanie
                case NIE : if(!nrlit){zanegowany=1;}else{perror("BLAD: negacja po literale"); exit(3);} break;//negacja
                default: if(!nrlit){nrlit=zn;}else{perror("BLAD: zmienna wiecej niz jednoznakowa"); exit(3);}break;//ustawienie litera³u
            }
            if(dodajlit)
            {
                //printf("int dodajlit=%d, skoncz=%d, zanegowany=%d, nrlit=%d;",dodajlit, skoncz, zanegowany, nrlit);
                nowylit = ((lit)(nrlit))* ( (zanegowany)?(-1):(1) );
                //printf("#%d", (int)nowylit);
                *(zdkurs++)=nowylit;
                dodajlit=0; zanegowany=0; nrlit=0;
            }
            if(skoncz)
            {
                if(*zdkurs!='\0'){*(zdkurs++)='\0';}
                //printf("#%d", 0);
            }
        }
        txtkurs++;
        //printf("\n");
    }
    //char t[256];
    //lit_do_txt(zdanie,t);
    //printf("%s", t);
    //printlit(zdanie);
    return zdkurs-zdanie;
}

void lit_do_txt(lit * zdanie, char * tekst)
{
    if(!tekst){perror("BLAD:tekst==NULL");exit(3);}
    if(!zdanie){*(tekst++)='?'; *(tekst++)='\0'; return;}
    lit l = *zdanie;
    *(tekst++)='{';
    if(l==0){ *(tekst++)='}';  *(tekst++)='\0';}
    while(1)
    {
        if(l<0){ *(tekst++)=NIE;}
        *(tekst++)=(char)(abs((int)l));
        if( (l=*(++zdanie)) == 0){ *(tekst++)='}';  *(tekst++)='\0'; break;}
        else{*(tekst++)=',';}
    }

        return;
}




int szukajKomplementarnych(wezel * prawy, wezel * lewy, lit * tab)
{
    int ilepar=0;
    for(lit * k1 = prawy->pocz; *k1!=0; k1++)
    {
        for(lit * k2=lewy->pocz; *k2!=0; k2++)
        {
            //printf("\n%d,%d - %c %c", k1-pocz1, k2-pocz2, *k1, *k2);
            if(*k1 == -*k2)
            {
                //printf("tak");
                tab[ilepar]=*k1; //printf("@%c ",tab[ilepar]);
                ilepar++;
                //printf("tak");

            }
        }
    }
    //wartownik
    tab[ilepar]=0;
    return ilepar;
}


int cmpfunc (const void * a, const void * b) {
    int i = *(lit*)a; int j = *(lit*)b;
   return 2* (abs(i)-abs(j) + (i==-j));
}

int zwinpowtorki(lit * pocz, int ilosc)
{

    qsort(pocz, ilosc, sizeof(lit), cmpfunc);

    lit *wsk=pocz;
    lit * ciag=pocz;//ciag tych samych lit, co sie skracaja
    while(wsk-pocz < ilosc)
    {
        //policz litera³y z tymi samymi atomami
        ciag=wsk;
        int dlciagu=0;
        int prosty=0,zanegowany=0;//czy w ciagu powtorzen jest
        lit atom;
        for(atom = abs(*wsk); abs(*wsk) == atom; wsk++)
        {
            if(*wsk < 0){zanegowany=1;}
            if(*wsk > 0){prosty=1;}
            if(*wsk==0){prosty=1; zanegowany=1;/*exit(44);*/}//z matki obcej, krew jego dawne bohatery a imie jego CZTERDZIESCI I CZTERY
            dlciagu++;
        }


        if(prosty && zanegowany){*ciag = -atom; *(ciag+1)= +atom; dlciagu-=2;}
        else{
                if(zanegowany){*ciag= -atom; dlciagu--;}
                if(prosty){*ciag= +atom; dlciagu--;}
        }


        //dlciagu jako dlugosc o jaka nalezy przesunac reszte tablicy w lewo, np:
        //0 1 2 3 4 5 6
        //a a a a-a b d
        //a         b d
        //^-------^ -trzeba zmniejszyc o 1
        //a-a b
        //a-a b
        //TRZEBA ZOSTAWIC LIT. KOMPLEMENTARNE W JEDNYM ZDANIU (mo¿na by zamiast tego "top")

        for(lit * w = wsk; *w!=0; w++)
        {
            *(w-dlciagu)=*w;
        }
        wsk-=dlciagu;
        ilosc-=dlciagu;
        pocz[ilosc]=0;
        //lit_do_txt(pocz, t);printf(" %s, (%d <> %d)",t, wsk-pocz, ilosc);
    }
    return ilosc;
}

//DODAJ ZDANIE - ALGORYTM

    //ALOKACJA OBSZARU DANYCH
    //PRZEPISYWANIE DANYCH Z LEWEGO I PRAWEGO (bez usuwanego)
    //ZWIJANIE POWTORZEN
    //ZAPELNIANIE STRUKTURY (WEZLA - nwezel)
    //SPRAWDZANIE, CZY POWTARZA SIE NOWE ZDANIE
        //JESLI TAK - WARUNEK KONCA REKURENCJI
    //WYPISANIE NA WYJSCIE WYGENEROWANEGO ZDANIA

    //^(wyzej) wpisanie zadanego zdania
    //________________________________________
    //v(nizej) generacja zdan pochodnych

    //DLA KAZDEGO Z RESZTY ZDAN:
        //ZNAJDOWANIE LISTY LIT. KOMPLEMENTARNYCH Z DANYM ZDANIEM
            //DLA KAZDEJ PARY ZE ZNALEZIONYCH ZE ZNALEZIONYCH:
                //WYWO£ANIE REKURENCYJNECH ZE ZNALEZIONYCH:
                //WYWO£ANIE REKURENCYJNE
//argumenty:
//              nowy wezel         prawy rodzic   lewy rodzic  niezanegowany literal ktory trzeba usunac (z LEWEGO) (z prawego negację)
wezel * dodajZd(wezel * nwezel, wezel * rlewy, wezel * rprawy, lit usuwany/*z LEWEGO*/)
{
    DEBUG_PRINT("\n\n____POCZATEK_PRZETWARZANIA[%d]____\n", iloscgrafu);
    DEBUG_PRINT("\nusuwany%c, %c", usuwany, (abs(usuwany)) );
    char t[MALY_BUFOR];//bufor pomocniczy (na tekst)
    int rozmzd=0;//rozmiar zdania

    //ALOKACJA OBSZARU DANYCH
    int maks_rozmzd = (rlewy)?(rlewy->dlugosc-1):(0) + (rprawy)?(rprawy->dlugosc-1):(0);
    if(maks_rozmzd<1){maks_rozmzd=1;}
    // ^ trzeba pamietac aby zostawic miejsce na NULLa na koncu danych ^
    nwezel->pocz = mallocspr((size_t)maks_rozmzd);

    //kursor
    lit * kursor = nwezel->pocz;

    //PRZEPISYWANIE DANYCH Z LEWEGO I PRAWEGO z pominieciem usuwanego
    if(rprawy && rprawy->pocz)
    {
            lit *k= (rprawy->pocz); for(int i=0; k[i]!=0; i++){if((int)k[i] != -(int)usuwany) {*kursor=k[i]; kursor++; } }

    }

    if(rlewy && rlewy->pocz)
    {
            lit *k=(rlewy->pocz); for(int i=0; k[i]!=0; i++){if((int)k[i] != +(int)usuwany) {*kursor=k[i]; kursor++; } }

    }

    if(*(kursor-1)!=0){*kursor=0;}

    rozmzd=kursor- nwezel->pocz;


    //ZWIJANIE POWTORZEN
    rozmzd = zwinpowtorki(nwezel->pocz, rozmzd);

    //wypisanie
    lit_do_txt(nwezel->pocz, t);//DEBUG_PRINT("ZDANIE PO ZWINIECIU: [ %s ]\n",t);
    //ZAPELNIANIE STRUKTURY (WEZLA - nwezel)
    if(rlewy && rprawy && rlewy->pocz && rprawy->pocz)
    {

        nwezel->lewy = rlewy;
        nwezel->prawy = rprawy;
    }
    else{

        nwezel->lewy = NULL;
        nwezel->prawy = NULL;
    }

    nwezel->dlugosc = rozmzd;
    nwezel->usuniety = usuwany;


    //SPRAWDZANIE, CZY POWTARZA SIE NOWE ZDANIE
    int lnum, rnum;
    for(int i=0; i<iloscgrafu; i++ )
    {

        int to_samo = !strcmp((char *)(graf[i].pocz),(char *)(nwezel->pocz) );

        //WARUNEK KONCA REKURENCJI
        if(to_samo)
        {

            lit_do_txt(graf[i].pocz, t);DEBUG_PRINT("%s ",t);
            lit_do_txt(nwezel->pocz, t);DEBUG_PRINT("%s\n",t);

            free(nwezel->pocz);
            nwezel->pocz=NULL;
            //de facto igoruje wszystko zrobione wczesniej...
            //KONIEC REKURENCJI
            return nwezel;//nic juz nie trzeba robic
        }

    }
        iloscgrafu++;

    //WYPISANIE NA WYJSCIE

    //PISZ_ZDANIE(nwezel, nwezel-graf, nwezel->lewy - graf, nwezel->prawy - graf);
    if(nwezel->lewy){lnum= nwezel->lewy -graf+1;}else{lnum=0;}
    if(nwezel->prawy){rnum= nwezel->prawy -graf+1;}else{rnum=0;}
    PISZ_ZDANIE(nwezel, nwezel-graf+1, lnum, rnum);

    //^(wyzej) wpisanie zadanego zdania
    //________________________________________
    //v(nizej) generacja zdan pochodnych

    //DLA KAZDEGO Z RESZTY ZDAN:
    lit komptab[MAX_LICZBA_LITERALOW];
    komptab[0]=0;
    for(int i=0; i<iloscgrafu-1;i++)
    {
        //ZNAJDOWANIE LISTY LIT. KOMPLEMENTARNYCH Z DANYM ZDANIEM
        int czyGeneruje = szukajKomplementarnych(nwezel, graf+i, komptab);
        DEBUG_PRINT("\n%d GENERUJE dla %d", czyGeneruje, i);
        //DLA KAZDEJ PARY ZE ZNALEZIONYCH:
        for(int j=0; komptab[j]!=0; j++)
        {
         //WYWOŁANIE REKURENCYJNE
         //
         DEBUG_PRINT("\ndodajZd(iloscgrafu=%d, nwezel, i=%d, komptab[j=%d]=%c);", iloscgrafu, i, j, komptab[j]);
         dodajZd(graf+iloscgrafu, nwezel, graf+i, komptab[j]);
         DEBUG_PRINT("\nKONIEC %d\n", nwezel-graf);//pisz_graf();putchar('\n');
        }
    }
    return 0;
}


void pisz_graf()
{
    char buf[MALY_BUFOR];

    for(int i=0; i<iloscgrafu; i++)
    {
        lit_do_txt(graf[i].pocz, buf);
        DEBUG_PRINT("\n%d: %s", i, buf);
    }
    DEBUG_PRINT("\n");
}

int czy_to_przeslanka(wezel * z)
{
    if( (!(z->lewy) || !(z->prawy) ) || z->pocz==NULL)
    return 1;
    else return 0;
}
