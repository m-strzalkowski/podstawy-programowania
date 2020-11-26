#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>
#include<ctype.h>


int f(const char * dest, const char * src, char bytes)
{
    char * sp = src+bytes-1;
    char * dp = dest;
    for(;sp>=src; --sp, ++dp)
    {
        *dp=*sp;//printf("%c", *sp);
    }
    *dp='\0';
}

int main()
{

    char dest[2048];
    f(dest, "123456789", 9);
    printf("%s", dest);
    return 0;
}
