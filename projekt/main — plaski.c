#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_LICZBA_LITERALOW 127//maksymalna bo signed char
#define MALY_BUFOR 4096
#define DUZY_BUFOR 32768

#define NIE '-'

typedef signed char literal;
typedef signed char lit;

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
                    printf("BLAD: NAPOTKANO { WEWNATRZ ZDANIA");
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
                *(zdkurs++)='\0';
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
//znajduje wszystkie pary literalow komplementarnych miedzy dwoma zdaniami i wpisuje ich adresy do dwoch tablic
int czyParaGeneruje(lit * pocz1, lit ** kompl1, lit * pocz2, lit ** kompl2)
{
    //printf("\nczy:%p %p", pocz1,pocz2);
    int ilepar=0;
    for(lit * k1 = pocz1; *k1!=0; k1++)
    {
        for(lit * k2=pocz2; *k2!=0; k2++)
        {
            //printf("\n%d,%d - %c %c", k1-pocz1, k2-pocz2, *k1, *k2);
            if(*k1 == -*k2)
            {
                //printf("tak");
                kompl1[ilepar]=k1; //printf("@%c",(char)(abs((int)*k1)));
                kompl2[ilepar]=k2; //printf(" %c",(char)(abs((int)*k2)));
                ilepar++;
                //printf("tak");

            }
        }
    }
    //wartowniki
    kompl1[ilepar]=NULL;
    kompl2[ilepar]=NULL;
    return ilepar;
}

int cmpfunc (const void * a, const void * b) {
    int i = *(lit*)a; int j = *(lit*)b;
   return 2* (abs(i)-abs(j) + (i==-j));
}

int zwinpowtorki(lit * pocz, int ilosc)
{
    //printf("\nilosc:%d",ilosc);
    //char t[MALY_BUFOR];
    //lit_do_txt(pocz, t);printf("%s",t);
    qsort(pocz, ilosc, sizeof(lit), cmpfunc);
    //lit_do_txt(pocz, t);printf("%s",t);
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
            if(*wsk==0){exit(44);}//z matki obcej, krew jego dawne bohatery a imie jego CZTERDZIESCI I CZTERY
            dlciagu++;
        }


        if(prosty && zanegowany){*ciag = -atom; *(ciag+1)= +atom; dlciagu-=2;}
        else{
                if(zanegowany){*ciag= -atom; dlciagu--;}
                if(prosty){*ciag= +atom; dlciagu--;}
        }
        //printf("\nlicznik: %c x %d %d", *ciag, licznik, dlciagu);

        //dlciagu jako dlugosc o jaka nalezy przesunac reszte tablicy w lewo, np:
        //0 1 2 3 4 5 6
        //a a a a-a b d
        //a         b d
        //^-------^ -trzeba zmniejszyc o 1
        //a-a b
        //a-a b
        //TRZEBA ZOSTAWIC LIT. KOMPLEMENTARNE W JEDNYM ZDANIU (mo¿na by zamiast tego "top")
        //printf("<-");
        for(lit * w = wsk; *w!=0; w++)
        {
            *(w-dlciagu)=*w; //printf("%c", *w);
        }
        wsk-=dlciagu;
        ilosc-=dlciagu;
        pocz[ilosc]=0;
        //lit_do_txt(pocz, t);printf(" %s, (%d <> %d)",t, wsk-pocz, ilosc);
    }
    return ilosc;
}

lit pam[DUZY_BUFOR];
lit * pampoz=pam;//koniec danych w pamieci glownej (globalny)
int liczbazdan=0;

//              miejsce docelowe,pocz±teki obu zdañ i miejsca wytêpowania litera³ów komplementarnych
lit * dodajZdanie(lit * gdzie, lit * pocz1, lit * kompl1, lit * pocz2, lit * kompl2)
{
    printf("\n"); for(int i=0, j=(gdzie-pam)*3; i<=j;i++ ){printf(" ");} printf("!\n");
    char t[MALY_BUFOR];

    int rozmzd=0;//rozmiar zdania
    lit * kursor=gdzie;
    //wpisz pierwsze zdanie bez litera³u komplementarnego
    if(pocz1)
    {
            for(lit * k=pocz1; *k!=0;k++){if(k!=kompl1){*(kursor++) = *k; rozmzd++;} }
    }
    //wpisz drugie zdanie bez litera³u komplementarnego
    if(pocz2)
    {
        for(lit * k=pocz2; *k!=0;k++){if(k!=kompl2){*(kursor++) = *k;rozmzd++;} }
    }
    *(++kursor)=0;
    rozmzd = zwinpowtorki(gdzie, rozmzd);
    //zrzut(pam,16);

    //przesuniecie globalnego wskaznika na koniec danych w glownym skladowisku
    pampoz+=rozmzd+1;
    printf("\n"); for(int i=0, j=(pampoz-pam)*3; i<=j;i++ ){printf(" ");} printf("$\n");
    printf("rozmzd=%d\n", rozmzd);


    //SPRAWDZ CZY NIE WYGENEROWALO SIE ZDANIE JUZ ISTNIEJACE
    for(lit * wsk=pam; wsk < gdzie; )
    {
        lit * kompl1=NULL, *kompl2 = NULL;

        int to_samo = !strcmp((char *)wsk,(char *)gdzie);

        if(to_samo)
        {
            printf("powtorka:");
            printf("\n"); for(int i=0, j=(wsk-pam)*3; i<=j;i++ ){printf(" ");} printf("#");
            printf("\n"); for(int i=0, j=(gdzie-pam)*3; i<=j;i++ ){printf(" ");} printf("#");
            lit_do_txt(wsk, t);printf("%s ",t);
            lit_do_txt(gdzie, t);printf("%s\n",t);
            pampoz=gdzie;//de facto igoruje wszystko zrobione wczesniej...
            return gdzie;//nic juz nie trzeba robic
        }
        printf("%p\t", wsk);
        for(;wsk<gdzie && *wsk!=0; wsk++){;} wsk++;//przesun sie do nastepnego
        if(*wsk==0)wsk++;//zdanie - nil

    }
    //zwieksz licznik zdan i wypisz
    ++liczbazdan;
    //lit_do_txt(gdzie, t);printf("[%d]- >%s\n",liczbazdan, t);
    lit_do_txt(gdzie, t);printf("%d: %s",liczbazdan, t);//samo zdanie

    lit_do_txt(pocz1, t);printf(" <- %s", t);
    lit_do_txt(pocz2, t);printf(",%s ",t);
    printf("\n");
    //SPRAWDZ CZY TO ZDANIE W KONIUNKCJI Z KAZDYM WCZESNIEJSZYM GENERUJE NOWE
    lit * komptab1[MAX_LICZBA_LITERALOW]; lit * komptab2[MAX_LICZBA_LITERALOW];//tablice wskaznikow
    komptab1[0]=NULL; komptab2[0]=NULL;

    for(lit * wsk=pam; wsk < gdzie; )
    {

        int generuje = czyParaGeneruje(wsk, komptab1, gdzie, komptab2);
        printf("\n@\n");
        zrzut(pam,32);
        printf("\n"); for(int i=0, j=(wsk-pam)*3; i<=j;i++ ){printf(" ");} printf("^");
        printf("\n"); for(int i=0, j=(gdzie-pam)*3; i<=j;i++ ){printf(" ");} printf("^");
        printf("\n");
        if(generuje){printf("   GENERUJE");} else{printf("NIE GENERUJE");}
        for(int i=0; komptab1[i]!=NULL; i++) {printf("%c%c,", (*komptab1[i]<1)?('-'):(' '), abs(*komptab1[i]) ); }
        for(int i=0; komptab2[i]!=NULL; i++) {printf("%c%c,", (*komptab2[i]<1)?('-'):(' '), abs(*komptab2[i]) ); }printf("\n");
        printf("\n");

        //printf("\nczygeneruje:%d,| %c vs %c\n", wsk, generuje, (kompl1)?(*kompl1):('0'), (kompl1)?(*kompl2):('0'));

        if(generuje)
        {
            //DLA KAZDEJ ZNALEZIONEJ PARY
            for(int i=0; komptab1[i]!=NULL; i++)
            {
                    gdzie = dodajZdanie(pampoz, wsk, komptab1[i], gdzie, komptab2[i]);// printf("\n\n\n"); //getch();
            }
            //dodajZdanie(pampoz, wsk, komptab1[0], gdzie, komptab2[0]);// printf("\n\n\n"); //getch();
        }

        for(;wsk<gdzie && *wsk!=0; wsk++){;} wsk++;//przesun sie do nastepnego

    }
    return gdzie;
    //dodajZdanie()

}
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


//OPCJE (PRZELACZNIKI)
int we_z_pliku=0;
int wy_do_pliku=0;

int ludzki_format=0;
int drzewo=0;

int main(int argc, char *argv[])
{
    //OBSLUGA ARGUMENTOW
    int argind=0;//indeks/licznik
    char * nazwawe=NULL;
    char * nazwawy=NULL;
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
            if(strcmp(argv[argind], "do")==0 )
            {
                argind++;
                if(! (argind<argc) ) //nie ma po tym nazwy pliku
                {
                    perror("BLEDNE ARGUMENTY: brak nazwy za 'do' Zobacz --help\n");
                    exit(4);
                }
                else
                {
                    nazwawy = argv[argind];
                    wy_do_pliku=1;
                    printf("plik wyjsciowy: %s\n", nazwawy);
                    continue;
                }
            }

            //PLIK WEJSCIOWY
            if(strcmp(argv[argind], "z")==0 )
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
                    printf("plik wejsciowy: %s\n", nazwawe);
                    continue;
                }
            }

            if(argv[argind][0]=='-')
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

    char t[MALY_BUFOR];


    //lit * poz1 = pam+txt_do_lit("{p,q}",pam); lit_do_txt(pam, t); printf("%s\n", t);
    char buftxt[MALY_BUFOR];//jedna linia
    lit buflit[MALY_BUFOR];//jedno zdanie
    int dlwej=0;
    //dlwej = txt_do_lit("{p,q}",bufwej);
    //dodajZdanie(pampoz, bufwej, 0, 0,0);


    if(!we_z_pliku)
    {
        printf(">");
        while(scanf("%[^\n]%*c", buftxt))
        {
            //printf("%s", buftxt);
            dlwej = txt_do_lit(buftxt,buflit);
            dodajZdanie(pampoz, buflit, 0, 0,0);
            printf("\n>");
        }
        return 0;
    }
    dlwej = txt_do_lit("{p}",buflit);
    dodajZdanie(pampoz, buflit, 0, 0,0);

    dlwej = txt_do_lit("{-p}",buflit);
    dodajZdanie(pampoz, buflit, 0, 0,0);

    return 0;
}
