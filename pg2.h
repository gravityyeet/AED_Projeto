#ifndef pg2header
#define pg2header

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

typedef struct _Graph
{
  int V;              // Number of vertex
  int E;              // Number of edges
  LinkedList **adj;   // Array of pointers to list
} Graph;

typedef struct _Edge
{
  int V;    // Adj vertex
  int W;    // Weight
  int l, c; // Coords da parede
  struct _Edge *next;
} Edge;

Graph *ReadGraph(FILE *);
void WritesGraph(Graph *);
void FreeGraph(Graph *);
Edge *gets_edge(Graph *, int, int);

Edge *criar_No_edge (int, int, int);
Edge *inserir_lista_edge (Edge *, Edge *);
void print_edges (Edge *);
void free_edges(Edge *);

#endif