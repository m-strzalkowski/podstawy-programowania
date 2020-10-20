#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main()
{
    float a,b,c,d;
    scanf("%f %f %f", &a, &b, &c);
    d=sqrt(b*b-4*a*c);
    printf("x1=%f x2=%f", (-b-d)/(2*a),(-b+d)/(2*a));
    return 0;
}
