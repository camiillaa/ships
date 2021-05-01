
#include "bt.h"
#include <memory.h>


/* pDepthTab - tablica okreslajaca glebokosc w kazdym polu prostokatnego obszaru
   nRow, nCol - rozmiary pTab,
   nDepth - glebokosc zanurzenia statku
   nextMove - kierunek ruchu
   x, y - indeksy w tablicy skad wykonujemy kolejny ruch np. zaczynamy od 0,0
   px, py - parametry WYJSCIWE - nowe wspolrzedne
   pRoot - tablica pamietajaca ruchy o rozm nRow, nCol
*/

int move( int** pDepthTab, int nRow, int nCol, int nDepth,
    int nextMove, int x, int y, int* px, int* py, int** pRoot )
{
    // x  y - wsporzedne skad robimy nowy ruch
//  wykonac kolejny ruch w kierunku nextMove obliczajac nowe wspolrzedne *px *py
     //(switch)
    switch ( nextMove )
    {
    case UP: *px = x-1; *py = y;     break;
    case RIGHT: *px = x; *py = y+1;  break;
    case DOWN: *px = x+1; *py = y;   break;
    case LEFT: *px = x; *py = y-1;   break;
    default: printf("Error: move function!"); break;
    }
    //sprawdzic czy nowe indeksy *px i *py sa w zakresie indeksow tablicy
    if ( *px < N && *py < M && *px >= 0 && *py >= 0 )
    {
        // a nastepnie sprawdzic warunek czy nie jest za plytko oraz
        if ( nDepth < pDepthTab[*px][*py] && pRoot[*px][*py] == 0 ) // pRoot = 0 ->>> pole nieodwiedzone
            // czy nie bylo sie juz w lokalizacji (*px,*py) - wg tabl pRoot
            return 1;
    }
//    jesli wszystkie warunki poprawne to zwracamy 1
  //   jesli nie to 0
    return 0;
}

/* pDepthTab tablica glebokosci morza o romiarze nRow  i nCol
    dDepth - glebokosc zanurzenia ststku
    x, y - wspol skad robimy kolejny ruch
    pRoot tablica kolejnych ruchow
    x_dest, y_dest - wsporzedne portu
*/


int root( int** pDepthTab, int nRow, int nCol, int nDepth,
    int x, int y, int** pRoot, int x_dest, int y_dest )
{
    static int numofmoves = 0;
    pRoot[x][y] = ++numofmoves;

    if ( x == x_dest && y == y_dest )
        return 1;
    // zdefiniowac nowe wspolrzende 
    int px = 0;
    int py = 0;
  // sprwadzic wszystkie mozliwosci ruchu (for od UP do LEFT)
    for ( int i = UP; i <= LEFT; i++ )
    {
        // jesli ruch jest mozliwy w zadanym kierunku - funkcja move()
        if ( move( pDepthTab, nRow, nCol, nDepth, i, x, y, &px, &py, pRoot ) )
        {
           
            // to jesli rekurencyjnie wolany root() zwroci prawde to  return 1;
            if ( root( pDepthTab, N, M, SHIP_DEPTH, px, py, pRoot, x_dest, y_dest ) )
                return 1;
        }
    }
   pRoot[x][y] = 0;
   numofmoves--;
    return 0; 
}
// jesli wracamy to ustawiamy w pRoot ze ruch byl zly  - czyli 0



int readDepthTab( char* sFile, int** pTab, int nRow, int nCol )
{
    FILE* plik = fopen( sFile, "r" ); // wlaczenie pliku na odczyt
    if ( !plik )
    {
        printf( "ERROR: Read error: %s", sFile );
        return 0;
    }
    for ( int i = 0; i < nRow; i++ )
    {
        int* ppTab = *pTab++;
        for ( int j = 0; j < nCol; j++ )
        {
            fscanf( plik, " %d ", ppTab++ );
        } 

    }
    fclose( plik );
    plik = NULL;
    return 1;
}
// wczytuje dane z pliku
// sFile -  nazwa pliku wejsciowego - parametr main()
// pTab  - tablica glebokosci morza
// nRow, nCol wymiary tej tablicy

int** createTab( int nRow, int nCol )
{
    int** Row = (int**)malloc( sizeof(int*)*nRow );
    int* Col = (int*)malloc( sizeof(int)* nRow * nCol );
    if ( !*Row || !Col ) return 0;
    memset( Row, 0, sizeof(int*) * nRow );
    memset( Col, 0, sizeof(int) * nRow*nCol );

   // int* dCol = Col;
    int** rRow = Row;
    for ( int i = 0; i < nRow; i++, rRow++ )
    {
        *rRow = Col;
        Col += nCol;

    }
    return Row;
}


void printTab( int** pRoot, int nRow, int nCol )
{
    for ( int i = 0; i < nRow; i++ )
    {
        int* ppRoot = *pRoot++;
        for ( int j = 0; j < nCol; j++ )
        {
            printf( " %d", *ppRoot++ );
        }
        printf( "\n" );
    }
}
void freeTab( int*** pTab ) // nie potrebne rozmiary
{
    free( **pTab );
    free( *pTab );
    *pTab = NULL;
}
