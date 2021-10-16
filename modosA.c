#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "modosA.h"
#include "roap.h"

int A1 (LabList *lista) {

    int i = 0;
    int coord_l = lista->lab->cel_L, coord_c = lista->lab->cel_C;

    /* Fora do labirinto */
    if ( coord_l > lista->lab->L || coord_c > lista->lab->C || coord_l < 1 || coord_c < 1) {
        return -2;
    }
    /* Se tem valor, da return do valor, senao tem que ser  *
     * uma celula branca                                    */
    i = lista->lab->tabuleiro[coord_l][coord_c];
    if ( i != 0 ) {
        return i;
    } else {
        return 0;
    }
    return -5;
}

int A5 (LabList *lista) {

    int coord_l = lista->lab->cel_L, coord_c = lista->lab->cel_C;

    /* Fora do labirinto */
    if ( coord_l > lista->lab->L || coord_c > lista->lab->C || coord_l < 1 || coord_c < 1) {
        return -2;
    }

    if ( lista->lab->tabuleiro[coord_l][coord_c] > 0 ) {
        /* Verifica se e possivel quebrar a peca */
        if (    (lista->lab->tabuleiro[coord_l - 1][coord_c] != 0 && 
                    lista->lab->tabuleiro[coord_l][coord_c + 1] != 0) ||
                (lista->lab->tabuleiro[coord_l][coord_c + 1] != 0 && 
                    lista->lab->tabuleiro[coord_l + 1][coord_c] != 0) ||
                (lista->lab->tabuleiro[coord_l + 1][coord_c] != 0 && 
                    lista->lab->tabuleiro[coord_l][coord_c - 1] != 0) ||
                (lista->lab->tabuleiro[coord_l][coord_c - 1] != 0 && 
                    lista->lab->tabuleiro[coord_l - 1][coord_c] != 0) ) {
            
            return 0;
        } else {
            return 1;    
        }
    } else {
        return -1;
    }
    return -5;
}

int A2_4 (LabList *lista, int modo) {
    int coord_l = lista->lab->cel_L, coord_c = lista->lab->cel_C;

    /* Coordenada fora do labirinto */
    if ( coord_l > lista->lab->L || coord_c > lista->lab->C || coord_l < 1 || coord_c < 1) {
        return -2;
    }

    if (modo == 2) {
        if (    lista->lab->tabuleiro[coord_l - 1][coord_c] == 0 ||
                lista->lab->tabuleiro[coord_l + 1][coord_c] == 0 ||
                lista->lab->tabuleiro[coord_l][coord_c - 1] == 0 ||
                lista->lab->tabuleiro[coord_l][coord_c + 1] == 0 ) {
            return 1;
        }
    }
    if (modo == 3) {
        if (    lista->lab->tabuleiro[coord_l - 1][coord_c] > 0 ||
                lista->lab->tabuleiro[coord_l + 1][coord_c] > 0 ||
                lista->lab->tabuleiro[coord_l][coord_c - 1] > 0 ||
                lista->lab->tabuleiro[coord_l][coord_c + 1] > 0 ) {
            return 1;
        }
    }
    if (modo == 4) {
        if (    lista->lab->tabuleiro[coord_l - 1][coord_c] == -1 ||
                lista->lab->tabuleiro[coord_l + 1][coord_c] == -1 ||
                lista->lab->tabuleiro[coord_l][coord_c - 1] == -1 ||
                lista->lab->tabuleiro[coord_l][coord_c + 1] == -1 ) {
            return 1;
        }
    }
    return 0;
}