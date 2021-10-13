#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "modosA.h"
#include "roap.h"

int A1 (LabList *lista) {

    int i = 0;
    int linhas = 0, colunas = 0;

    linhas = lista->lab->L;
    colunas = lista->lab->C;

    /* Fora do labirinto */
    if ( lista->lab->cel_L > linhas || lista->lab->cel_C > colunas ) {
        return -2;
    };

    /* Se tem valor, da return do valor, senao tem que ser  *
     * uma celula branca                                    */
    /*if ( i = lista->lab->paredes->cost != 0 ) {     // ISTO TA MAL
        return i;
    } else {
        return 0;
    }*/

    return -1;
}

int A2_4 (LabList *lista, int modo) {

    if (modo == 2) {

    }
    if (modo == 3) {

    }
    if (modo == 4) {

    }

    return -1;
}