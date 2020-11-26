#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>
#include<ctype.h>

int samogloska(char zn)
{
    static const char wzor[] = "aeioyu";
    for(int i=0;wzor[i]!='\0';i++)
    {
        if(zn==wzor[i]){return 1;}
    }
    return 0;
}

dodajsylabe(char * pocz, char * kon, char * wy)
{
    char * k = pocz;
    for(char * k = pocz; k<=kon && *k!='\0';k++)
    {
        printf("!%c!", *k);
        *(wy+(k-pocz))=*k;
    }
}

const char * jakala(const char * we)
{
    //printf("%d\n", strlen(we));
    const char * wy = malloc(2*strlen(we));

    char * psyl=we;
    char * ksyl=we;
    char * kurswy=wy;//kursor wyjsciowy
    while(1)
    {
        if(*ksyl==' '){dodajsylabe(psyl, ksyl, kurswy); ksyl++; kurswy++; continue;}
        int s = samogloska(*ksyl); int a = isalpha(*ksyl);
        if()
    }


    /*if(wy==NULL){return NULL;}
    int n=0;
    int licznik=0;
    do
    {
        sscanf(we+licznik,"%s%n", wy, &n);
        printf("!%s!%d\n", wy,n);
        licznik+=n+1;
    }while(n>0);
    */
 //   sscanf(we,"%s%n", wy, &n);
 //   printf("!%d!%d", wy[0],n);
}

int main()
{
    const char * wy = jakala("  Ala ma kota");
    return 0;
}
