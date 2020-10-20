#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    int n;
    printf("ILE LICZB? ");
    scanf("%d", &n);

    float  t;
    float suma=0;

    int j=0;
    petla:
    //for(int j=0; j<n ;j++)
    //{
        printf("\r%f+=", suma);
        scanf("%f", &t);
        suma+=t;
    //}
    if(++j<n){goto petla;};
    printf("suma=%f", suma);
    return 0;
}
