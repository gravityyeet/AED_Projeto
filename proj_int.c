#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declaracoes.h"

void main (int argc, char *argv[]) {

    tab *tabuleiro;
    tabuleiro = (tab*) malloc(sizeof(tab));

    if (argc != 2) {        // Tem que ter apenas 2 argumentos
        exit(EXIT_FAILURE);
    }

    read_file_info(tabuleiro, argv[1]);

    print_tabuleiro(tabuleiro);

    free_tabuleiro(tabuleiro);

}