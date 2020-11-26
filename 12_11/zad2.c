#include<stdio.h>
#include<time.h>

//#define LOG(s) printf( "file:" #__FILE__ " line:" #__LINE__ );

#define N 1024

int cmpfunc(const void * a, const void * b)
{
    int arga = *(const int *)a;
    int argb = *(const int *)b;

    if (arga < argb) return -1;
    if (arga > argb) return 1;
    return 0;
}

randcolor()
{
    char chroma[30];
    sprintf(chroma, "color %02x", (int)(rand()%0xff));
    system(chroma);
}

main()
{
    //char chroma[3];
    system("color 70");
    //printf("color %02x", (int)(rand()%0xf));
    int t[N];
    srand(time(NULL));
    //int size = sizeof t / sizeof *t;
    for(int i=0; i<N;i++)
    {
        t[i]=rand()%100;
    }

    qsort(t, N, sizeof(int), cmpfunc);
    for(int i=0; i<N;i++)
    {
        randcolor();
        printf("%d\n", t[i]);
    }
    int key = 7;
    void * ptr = bsearch(&key, t, N, sizeof(int), cmpfunc);
    printf("%p %p %d", t, ptr, *((int *)ptr));


}
