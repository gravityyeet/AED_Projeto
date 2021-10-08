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

void free_tabuleiro(tab *tabuleiro) {
    int linhas = tabuleiro->tab_l;

    for (int t = 0; t < tabuleiro->tab_l; t++) {
        free(tabuleiro->tabuleiro[t]);
    }
    free(tabuleiro->tabuleiro);
    free(tabuleiro);
}

// Funçao apenas para DEBUG
void print_tabuleiro(tab *tabuleiro) {
    for (int i = 0; i < tabuleiro->tab_l; i++) {
        for (int j = 0; j < tabuleiro->tab_c; j++) {
            printf("%d ", tabuleiro->tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void read_file_info (tab *tabuleiro, char Filename[]) {

    FILE *fp;
    int parede_1 = 0, parede_2 = 0, parede_v = 0;
    char ch = '0', ch_next = '0';
    int t_counter = 0;

    fp = fopen(Filename, "r");      // BUG: Se o nome do file nao tiver correto
    if (fp == (FILE *) NULL) {      //      da segmentation fault
        exit(EXIT_FAILURE);
    }

    // Calcula a quantidade de informação da tabela + paredes

    for (int i = 0; i < 100; i++) {
        fscanf(fp, " ");
        fscanf(fp, "\n");

        if(feof(fp) != 0) break; 

        if (i == 0) {
            fscanf(fp, "%d", &(tabuleiro->tab_l));
            printf("%d\n", tabuleiro->tab_l);            
        }
        if (i == 1) {
            fscanf(fp, "%d", &(tabuleiro->tab_c));
            printf("%d\n", tabuleiro->tab_c);

            // Alocaçao do tabuleiro 2D
            alloc_tabuleiro(tabuleiro); 
        }
        if (i == 2) {
            fscanf(fp, "%d", &(tabuleiro->tesouro_l));
            printf("%d\n", tabuleiro->tesouro_l);            
        }
        if (i == 3) {
            fscanf(fp, "%d", &(tabuleiro->tesouro_c));
            printf("%d\n", tabuleiro->tesouro_c); 
        }
        if (i == 4) {
            fscanf(fp, "%s", tabuleiro->tipo_jogo);
            printf("%s\n", tabuleiro->tipo_jogo); 
        }
        if (i == 5 && (strcmp(tabuleiro->tipo_jogo, "A6") != 0)) {
            fscanf(fp, "%s", tabuleiro->tipo_jogo);
            printf("%s\n", tabuleiro->tipo_jogo); 
        }


        if (i > 5 /* && tipo_jogo != A6 */) {    // Ler Paredes para apenas 1 int

            // Passagem do valor da celula para as coord no tabuleiro
            fscanf(fp, "%d", &parede_1);

            fscanf(fp, " ");
            fscanf(fp, "\n");

            fscanf(fp, "%d", &parede_2);

            fscanf(fp, " ");
            fscanf(fp, "\n");

            fscanf(fp, "%d", &parede_v);

            tabuleiro->tabuleiro[parede_1 - 1][parede_2 - 1] = parede_v;
        }
    }

    fclose(fp);
}