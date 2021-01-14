#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "glob.h"
#include "wyjscie.h"
#include "baza.h"

#include "szukanie.h"

#define PODST_REPR_NIE_ZNALEZIONO_ZDANIA "NIE ZNALEZIONO ZDANIA"
char * reprezentacja_nie_znaleziono_zdania = PODST_REPR_NIE_ZNALEZIONO_ZDANIA;

Przeslanki_w_dowodzie przeslanki_w_dowodzie;

kolejka * nowa_kolejka()
{
    kolejka * klk = mallocspr(sizeof(kolejka));
    klk->ostatni=NULL;
    klk->pierwszy=NULL;
    klk->wielkosc=0;
    return klk;
}
kolejkowicz * nowy_kolejkowicz(wezel * wz, kolejkowicz ** retro)
{
    kolejkowicz * k = mallocspr(sizeof(kolejkowicz));
    k->nastepny=NULL;
    k->poprzedni=NULL;
    k->nr=0;
    k->wez=wz;
    return k;
}

int zniszcz_kolejke_z_kolejkowiczami(kolejka * klk)
{
    int i=0;
    for(kolejkowicz * kursor=klk->pierwszy; kursor!=klk->ostatni && kursor->nastepny!=NULL; kursor=kursor->nastepny, i++)
    {
            free(kursor);
    }
    free(klk);
    return 0;
}
//kolejka
//ostatni ... nastepny (ten ) poprzedni ... pierwszy
int dodaj_do_kolejki(kolejka * klk, kolejkowicz * elm)
{
    if(klk==NULL){perror("NIE MA TAKIEJ KOLEJKI"); exit(41);}
    if(klk->ostatni) {klk->ostatni->nastepny=elm;}
    else {klk->pierwszy=elm;}
    elm->poprzedni=klk->ostatni;
    elm->nastepny=NULL;
    klk->ostatni=elm;
    klk->wielkosc++;
    return 1;
}
kolejkowicz * zdejm_z_kolejki(kolejka * klk)
{
    if(klk==NULL){perror("NIE MA TAKIEJ KOLEJKI"); exit(41);}
    //printf("ZDEJM Z KOLEJKI");
    if(!klk->pierwszy){printf("KOLEJKA JUZ BYLA PUSTA");return NULL;}
    kolejkowicz * wyrzucany = klk->pierwszy;
    kolejkowicz * drugi = klk->pierwszy->nastepny;//moze byc NULL
    if(drugi)
    {
        drugi->poprzedni=NULL;
    }
    klk->pierwszy=drugi;
    wyrzucany->nastepny=NULL;
    wyrzucany->poprzedni=NULL;
    klk->wielkosc--;
    //printf("wielkosc po usunieciu :%d", klk->wielkosc);
    return wyrzucany;
}
kolejkowicz * wytnij_z_kolejki(kolejka * klk, kolejkowicz * elm)
{

    if(!elm->poprzedni && elm->nastepny)//przod
    {
        elm->nastepny->poprzedni=NULL;
        klk->pierwszy=elm->nastepny;
    }
    if(elm->poprzedni && !elm->nastepny)
    {
        elm->poprzedni->nastepny=NULL;
        klk->ostatni = elm->poprzedni;
    }
    if(elm->poprzedni && elm->nastepny)
    {
        elm->nastepny->poprzedni= elm->poprzedni;
        elm->poprzedni->nastepny = elm->nastepny;
    }

    elm->nastepny=NULL;
    elm->poprzedni=NULL;

    klk->wielkosc--;
    return elm;
}
void zamien(kolejkowicz ** a, kolejkowicz ** b)
{
    kolejkowicz * t=*a;
    *a=*b;
    *b=t;
}
void odwroc_kolejke(kolejka * klk)
{
    if(!klk->pierwszy || !klk->ostatni){return;}
    int i=0;
    kolejkowicz * wyjety;
    kolejkowicz * stary_ostatni = klk->ostatni;
    while(stary_ostatni->poprzedni!=NULL)
    {
        wyjety = wytnij_z_kolejki(klk, stary_ostatni->poprzedni);
        //printf("\npo wycieciu:");wypisz_kolejke(klk);
        //printf("\nwycieto %p", wyjety);
        dodaj_do_kolejki(klk, wyjety);
        //printf("\npo dodaniu:");wypisz_kolejke(klk);
    }

}
void polacz_kolejki(kolejka * tylna, kolejka * przednia)
{
    if(przednia->wielkosc==0)
    {
        przednia->pierwszy=tylna->pierwszy;
        przednia->ostatni=tylna->ostatni;
        return;
    }
    if(tylna->wielkosc==0)
    {
        tylna->pierwszy=przednia->pierwszy;
        tylna->ostatni=przednia->ostatni;
        return;
    }
    //powiązanie elementów
    tylna->pierwszy->poprzedni = przednia->ostatni;
    przednia->ostatni->nastepny = tylna->pierwszy;
    //powiązanie struktur kolejek
    tylna->pierwszy = przednia->pierwszy;
    przednia->ostatni = tylna->ostatni;
}

void wypisz_kolejke(kolejka * klk)
{
    int i=0;
    DEBUG_PRINT("( ");

    DEBUG_PRINT("[pierwszy: poprz: ten:%p nast:] ",  klk->pierwszy );
    for(kolejkowicz * kursor=klk->pierwszy; kursor!=NULL; kursor=kursor->nastepny, i++)
    {
            char t[MALY_BUFOR];
            lit_do_txt(kursor->wez->pocz, t); DEBUG_PRINT("[%d:%s poprz:%p ten:%p nast:%p] ", i, t, kursor->poprzedni, kursor, kursor->nastepny);
            if(kursor->nastepny==NULL && kursor!=klk->ostatni){DEBUG_PRINT(" ZEPSUTA KOLEJKA - NULL przed koncem )"); break;}
    }

     DEBUG_PRINT("[ostatni: poprz:%p ten:%p nast:%p] ",  klk->ostatni);
    DEBUG_PRINT(" )\n");
}

kolejka * lista_wszystkich_przeslanek(wezel * graf, int wielkosc_grafu, kolejkowicz ** retro, wezel * szukane)
{
    DEBUG_PRINT("\nlista_wszystkich_przeslanek\n");
    if(szukane==NULL){WYJSCIE("KB=\n");}
    kolejka * przesl = nowa_kolejka();

    kolejkowicz * nowy=NULL;
    for(int i=0; i<wielkosc_grafu; i++)
    {
        if(czy_to_przeslanka(&graf[i]) || szukane==NULL)
        {
            nowy = nowy_kolejkowicz(&graf[i], retro);
            dodaj_do_kolejki(przesl, nowy);
            retro[i]=nowy;
            DEBUG_PRINT("dodano [%d] element do przesl \n", i);
        }
    }
    DEBUG_PRINT("wypisywanie kolejki:\n");
    wypisz_kolejke(przesl);
    return przesl;
}

kolejka * podst_lista_z_BFS(wezel * korzen, wezel * graf, int wielkosc_grafu, kolejkowicz ** retro)
{
    kolejka * dowod = nowa_kolejka();
    kolejka * robocza = nowa_kolejka();
    DEBUG_PRINT("\npoczatek BFS\n");
    if(!korzen){DEBUG_PRINT("BFS nic nie robi\n"); free(robocza); return dowod;}

    dodaj_do_kolejki(robocza, nowy_kolejkowicz(korzen, retro));

    while(robocza->wielkosc>0)
    {
        if(!czy_to_przeslanka(robocza->pierwszy->wez)) //czyli de facto liść drzewa binarnego
        {
            wezel * rlewy = robocza->pierwszy->wez->lewy;
            wezel * rprawy = robocza->pierwszy->wez->prawy;

            dodaj_do_kolejki(robocza, nowy_kolejkowicz(rlewy, retro) );
            dodaj_do_kolejki(robocza, nowy_kolejkowicz(rprawy, retro) );
        }

        wypisz_kolejke(robocza);
        kolejkowicz * zdejmowany = zdejm_z_kolejki(robocza);DEBUG_PRINT("\nzdejm, wielkosc=%d\n", robocza->wielkosc);
        DEBUG_PRINT("retro[%d] :", (zdejmowany->wez) - graf);
        DEBUG_PRINT("%p\n", retro[ (zdejmowany->wez) - graf]);
        if(retro[ (zdejmowany->wez) - graf]==NULL)
        {
            DEBUG_PRINT("DODAJ DO DOWODU");
            dodaj_do_kolejki(dowod, zdejmowany);

            DEBUG_PRINT("\nINDEKS:%d \n", zdejmowany->wez - graf);
            retro[zdejmowany->wez - graf]=zdejmowany;
            pisz_retro(retro, 30);
        }

        //zdejm_z_kolejki(robocza);

        wypisz_kolejke(robocza);
        wypisz_kolejke(dowod);
        DEBUG_PRINT("\n");
    }
    DEBUG_PRINT("pre-dowod: "); wypisz_kolejke(dowod);
    odwroc_kolejke(dowod);
    DEBUG_PRINT("\ndowod: "); wypisz_kolejke(dowod);
    return dowod;
}

void przesl_na_pocz(kolejka * klk)
{
    kolejka * przesl = nowa_kolejka();
    int i=0;
    kolejkowicz * t;
    for(kolejkowicz * kursor=klk->pierwszy; kursor!=klk->ostatni && kursor->nastepny!=NULL; i++)
    {
        t=kursor;
        kursor=kursor->nastepny;
        if(czy_to_przeslanka(t->wez))
        {
            wytnij_z_kolejki(klk, t);
            dodaj_do_kolejki(przesl, t);
        }
    }
    polacz_kolejki(klk, przesl);
    free(przesl);
    //printf("OK");
}

void pisz_retro(kolejkowicz ** retro, int n)
{
    DEBUG_PRINT("\nretro:\n")
    for(int i=0; i<n; i++)
    {
        DEBUG_PRINT("%d:%p\t", i, retro[i]);
    }
    DEBUG_PRINT("\n");
}

int szukaj_dowodu_na(wezel * szukane, wezel * graf, int wielkosc_grafu)
{
    wezel * korzen=NULL;
    char t[MALY_BUFOR];
    if(szukane){DEBUG_PRINT("\nSZUKANIE DOWODU: %p %p\n",szukane,graf);}
    else{DEBUG_PRINT("\nWYPISYWANIE BAZY WIEDZY:\n");}
    if( !graf )
    {
        perror("graf==null w dowodzeniu");
        exit(31);
    }

    if(szukane)
    {
        DEBUG_PRINT("strlen(szukane)=%d", strlen(szukane->pocz));
        zwinpowtorki(szukane->pocz, strlen(szukane->pocz));
        lit_do_txt(szukane->pocz, t); DEBUG_PRINT("szukane zwiniete:%s\n", t);//samo zdanie
        for(int i=0; graf[i].pocz!=NULL ;i++)
        {

                if(strcmp((char *)szukane->pocz, (char *)graf[i].pocz)==0)
                {korzen=&graf[i]; break;}
        }
        if(!korzen)
        {
            WYJSCIE(reprezentacja_nie_znaleziono_zdania);
            lit_do_txt(szukane->pocz, t); WYJSCIE(" %s\n", t);
            return 0;
        }

        lit_do_txt(korzen->pocz, t); WYJSCIE("DOWOD NA %s:\n", t);//samo zdanie

    }



    //trzeba zapewnic dwustronną relację między generowanym drzewem wywodu a całą bazą wiedzy (graf)
    //w generowanej kolejce sa relacje w jedną stronę, a tu w drugą (stąd retro)

    kolejkowicz * retro[wielkosc_grafu+10];
    for(int i=0; i<wielkosc_grafu; i++){retro[i]=NULL;}
    pisz_retro(retro, wielkosc_grafu);
    //szukanie
    kolejka * przesl;
    if(przeslanki_w_dowodzie == wszystkie_na_poczatku)
    {

        przesl = lista_wszystkich_przeslanek(graf, wielkosc_grafu, retro, szukane);
        DEBUG_PRINT("\n\nWSZYSTKIE PRZESLANKI:%d\n", przesl->wielkosc);
        wypisz_kolejke(przesl);
    }
    pisz_retro(retro, wielkosc_grafu);

    //podst_lista
    kolejka * dowod = podst_lista_z_BFS(korzen, graf, wielkosc_grafu, retro);

    if(przeslanki_w_dowodzie == wszystkie_na_poczatku)
    {
        //doklej przesl na pozcatku reszty
        polacz_kolejki(dowod, przesl);
    }

    if(przeslanki_w_dowodzie == wystepujace_na_poczatku || (szukane==NULL && przeslanki_w_dowodzie!=jak_leci))
    {
        //wystepujace przeslanki  na poczatek
        przesl_na_pocz(dowod);
    }
    //wypisywanie
    DEBUG_PRINT("\n\nDOWOD:\n");
    wypisz_kolejke(dowod);
    int i=1;
    for(kolejkowicz * kursor=dowod->pierwszy; kursor!=dowod->ostatni && kursor->nastepny!=NULL; kursor=kursor->nastepny, i++)
    {
        kursor->nr=i;
        DEBUG_PRINT("#%d", i);
    }
    pisz_retro(retro, wielkosc_grafu);
    //pisz_graf();

    //lit_do_txt(korzen->pocz, t); WYJSCIE("\ndowod na %s:\n", t);//samo zdanie
    for(kolejkowicz * kursor=dowod->pierwszy; kursor!=NULL; kursor=kursor->nastepny)
    {
        //kursor->wez
        //printf("\nZD:");printf("(%d %d %d)", kursor->nr, (kursor->wez->lewy) , (kursor->wez->prawy) );
        int lnum, rnum;
        //lnum=retro[0]->nr;
        if( (kursor->wez->lewy)==NULL || (kursor->wez->prawy)==NULL )
        {lnum=0; rnum=0;}
        else{
            lnum = retro[(kursor->wez->lewy) - graf]->nr;
            rnum = retro[(kursor->wez->prawy) - graf]->nr;
        }
        PISZ_ZDANIE(kursor->wez, kursor->nr, lnum,rnum);
    }
    //sprzątanie
    //zniszcz_kolejke_z_kolejkowiczami(przesl);

    return 1;
}


