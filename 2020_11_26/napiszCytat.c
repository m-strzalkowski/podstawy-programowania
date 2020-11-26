#include<stdio.h>

int main()
{
   FILE *fp;

   fp = fopen("Machiavelli.txt", "w+");
   if(!fp){perror("Nie moge otworzyc pliku");}
   fprintf(fp, "Ludzie latwiej zniosa strate ojca niz ojcowizny.\n");
   fclose(fp);
    return 0;
}
