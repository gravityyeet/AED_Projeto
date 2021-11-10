#ifndef pg2header
#define pg2header

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

typedef struct _Graph
{
  int V;
  int E;
  LinkedList **adj;
} Graph;

typedef struct _Edge
{
  int V;
  int W;
} Edge;

Graph *ReadGraph(FILE *);
void WritesGraph(FILE *, Graph *);
void FreeGraph(Graph *);
void pg2();

#endif