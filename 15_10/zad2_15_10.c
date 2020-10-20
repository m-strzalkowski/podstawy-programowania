#include<stdio.h>
#include<stdlib.h>

int main()
{
    int a=2, b=7;
    printf("%d %d", a|b||a, (a||b)|a);

    return 0;
}
