#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "salas_adj.h"
#include "salas.h"

#include "pg2.h"

#define inf 999

Graph *criar_grafo_salas (Sala *salas_head, Graph *graph) {
    Sala *sala_aux, *sala_aux2;

    Parede *p_min, *aux1, *aux2, *f_aux;

    Listaadj *l_node;

    int v_graph = 0;
    int i = 0, j = 0;

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

    p_min = (Parede *)malloc(sizeof(Parede));   // DPS TEM DE SE DAR FREE
    if (p_min == NULL){
        exit(0);
    }
    f_aux = p_min;

    /*  Aqui ja ta tudo alocado, so é preciso descobrir a parede que    *
     *  corresponde a aresta entre 2 salas                              */

    sala_aux = salas_head;
    for (i = 0; sala_aux != NULL; i++) {
        sala_aux2 = salas_head;
        for (j = 0; sala_aux2 != NULL; j++) {
            if (sala_aux != sala_aux2) {
                
                p_min->v = inf;
                aux1 = sala_aux->paredes_sala;
                while (aux1 != NULL) {
                    aux2 = sala_aux2->paredes_sala;  // aux2 é uma parede da sala2
                    while (aux2 != NULL) {
                        // Se as salas tiverem a mesma parede e se for a minima, mete se em p_min
                        if (aux2->l == aux1->l && aux2->c == aux1->c) {
                            if (aux2->v < p_min->v) {
                                p_min = aux2;
                            }
                        }
                        aux2 = aux2->next;
                    }
                    aux1 = aux1->next;
                }
                
                if (p_min->v != inf) {
                    // Criar aresta entre salas
                    //printf("! %d %d !\n", i, j);
                    //printf("### %d %d | %d\n", parede_aresta->l, parede_aresta->c, parede_aresta->v);
                    l_node = novo_no(p_min->l, p_min->c, j, p_min->v);
                    graph->adj[i] = insertllist(graph->adj[i], l_node);
                }            
            
            }
            sala_aux2 = sala_aux2->next;
        }
        sala_aux = sala_aux->next;
    }
    free(f_aux);
    return graph;
}

// Percorrer a sala2, comparando com a sala1 e escolhe a parede minima
Parede *comparar_salas(Sala *sala1, Sala *sala2) {
    Parede *p_min, *aux1, *aux2;

    p_min = (Parede *)malloc(sizeof(Parede));   // DPS TEM DE SE DAR FREE
    if (p_min == NULL){
        exit(0);
    }

    p_min->v = inf;

    aux1 = sala1->paredes_sala;
    while (aux1 != NULL) {
        aux2 = sala2->paredes_sala;  // aux2 é uma parede da sala2
        while (aux2 != NULL) {
            // Se as salas tiverem a mesma parede e se for a minima, mete se em p_min
            if (aux2->l == aux1->l && aux2->c == aux1->c) {
                if (aux2->v < p_min->v) {
                    p_min = aux2;
                }
            }
            aux2 = aux2->next;
        }
        aux1 = aux1->next;
    }

    if (p_min->v == inf) {   // Caso nao haja ligacao entre as salas
        p_min = NULL;
    } else {
        //printf("%d %d : %d %d\n", sala1->l, sala1->c, sala2->l, sala2->c);
    }

    return p_min;   // Parede mais pequena comum a 2 salas
}



