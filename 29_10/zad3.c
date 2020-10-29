#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>
#include<ctype.h>
#include<stdarg.h>

typedef int typ;

typ kalkulator(char dzialanie, typ w)
{
    static typ a; //akumulator
    switch (dzialanie)
    {
        case '+':
          a+=w;
          break;

        case '-':
          a-=w;;
          break;

        case '*':
          a*=w;
          break;

        case '/':
          a/=w;
          break;
        case '=':
          a=w;
          break;

    }

    printf("a=%d\n",a);
}

int main()
{

    kalkulator('+', 2);
    kalkulator('-', 3);
    kalkulator('*', 3);
    return 0;
}
