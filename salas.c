#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "modosA.h"
#include "salas.h"

void print_tabuleiro(Labirinto *lab) {
    for (int i = 0; i < lab->L + 2; i++) {
        for (int j = 0; j < lab->C + 2; j++) {
            printf("%d ", lab->tabuleiro[i][j]);
        }
        printf("\n");
    }
}

Sala *analisar_salas (LabList *lista, int l, int c) {
    Parede *p_node = NULL;
    Sala *head = NULL, *node = NULL;

    p_node = A6_salas(lista, l, c, p_node);

    /*
        Analisar a primeira sala. Vai retornar um ponteiro para a lista
        de paredes da primeira sala.
        Associa se esse ponteiro de paredes a sala 1.
        Vai se ver os vertices adjacentes das paredes da sala 1, se forem
        celulas brancas, entao vai se criar uma nova sala ai e fazer A6.
    */

    node = criar_sala(l, c, p_node);
    head = inserir_lista_sala(head, node);

    ver_paredes_sala(head, lista);

    node = head;
    p_node = head->paredes_sala;
    while (node != NULL) {
        printf("\nCoords Sala: %d %d\n", node->l, node->c);
        print_paredes(node->paredes_sala);

        node = node->next;
    }

    return head;
}

void ver_paredes_sala (Sala *head, LabList *lista) {
    Parede *p;
    Sala *node = NULL;
    Parede *p_node = NULL;
    int **tabela = lista->lab->tabuleiro;

    p = head->paredes_sala;

    while (p != NULL) {
        if (tabela[p->l + 1][p->c] == 0) {
            p_node = A6_salas(lista, p->l + 1, p->c, p_node);
            node = criar_sala(p->l + 1, p->c, p_node);
            head = inserir_lista_sala(head, node);
            ver_paredes_sala(node, lista);
        }
        if (tabela[p->l - 1][p->c] == 0) {
            p_node = A6_salas(lista, p->l - 1, p->c, p_node);
            node = criar_sala(p->l - 1, p->c, p_node);
            head = inserir_lista_sala(head, node);
            ver_paredes_sala(node, lista);
        }
        if (tabela[p->l][p->c + 1] == 0) {
            p_node = A6_salas(lista, p->l, p->c + 1, p_node);
            node = criar_sala(p->l, p->c + 1, p_node);
            head = inserir_lista_sala(head, node);
            ver_paredes_sala(node, lista);
        }
        if (tabela[p->l][p->c - 1] == 0) {
            p_node = A6_salas(lista, p->l, p->c - 1, p_node);
            node = criar_sala(p->l, p->c - 1, p_node);
            head = inserir_lista_sala(head, node);
            ver_paredes_sala(node, lista);
        }
        p = p->next;
    }
}

Parede *A6_salas (LabList *lista, int teste_l, int teste_c, Parede *head_p) {
    A6_coord *head = NULL, *node = NULL, *node1 = NULL;
    Parede *node_p = NULL;

    /*  Adiciona-se o primeiro ponto a lista, as coordenadas que queremos saber se  *
     *  estao na mesma sala que outras                                              */
    node1 = criar_No_A6(lista->lab->cel_L, lista->lab->cel_C);
    head = inserir_lista_A6 (head, node1);
    lista->lab->tabuleiro[teste_l][teste_c] = -3;   // Para saber que ja foi analisado
    while (1) {
        head = remover_lista_A6(head, node1);

        /* Avalia se as vizinhas são brancas, se forem adiciona a lista de pontos */
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

        /* Se alguma adj for uma parede, adiciona a lista de paredes da sala */
        if (lista->lab->tabuleiro[teste_l - 1][teste_c] > 0) {
            node_p = criar_No_Parede(teste_l - 1, teste_c);
            head_p = inserir_lista_Parede(head_p, node_p);
            lista->lab->tabuleiro[teste_l - 1][teste_c] = -9;
        }
        if (lista->lab->tabuleiro[teste_l + 1][teste_c] > 0) {
            node_p = criar_No_Parede(teste_l + 1, teste_c);
            head_p = inserir_lista_Parede(head_p, node_p);
            lista->lab->tabuleiro[teste_l + 1][teste_c] = -9;
        }
        if (lista->lab->tabuleiro[teste_l][teste_c + 1] > 0) {
            node_p = criar_No_Parede(teste_l, teste_c + 1);
            head_p = inserir_lista_Parede(head_p, node_p);
            lista->lab->tabuleiro[teste_l][teste_c + 1] = -9;
        }
        if (lista->lab->tabuleiro[teste_l][teste_c - 1] > 0) {
            node_p = criar_No_Parede(teste_l, teste_c - 1);
            head_p = inserir_lista_Parede(head_p, node_p);
            lista->lab->tabuleiro[teste_l][teste_c - 1] = -9;
        }
        
        /*  Todos os pontos da sala ja foram analisados     */
        if (head == NULL) {
            break;
        }

        /* Na proxima iteraçao, analisa-se a head da lista */
        node1 = head;
        teste_l = node1->l;
        teste_c = node1->c;
    }
    node_p = head_p;
    while (node_p != NULL) {
        lista->lab->tabuleiro[node_p->l][node_p->c] = 9;    // Valor da parede nao relevante
        node_p = node_p->next;
    }

    return head_p;
}

void print_paredes (Parede *head) {
    Parede *node;
    int i = 0;

    node = head;
    while (node != NULL) {
        printf ("%d %d  :  ", node->l, node->c);
        node = node->next;
        i++;
    }
    printf ("\nN de paredes: %d\n", i);
}

Parede *criar_No_Parede (int linha, int coluna) {

    Parede *newnode;

    newnode = (Parede *) calloc(1, sizeof(Parede));
    if(newnode == NULL) {
        exit(0);
    }

    newnode->l = linha;
    newnode->c = coluna;
    newnode->next = NULL;

    return newnode;
}

Parede *inserir_lista_Parede (Parede *head, Parede *node) {
    Parede *auxA, *auxN;

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

Sala *criar_sala (int linha, int coluna, Parede *lista_paredes) {

    Sala *newnode;

    newnode = (Sala *) calloc(1, sizeof(Sala));
    if(newnode == NULL) {
        exit(0);
    }

    newnode->l = linha;
    newnode->c = coluna;
    newnode->paredes_sala = lista_paredes;
    newnode->next = NULL;

    return newnode;
}

Sala *inserir_lista_sala (Sala *head, Sala *node) {
    Sala *auxA, *auxN;

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

void free_parede(Parede *p) {
    Parede *aux;

    aux = p;
    while (p != NULL) {
        aux = p;
        p = p->next;
        free(aux);
    }
}

void free_sala(Sala *head) {
    Sala *aux;

    aux = head;
    while (head != NULL) {
        aux = head;
        head = head->next;
        free(aux);
    }
}