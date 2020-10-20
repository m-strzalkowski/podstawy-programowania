//author: Mateusz Strzalkowski
#include<stdio.h>
#include<stdlib.h>

int main()
{
    const int s_in_m=60;
    const int m_in_h=60;

    int h,m,s;
    scanf("%d %d %d", &h ,&m, &s);
    printf("%d", h*m_in_h*s_in_m + m*s_in_m + s);

    retutn 0;
}


