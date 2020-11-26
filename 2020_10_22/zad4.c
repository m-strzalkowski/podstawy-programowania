#include<stdio.h>
#include<stdlib.h>
#include<float.h>
#include<limits.h>
#include<math.h>
#include<ctype.h>

f()
{

}

int main()
{
    const int tsize=4096;
    int c=0;
    char t[tsize];
    int n=0;
    scanf("%s%n", &t, &n);
    for(int i=0; i<n ; i++)
    {
        if(islower(t[i])){c++;}

    }
    printf("\n%d pasujacych liter",c);
    return 0;
}
