#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "salas_adj.h"
#include "salas.h"

#include "pg2.h"

#define inf 2147483647

Graph *criar_grafo_salas (LabList *lista, Sala *salas_head, Graph *graph) {
    Sala *sala_aux, *sala_aux2;

    Parede *aux1, *aux2;

    Listaadj *l_node;

    int v_graph = 0;
    int i = 0, j = 0;
    int l = 0, c = 0, w = 0;

    sala_aux = salas_head;
    while (sala_aux != NULL) {
        v_graph++;
        sala_aux = sala_aux->next;
    }
    graph->V = v_graph;
    //printf("::%d\n", v_graph);

    /* Allocates vertices array list */
    graph->adj = (Listaadj **)malloc(graph->V * sizeof(Listaadj *));
    if (graph->adj == NULL) {
        exit(0);
    }
    for (i = 0; i < graph->V; i++) {
        graph->adj[i] = initListabase();
    }

    /*  Aqui ja ta tudo alocado, so é preciso descobrir a parede que    *
     *  corresponde a aresta entre 2 salas                              */

    sala_aux = salas_head;
    for (i = 0; sala_aux != NULL; i++) {
        sala_aux2 = salas_head;
        for (j = 0; sala_aux2 != NULL; j++) {
            if (sala_aux != sala_aux2) {
                
                w = inf;
                aux1 = sala_aux->paredes_sala;
                while (aux1 != NULL) {
                    aux2 = sala_aux2->paredes_sala;  // aux2 é uma parede da sala2
                    while (aux2 != NULL) {
                        // Se as salas tiverem a mesma parede e se for a minima
                        if (aux2->l == aux1->l && aux2->c == aux1->c) {
                            // Se a ligacao entre as duas salas é possivel
                            if (ligacao_possivel_salas(lista, sala_aux, sala_aux2, aux2)) {
                                if (aux2->v < w) {
                                    w = aux2->v;
                                    l = aux2->l;
                                    c = aux2->c;
                                }
                            }
                        }
                        aux2 = aux2->next;
                    }
                    aux1 = aux1->next;
                }
                
                if (w != inf) {
                    // Criar aresta entre salas
                    //printf("! %d %d !\n", i, j);
                    //printf("### %d %d | %d\n", parede_aresta->l, parede_aresta->c, parede_aresta->v);
                    l_node = novo_no(l, c, j, w);
                    graph->adj[i] = insertllist(graph->adj[i], l_node);
                }            
            
            }
            sala_aux2 = sala_aux2->next;
        }
        sala_aux = sala_aux->next;
    }
    return graph;
}

int ligacao_possivel_salas(LabList *lista, Sala *s1, Sala *s2, Parede *p) {
    int l = 0, c = 0;

    l = p->l;
    c = p->c;

    // Se fazendo A6 em l+1|c, se encontrar as coords mae de s1 ou s2
    // e fazendo A6 em l-1|c, se encontrar as coords mae de s2 ou s1
    // entao retorna 1

    if ((A6_modded(lista, l + 1, c, s1) && A6_modded(lista, l - 1, c, s2)) ||
            (A6_modded(lista, l + 1, c, s2) && A6_modded(lista, l - 1, c, s1))) {
        return 1;
    }
    if ((A6_modded(lista, l, c + 1, s1) && A6_modded(lista, l, c - 1, s2)) ||
            (A6_modded(lista, l, c + 1, s2) && A6_modded(lista, l, c - 1, s1))) {
        return 1;
    }
    
    return 0;
}

int A6_modded (LabList *lista, int l, int c, Sala *sala) {
    A6_coord *head = NULL, *node = NULL, *node1 = NULL;
    int i = 0;

    reset_tab(lista->lab);

    /* Coordenadas de origem ou destino fora do labirinto */
    if (l > lista->lab->L || c > lista->lab->C || l < 1 || c < 1) {
        return 0;
    }
    if (sala->l > lista->lab->L || sala->c > lista->lab->C ||  sala->l < 1 || sala->c < 1) {
        return 0;
    }

    /*  Adiciona-se o primeiro ponto a lista, as coordenadas que queremos saber se  *
     *  estao na mesma sala que outras                                              */
    node1 = criar_No_A6(l, c);
    head = inserir_lista_A6 (head, node1);
    lista->lab->tabuleiro[l][c] = -3;   // Para saber que ja foi analisado
    while (1) {
        /* Ve sempre se ja encontramos a nossa resposta, se for afirmativa, retorna 1 */
        i = procurar_coord(head, sala->l, sala->c);
        if (i == 1) {
            while (head != NULL) {
                node = head;
                head = head->next;
                free(node);
            }
            return 1;
        }

        /* Remove o ponto que ja sabemos que nao tem la nada */
        head = remover_lista_A6(head, node1);

        /* Avalia se as vizinhas são brancas, se forem adiciona a lista de pontos */
        if (lista->lab->tabuleiro[l - 1][c] == 0) {
            node = criar_No_A6(l - 1, c);
            head = inserir_lista_A6(head, node);
            lista->lab->tabuleiro[l - 1][c] = -3;
        }
        if (lista->lab->tabuleiro[l + 1][c] == 0) {
            node = criar_No_A6(l + 1, c);
            head = inserir_lista_A6(head, node);
            lista->lab->tabuleiro[l + 1][c] = -3;
        }
        if (lista->lab->tabuleiro[l][c + 1] == 0) {
            node = criar_No_A6(l, c + 1);
            head = inserir_lista_A6(head, node);
            lista->lab->tabuleiro[l][c + 1] = -3;
        }
        if (lista->lab->tabuleiro[l][c - 1] == 0) {
            node = criar_No_A6(l, c - 1);
            head = inserir_lista_A6(head, node);
            lista->lab->tabuleiro[l][c - 1] = -3;
        }

        /*  Se ja nao tivermos pontos por analisar e nao tivermos encontrado    *
         *  o tesouro entao nao estao na mesma sala                             */
        if (head == NULL) {
            return 0;
        }

        /* Na proxima iteraçao, analisa-se a head da lista */
        node1 = head;
        l = node1->l;
        c = node1->c;
    }
    return -5;
}

void reset_tab(Labirinto *lab) {
    int i, j;

    for (i = 1; i < lab->L; i++) {
        for (j = 1; j < lab->C; j++) {
            if (lab->tabuleiro[i][j] == -3) {
                lab->tabuleiro[i][j] = 0;
            }
        }
    }
}

int procurar_coord (A6_coord *head, int l, int c) {
    A6_coord *aux;
    
    aux = head;
    while (aux != NULL) {
        if (aux->l == l && aux->c == c) {
            return 1;
        }
        aux = aux->next;
    }
    return 0;
}
