#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>

czy_jest(float * t, int n, float l)
{
     for(int i=0; i<n; i++)
    {
        if( fabs(t[i] - l) < FLT_EPSILON)
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    float t[]={0.1, 0.2,0.3};
    printf("%d",czy_jest(&t, 3, 0.2));
    return 0;
}
