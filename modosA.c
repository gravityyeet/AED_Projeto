#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "modosA.h"
#include "roap.h"

int A1 (LabList *lista) {

    int i = 0;
    int coord_l = lista->lab->cel_L, coord_c = lista->lab->cel_C;

    /* Fora do labirinto */
    if ( coord_l > lista->lab->L || coord_c > lista->lab->C ) {
        return -2;
    };
    /* Se tem valor, da return do valor, senao tem que ser  *
     * uma celula branca                                    */
    if ( (i = lista->lab->tabuleiro[coord_l - 1][coord_c - 1]) != 0 ) {
        return i;
    } else {
        return 0;
    }
    return -5;
}

int A5 (LabList *lista) {

    int coord_l = lista->lab->cel_L, coord_c = lista->lab->cel_C;

    /* Fora do labirinto */
    if ( coord_l > lista->lab->L || coord_c > lista->lab->C ) {
        return -2;
    };

    if ( lista->lab->tabuleiro[coord_l - 1][coord_c - 1] > 0 ) {
        return 1;
    } else {
        return -1;
    }
    return -5;
}

int A2_4 (LabList *lista, int modo) {
    int coord_l = lista->lab->cel_L, coord_c = lista->lab->cel_C;

    /* Coordenada fora do labirinto */
    if ( coord_l > lista->lab->L || coord_c > lista->lab->C ) {
        return -2;
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            /* Impede acessos a fora da memoria alocada, verificando se *
             * algum vizinho esta fora do labirinto                     */
            if ( coord_l - 2 + i < 0 || coord_l - 2 + i > lista->lab->L - 1 || coord_c + j - 2 < 0
                        || coord_c - 2 + j > lista->lab->C - 1 ) {
                continue;
            }
            /* Nao se pretende verificar a celula cujas coordenadas foram introduzidas */
            if (i == 1 && j == 1) {
                continue;
            }

            if (modo == 2) {
                if ( lista->lab->tabuleiro[coord_l - 2 + i][coord_c - 2 + j] == 0 ) {
                    return 1;
                }
            }
            if (modo == 3) {
                if ( lista->lab->tabuleiro[coord_l - 2 + i][coord_c - 2 + j] > 0 ) {
                    return 1;
                }
            }
            if (modo == 4) {
                if ( lista->lab->tabuleiro[coord_l - 2 + i][coord_c - 2 + j] == -1 ) {
                    return 1;
                }
            }
        }
    }
    return 0;
}