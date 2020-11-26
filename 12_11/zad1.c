#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>
#include<ctype.h>
#include<time.h>

#define MAXW 1024

#define LOG(str) printf(#str __FILE__ __LINE__);

int ** constrMatrix(int i, int j)
{
    int ** tab  = (int **)malloc(sizeof(int)*i);
    for(int k=0;k<i;k++)
    {
        tab[k] = (int *)malloc(sizeof(int)*j);
    }
    return tab;
}

destrMatrix(int ** t, int i, int j )
{

}

const char * joinWords(const char ** words, int nwords)
{
    const char * output=malloc(1000*sizeof(char));
    printf("%p\n", output);
    char * curs = output;
    printf("%p\n", curs);
    for(int i=0; i<nwords; i++)
    {
        strcat(curs, words[i]);
        printf("%p\n", words[i]);
        printf("%d", strlen(curs));
        printf("%s", curs);
        curs +=strlen(curs);
    }
    return output;
}

main()
{
    free(NULL)
    LOG("cos");
    /*srand(time(NULL));

    char words[MAXW][MAXW];
    int wc=0;
    int nwords;
    printf("ile slow?");
    scanf("%d", &nwords);
    while(wc<nwords )
    {
            scanf("%s", words[wc]);
            printf("%s", words[wc]);
            wc++;

    }
    const char * str = joinWords(words, nwords);
    printf("%s", str);
    */
}
