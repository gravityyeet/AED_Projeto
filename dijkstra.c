#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pq.h"
#include "pg2.h"

#define inf 999     // May lead to some problems. Maybe needs to be bigger (See maximum double value)

void dijkstra(Graph *, int, int *, double *);
void print_caminho(int *, double *);

int main(int argc, char** argv) {
    int st[9];
    double dist[9];
    FILE *fpIn, *fpOut;
    char *input_name = "grafo7.edge";
    char *output_name = "grafo7.ladj";
    Graph *graph;

    fpIn = fopen(input_name, "r");
    if (fpIn == NULL)
    {
        exit(2);
    }

    graph = ReadGraph(fpIn);
    fclose(fpIn);

    fpOut = fopen(output_name, "w");
    if (fpOut == NULL)
    {
        exit(2);
    }

    WritesGraph(fpOut, graph);

    dijkstra(graph, 0, st, dist);
    print_caminho(st, dist);

    fclose(fpOut);
    FreeGraph(graph);
    return 1;
}

// Adaptar, mudar o nome das variaveis e rever a estrutura de dados
void dijkstra(Graph *G, int start, int vertice_origem[], double distancia[]) {
    int v1, v2;     // (v1, v2)
    double aux;
    LinkedList *t;
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

        for (t = G->adj[v1]; t != NULL; t = getNextNodeLinkedList(t)) {  // Analisa-se a lista de adjacencias de v1
            // Relaxaçao do caminho
            edge = (Edge *)getItemLinkedList(t);
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

void print_caminho(int st[], double dist[]) {
    int i = 3;
    int destino = 0;

    printf("%lf\n", dist[i]);

    if (i != destino) {
        printf("%d ", i);
        while (st[i] != destino) {
            i = st[i];
            printf("%d ", i);
        }
    }
    printf("%d\n", destino);
}