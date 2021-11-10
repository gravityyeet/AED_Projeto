#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pq.h"
#include "pg2.h"

#define inf 999     // May lead to some problems. Maybe needs to be bigger (See maximum double value)

typedef struct vertex link;
struct vertex {int v; link *next;};
struct Graph{int V; int E; link **adj;};

typedef struct _Paredes_partidas {
    int l, c, v;
    struct _Paredes_partidas *next;
} Paredes_partidas;


int main(int argc, char** argv) {
    
    if (argc < 1) {
        exit(0);
    }

    pg2();

    return 1;
}

// Adaptar, mudar o nome das variaveis e rever a estrutura de dados
/*void dijkstra(Graph *G, int start, int vertice_origem[], double distancia[]) {
    int v1, v2;     // (v1, v2)
    double aux;
    link *t;
    PQ *head = NULL, *node;
    Paredes_partidas *head_p = NULL, *node_p;

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
                    /*if (node->V > 0) {
                        node = create(contar_linhas(v1, numero_colunas), v1 % 10, node->V);
                        head = add_to_list(head, node);
                    }
                } else {
                    PQdec(head, v2, distancia);
                }
                vertice_origem[v2] = v1;
            }
        }
    }
}*/

void output_final(Graph *grafo, char *filename, int v_ant[], double dist[], int destino) {
    FILE *fp;

    fp = fopen (filename, "w");

    fprintf(fp, "%lf\n", dist[destino]);


    fclose(fp);
}

int contar_linhas(int num, int sz_linha) {  //0...Linhas-1
    int i = 0;

    for (i = 0;; i++) {
        if (num < sz_linha) {
            break;
        }
        num -= sz_linha;
    }
    return i;
}

Paredes_partidas *create(int l, int c, int v) {
    Paredes_partidas *new;

    new = (Paredes_partidas *) malloc (sizeof(Paredes_partidas));
    if (new == NULL) {
        exit (0);
    }
    new->c = c;
    new->l = l;
    new->v = v;
    new->next = NULL;

    return new;
}

Paredes_partidas *add_to_list(Paredes_partidas *head, Paredes_partidas *new) {
    if (head == NULL) {
        head = new;
    } else {
        new->next = head;
        head = new;
    }
    return head;
}

void *free_list_pp(Paredes_partidas *head) {
    Paredes_partidas *aux;
    
    while (head != NULL) {
        aux = head;
        free(head);
        head = aux->next;
    }
}