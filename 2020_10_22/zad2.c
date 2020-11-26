#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>


int main()
{
    int n; float suma;
    printf("Ile liczb?");
    scanf("%d", &n);
    float * t = malloc(sizeof(float)*n);
    if(t==NULL){exit(1);}
    for(int i=0; i<n ;i++)
    {
        printf("(%d z %d): ",i+1,n);
        scanf("%f", &t[i]);
        suma+=t[i];
    }

    printf("suma: %fsrednia %f", suma, suma/n);
    free(t);
    return 0;
}
