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
} Edge;

Graph *ReadGraph(FILE *);
void WritesGraph(FILE *, Graph *);
void FreeGraph(Graph *);
void pg2();

#endif