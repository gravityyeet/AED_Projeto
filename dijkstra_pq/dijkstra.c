#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pq.h"

#define inf 999     // May lead to some problems. Maybe needs to be bigger (See maximum double value)

typedef struct _Graph {
    int V;
    struct _Graph *next;
} Graph;

int main(int argc, char** argv) {
    
    if (argc < 1) {
        exit(0);
    }

    return 1;
}

// Adaptar, mudar o nome das variaveis e rever a estrutura de dados
void dijkstra(Graph *G, int start, int vertice_origem[], double distancia[]) {
    int v1, v2;     // (v1, v2)
    double aux;
    link *t;
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
        v1 = PQdelmin(head);    // Elemento com o custo mais baixo removido e posto o seu vertice em v1

        for (t = G->adj[v1]; t != NULL; t = t->next) {  // Analisa-se a lista de adjacencias de v1
            // Relaxaçao do caminho
            if (distancia[v2 = t->v] > distancia[v1] + t->wt) {      // = dist[v1] + custo da aresta
                aux = distancia[v2];
                distancia[v2] = distancia[v1] + t->wt;

                if (aux == inf) {   // Primeira vez do vertice?
                    node = PQcreateNode(v2);
                    head = PQinsert(head, node, distancia);
                } else {
                    PQdec(head, v2, distancia);
                }
                vertice_origem[v2] = v1;
            }
        }
    }
}