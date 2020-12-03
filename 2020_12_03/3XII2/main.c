#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printBinary(long long n)
{
    for(int i=0; i<sizeof(n)*8; i++)
    {
        printf("%d", n%2); n=n>>1;
    }
    printf("\n");
}
void pb2(long long x)
{


    int i=0;
    for (i = (sizeof(int) * 8) - 1; i >= 0; i--)
    {
       putchar(x & (1u << i) ? '1' : '0');
    }
    printf("\n");
}

void zapal(long long)

int main()
{
    printBinary(1+2+4+8+32);
    pb2(1+2+4+8+32);
    return 0;
}
