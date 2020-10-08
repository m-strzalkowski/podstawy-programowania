//author: Mateusz Strzalkowski
#include<stdlib>
#include<stdio.h>

int main()
{
    char nazwisko[100];
    char imie[100];
    scanf("%99s %99s", &imie, &nazwisko);
    printf("<==%s %s==>", nazwisko, imie);

    return 0;
}

