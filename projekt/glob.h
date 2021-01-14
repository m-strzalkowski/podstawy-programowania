//W TYM PLIKU SIEDZĄ FUNKCJE UŻYTKOWE I GLOBALNE FLAGI
#ifndef GLOB_H
#define GLOB_H

#define MALY_BUFOR 4096
#define DUZY_BUFOR 32768

//malloc, który zwraca 7 i konczy program gdy zwróci null
void * mallocspr(size_t rozm);

#endif // GLOB_H
