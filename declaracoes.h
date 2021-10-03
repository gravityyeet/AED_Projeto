#ifndef DECLARACOES_H_INCLUDED
#define DECLARACOES_H_INCLUDED

typedef struct tabuleiro {
    int **tabuleiro;
    char tipo_jogo[2];    // A(0-6)
    int tab_l;          // N de linhas do tabuleiro
    int tab_c;          // N de colunas do tabuleiro
    int tesouro_l;      // Linha do tesouro
    int tesouro_c;      // Coluna do tesouro
    int coord_l;        // Linha para as 2ª coordenadas do modo de jogo A6
    int coord_c;        // Coluna para as 2ª coordenadas do modo de jogo A6
    int n_cel_p_c;      // N de celulas pretas ou cinzentas
} tab;

void alloc_tabuleiro();
void print_tabuleiro();

#endif // DECLARACOES_H_INCLUDED