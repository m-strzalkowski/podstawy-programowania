#include<stdio.h>
#include<stdlib.h>

int main()
{
    float a,b,w; char dz;
    scanf("%f %f %c", &a, &b, &dz);

    switch (dz)
    {
        case '+':
          w=a+b;
          break;

        case '-':
          w=a-b;
          break;

        case '*':
          w=a*b;
          break;

        case '/':
          w=a/b;
          break;

    }
    printf("=%f",w);

    return 0;
}
