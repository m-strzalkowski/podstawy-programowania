#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    char tab[4][20];
    for(int i=0; i<4;i++)
    {
        scanf("%19s", &tab[i]);
    }

    for(int i=0; i<4;i++)
    {
        printf("%19s,", &tab[i]);
    }
    return 0;
}
