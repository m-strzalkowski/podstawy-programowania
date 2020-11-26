#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>
void ZamianaMagiczna(int *x, int *y)
{
  if (x != y)
  {
    *x ^= *y;
    *y ^= *x;
    *x ^= *y;
  }
}
//2p

int accumulate(int * begin, int *end)
{

    int accumulator;
    for(int * curs=begin; curs<=end; curs++)
    {
        accumulator+=*curs;
    }
    return accumulator;
}
//2p
//1p - pyt.z aktywnosci

IdontCareWhatIReallyGotIShallIncrementIt(void * adr)
{
    int * ptr = adr;
    (*ptr)++;
}

int abominacja()
{
    int a,b,c=0;
    printf("a=%d b=%d c=%d\n", a,b,c);
    startlabel:
    c=7;
    c++;
    a=2;
    a++;
    b=a+c;
    //return a+b+c;
     printf("a=%d b=%d c=%d\n", a,b,c);
     printf("\nroznica miedzy etykietami %d\n", (int)(&&endlabel-&&startlabel));
     void * ptr = &&startlabel;
     //ptr+=sizeof(char)*64;
     if(b<100){goto *ptr;}
     printf("a=%d b=%d c=%d\n", a,b,c);
    endlabel:
    return 0;
}


main()
{

    int x=7; int y=9;
    int * px=&x; int *py=&y;
    printf("%d, %d\n", *px, *py);
    ZamianaMagiczna(px,py);
    printf("%d, %d\n", *px, *py);
    int t[]={1,2,3,-4};
    printf("\nAkumulator:%d", accumulate(t, t+2));
    char tekst[]="Ala ma kota.";
    printf("%s\n", tekst);
    IdontCareWhatIReallyGotIShallIncrementIt(tekst);
    printf("%s\n", tekst);
}
