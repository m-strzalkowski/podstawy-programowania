#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>
#include<ctype.h>

#include<stdarg.h>

f(const int ile, ...)
{
    va_list args;
    va_start(args, ile);

    /* cos */
    for(int i=0; i<ile; i++)
    {
        int a = va_arg(args, int);
        printf("arg%d:%d\n", i,a);
    }

    va_end(args);
}



int main()
{

    f2(3, 2, 4,5);
    f2(2, 1, 3);
    return 0;
}

