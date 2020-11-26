#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int liczbywjednejlinii(int nliczb)
{
    float liczby[nliczb];

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    fp = fopen("liczby.txt", "r");
    if (fp == NULL){perror("nie moge czytac"); exit(1);}
    printf("LINIE:\n");
    int i=0;
    while ((read = getline(&line, &len, fp)) != -1 && i<nliczb) {
        sscanf(line, "%f", &liczby[i++]);
        printf("%s", line);
    }

    fclose(fp);
    if (line) {free(line);}

    printf("\nLICZBY:\n");
    for(int j=0; j<i; j++)
    {
        printf("\n%f ", liczby[j]);
    }

    return 0;
}

int sformatowane(const char * nazwa)
{
    FILE * fp;
    fp = fopen(nazwa, "r");
    if (fp == NULL)
    {
        perror("nie moge czytac");
        exit(1);
    }
    char imie[256];
    int wiek=0;
    int n = fscanf(fp, "Jestem %s mam %d lat", imie, &wiek);
    printf("\n%s\n%d\n", imie, wiek);
    fclose(fp);
    return 0;
}

int srodekgwiazdkuj(const char * nazwa)
int srodekgwiazdkuj(const char * nazwa)
{
    FILE * fp;
    fp = fopen(nazwa, "r");
    if (fp == NULL)
    {
        perror("nie moge czytac");
        exit(1);
    }
    //while
    return 0;
}



int main()
{
    sformatowane("imiewiek.txt");
    //liczbywjednejlinii(10);
}
