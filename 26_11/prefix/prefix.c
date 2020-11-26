#include <stdio.h>
#include <string.h>
#include<stdlib.h>

//$1 - prefix
//reszta - lista plikow
int main(int argc, char *argv[])
{
    
    char nowanazwa[512];
    if(argc<3)
    {
        perror("zle argumenty. zobacz kod zrodlowy\n");
        exit(-1);
    }
    for(int i=2; i<argc; i++)
    {
    nowanazwa[0]=0;
    strcpy(nowanazwa, argv[1]);
    strcat(nowanazwa, argv[i]);
    //printf("\n%s", nowanazwa);
    rename(argv[i], nowanazwa);
    }
}
 
