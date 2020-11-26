#include<stdio.h>
#include<stdlib.h>

int main()
{
    float a,b,c;
    scanf("%f %f %f", &a, &b, &c);
    printf("delta:%f", b*b-4*a*c);
    return 0;
}
