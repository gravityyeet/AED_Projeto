#ifndef pg2header
#define pg2header

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

typedef struct _Graph
{
  int V;              // Number of vertex
  int E;              // Number of edges
  Listaadj **adj;   // Array of pointers to list
} Graph;

void WritesGraph(Graph *);
void FreeGraph(Graph *);
Edge *gets_edge(Graph *, int, int);

Edge *criar_No_edge (int, int, int);
Edge *inserir_lista_edge (Edge *, Edge *);
void print_edges (Edge *, FILE *);
void free_edges(Edge *);

#endif