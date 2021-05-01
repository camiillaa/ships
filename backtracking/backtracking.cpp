
#include "bt.h"

#define DEBUG
int main( int argc, char* argv[] )
{
    //!!argc
    if ( argc != 2 )
    {
        printf( "Usage: %s <plik wejsciowy>", argv[0] );
        return 1;
    }
    //Wykreowac dynamicznie dwie tablice dwuwymiarowe (ogolnie moga byc rozne wymiary)
    int** pTab = createTab( N, M );
    int** pRoot = createTab( N, M );
    if ( !*pTab || !*pRoot ) 
    {
        perror( "ERROR: Allocation error - createTab" );
        return -1;
    }
  
    // wczytac dane 
    if ( readDepthTab( argv[1], pTab, N, M ) )
    {

#ifdef DEBUG
        printf("DANE:\n");
        printTab(pTab, N, M);
        printf("\n");
#endif

        // Jezeli nie znaleziono drogi od (0,0) - funkcja rekur root zwraca 0 - wypisac

        if (!root(pTab, N, M, SHIP_DEPTH, 0, 0, pRoot, N - 1, M - 1))
            printf("\n\nNie ma mozliwosci doplynac do portu!!\n\n");
        else
        {
            printf("STATEK DOPLYNAL DO PORTU!!!\n");
            printTab(pRoot, N, M);
        }

    }

    // jesli ok to wypisac trase - czyli tablice z ruchami (pola zawieraj¹ce numer ruchu
    // pokazuja kolejnosc ruchu staku. 0 jest polem nieodwiedzonym (lub odwiedzonym ale statek nie 
    // mogl tam plynac wiec trzeba przywrocic 0)

     //zwolnic pamiec!!
    freeTab( &pTab );
    freeTab( &pRoot );

    return 0;
}