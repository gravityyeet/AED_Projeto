#include <stdio.h>
#include <string.h>
#include <stdlib.h>

 #include "dijkstra.h"

// Adaptar, mudar o nome das variaveis e rever a estrutura de dados
void dijkstra(Graph *G, int start, int vertice_origem[], int distancia[]) {
    int v1, v2;     // (v1, v2)
    double aux;
    Listaadj *t;
    Edge *edge;
    PQ *head = NULL, *node;

    //PQinit(G->V);
    for (v1 = 0; v1 < G->V; v1++) {
        vertice_origem[v1] = -1;
        distancia[v1] = inf;    // Infinito
    }

    // Distancia de source a source e 0
    distancia[start] = 0.0;
    node = PQcreateNode(start);
    head = PQinsert(head, node, distancia);    // Apenas inserir a source na PQ

    while (!PQempty(head)) {
        head = PQdelmin(head, &v1);    // Elemento com o custo mais baixo removido e posto o seu vertice em v1

        for (t = G->adj[v1]; t != NULL; t = getNextNodeLList(t)) {  // Analisa-se a lista de adjacencias de v1
            // Relaxaçao do caminho
            edge = getEdgeFromLList(t);
            if (distancia[v2 = edge->V] > distancia[v1] + edge->W) {      // = dist[v1] + custo da aresta
                aux = distancia[v2];
                distancia[v2] = distancia[v1] + edge->W;

                if (aux == inf) {   // Primeira vez do vertice?
                    node = PQcreateNode(v2);
                    head = PQinsert(head, node, distancia);
                } else {
                    head = PQdec(head, v2, distancia);
                }
                vertice_origem[v2] = v1;
            }
        }
    }
}

void print_caminho(Graph *graph, int st[], int dist[], int i, int destino) {
    Edge *head_e = NULL, *edge, *aux_e;
    int n = 0, aux = 0;

    printf("\n%d\n", dist[i]);

    aux = i;
    while (aux != destino) {
        aux = st[aux];
        n++;
    }
    printf("%d\n", n);

    // i = sala1 origem
    // st[i] == sala2 vizinho

    if (i != destino) {
        aux_e = gets_edge(graph, i, st[i]);
        if (aux_e == NULL) {
            exit(0);
        }
        edge = criar_No_edge(aux_e->l, aux_e->c, aux_e->W);
        head_e = inserir_lista_edge(head_e, edge);
        //printf("%d ", i);
        while (st[i] != destino) {
            i = st[i];
            aux_e = gets_edge(graph, i, st[i]);
            if (aux_e == NULL) {
                exit(0);
            }
            edge = criar_No_edge(aux_e->l, aux_e->c, aux_e->W);
            head_e = inserir_lista_edge(head_e, edge);
            //printf("%d ", i);
        }
    }
    print_edges(head_e);
    free_edges(head_e);
    
    //printf("%d\n", destino);printf("%d %d %d\n", edge->l, edge->c, edge->W);
}