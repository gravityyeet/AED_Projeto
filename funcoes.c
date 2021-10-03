#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declaracoes.h"

void alloc_tabuleiro(tab *tabuleiro) {
    tabuleiro->tabuleiro = (int **) malloc(sizeof(int *) * tabuleiro->tab_l);
    if (tabuleiro->tabuleiro == NULL) {
        exit(EXIT_FAILURE);
    } 
    for (int alloc_c = 0; alloc_c < tabuleiro->tab_l; alloc_c++) {
        tabuleiro->tabuleiro[alloc_c] = (int *) malloc(sizeof(int) * tabuleiro->tab_c);
        if (tabuleiro->tabuleiro[alloc_c] == NULL) {
            exit(EXIT_FAILURE);
        }
    }
}

void print_tabuleiro(tab *tabuleiro) {
    for (int i = 0; i < tabuleiro->tab_l; i++) {
        for (int j = 0; j < tabuleiro->tab_c; j++) {
            printf("%d ", tabuleiro->tabuleiro[i][j]);
        }
        printf("\n");
    }
}