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

int A6 (LabList *lista, int teste_l, int teste_c) {
    A6_coord *head = NULL, *node = NULL, *node1 = NULL;
    int i = 0;

    /* Coordenadas de origem ou destino fora do labirinto */
    if (    lista->lab->cel_L > lista->lab->L || lista->lab->cel_C > lista->lab->C || 
            lista->lab->cel_L < 1 || lista->lab->cel_C < 1) {
        return -2;
    }
    if (    lista->lab->cel_2_L > lista->lab->L || lista->lab->cel_2_C > lista->lab->C ||  
            lista->lab->cel_2_L < 1 || lista->lab->cel_2_C < 1) {
        return -2;
    }

    if (lista->lab->tabuleiro[lista->lab->cel_L][lista->lab->cel_C] != 0 || 
        lista->lab->tabuleiro[lista->lab->cel_2_L][lista->lab->cel_2_C] != 0) {
        return 0;
    }    

    node1 = criar_No_A6(lista->lab->cel_L, lista->lab->cel_C);
    head = inserir_lista_A6 (head, node1);
    lista->lab->tabuleiro[teste_l][teste_c] = -3;
    while (1) {
        i = procurar_tesouro(head, lista);
        if (i == 1) {
            while (head != NULL) {
                node = head;
                head = head->next;
                free(node);
            }
            return 1;
        }
        head = remover_lista_A6(head, node1);
        if (lista->lab->tabuleiro[teste_l - 1][teste_c] == 0) {
            node = criar_No_A6(teste_l - 1, teste_c);
            head = inserir_lista_A6(head, node);
            lista->lab->tabuleiro[teste_l - 1][teste_c] = -3;
        }
        if (lista->lab->tabuleiro[teste_l + 1][teste_c] == 0) {
            node = criar_No_A6(teste_l + 1, teste_c);
            head = inserir_lista_A6(head, node);
            lista->lab->tabuleiro[teste_l + 1][teste_c] = -3;
        }
        if (lista->lab->tabuleiro[teste_l][teste_c + 1] == 0) {
            node = criar_No_A6(teste_l, teste_c + 1);
            head = inserir_lista_A6(head, node);
            lista->lab->tabuleiro[teste_l][teste_c + 1] = -3;
        }
        if (lista->lab->tabuleiro[teste_l][teste_c - 1] == 0) {
            node = criar_No_A6(teste_l, teste_c - 1);
            head = inserir_lista_A6(head, node);
            lista->lab->tabuleiro[teste_l][teste_c - 1] = -3;
        }
        if (head == NULL) {
            return 0;
        }
        node1 = head;
        teste_l = node1->l;
        teste_c = node1->c;
    }
    return -5;
}

void print_tabuleiro(Labirinto *lab) {
    for (int i = 0; i < lab->L + 2; i++) {
        for (int j = 0; j < lab->C + 2; j++) {
            printf("%d ", lab->tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int procurar_tesouro (A6_coord *head, LabList *lista) {
    A6_coord *aux;
    
    aux = head;

    while (aux != NULL) {
        if (aux->l == lista->lab->cel_2_L && aux->c == lista->lab->cel_2_C) {
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}

A6_coord *criar_No_A6 (int linha, int coluna) {

    A6_coord *newnode;

    newnode = (A6_coord *) calloc(1, sizeof(A6_coord));
    if(newnode == NULL) {
        exit(0);
    }

    newnode->l = linha;
    newnode->c = coluna;
    newnode->next = NULL;

    return newnode;
}

A6_coord *inserir_lista_A6 (A6_coord *head, A6_coord *node) {
    A6_coord *auxA, *auxN;

    if (head == NULL) {
        head = node;
    } else {
        auxA = head;
        auxN = head->next;
        while (auxN != NULL) {
            auxA = auxN;
            auxN = auxN->next;
        }
        auxA->next = node;
    }
    return head;
}

A6_coord *procura_node (A6_coord *head ,int l, int c) {
    A6_coord *aux;

    aux = head;

    while (aux != NULL) {
        if (aux->l == l && aux->c == c) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

A6_coord *remover_lista_A6 (A6_coord *head, A6_coord *removenode) {
    A6_coord *aux, *auxn;

    aux = head;

    if (removenode->l == aux->l && removenode->c == aux->c) {
        head = head->next;
        free(aux);
    } else {
        while (removenode->l != aux->l && removenode->c != aux->c) {
            aux = auxn;
            auxn = auxn->next;
        }
        aux->next = auxn->next;
        free(auxn);
    }
    return head;
}