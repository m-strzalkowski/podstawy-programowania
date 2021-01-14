
#ifndef WYJSCIE_H
#define WYJSCIE_H

#include "baza.h"

//#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(...) do{ fprintf( stderr, __VA_ARGS__ ); } while( 0 );
#else
#define DEBUG_PRINT(...) do{ } while ( 0 );
#endif
//OPCJE (PRZELACZNIKI)
extern int we_z_pliku;
extern int wy_do_pliku;

extern FILE * plikwyjsciowy;
extern FILE * plikwejsciowy;
#define WYJSCIE(...) fprintf( ( (wy_do_pliku)?(plikwyjsciowy):(stdout) ), __VA_ARGS__ );


int format_zdan(char * fmt);
int PISZ_ZDANIE(wezel * zdanie, int num/*numer*/, int lnum, int rnum);
#endif // WYJSCIE_H
