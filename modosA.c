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

int A6 (LabList *lista, int teste_l, int teste_c, int control) {
    int a = 0, b = 0, c = 0, d = 0;  // Resultado
    int aux_l = 0, aux_c = 0;

    /* Coordenadas de origem ou destino fora do labirinto */
    if (    lista->lab->cel_L > lista->lab->L || lista->lab->cel_C > lista->lab->C || 
            lista->lab->cel_L < 1 || lista->lab->cel_C < 1) {
        return -2;
    }
    if (    lista->lab->cel_2_L > lista->lab->L || lista->lab->cel_2_C > lista->lab->C ||  
            lista->lab->cel_2_L < 1 || lista->lab->cel_2_C < 1) {
        return -2;
    }
    /* Uma das coordernadas e uma parede */
    if (control == 0) {
        control++;   
        if (lista->lab->tabuleiro[lista->lab->cel_L][lista->lab->cel_C] != 0 || 
            lista->lab->tabuleiro[lista->lab->cel_2_L][lista->lab->cel_2_C] != 0) {
            return 0;
        }    
    }

    if (teste_l == lista->lab->cel_2_L && teste_c == lista->lab->cel_2_C) {
        return 1;
    } else if (lista->lab->tabuleiro[teste_l][teste_c] != 0) {
        return 0;
    } else {
        aux_l = teste_l;
        aux_c = teste_c;
        lista->lab->tabuleiro[teste_l][teste_c] = -3;
        if (a = A6(lista, teste_l + 1, teste_c, control)) return 1;
        teste_l = aux_l;
        teste_c = aux_c;
        if (b = A6(lista, teste_l - 1, teste_c, control)) return 1;
        teste_l = aux_l;
        teste_c = aux_c;
        if (c = A6(lista, teste_l, teste_c + 1, control)) return 1;
        teste_l = aux_l;
        teste_c = aux_c;
        if (d = A6(lista, teste_l, teste_c - 1, control)) return 1;
    }

    if ( a || b || c || d ) {
        return 1;
    } else {
        return 0;
    }

    return -5;
}