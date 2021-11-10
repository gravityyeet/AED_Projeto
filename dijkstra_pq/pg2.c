#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

#include "pg2.h"

Graph *ReadGraph(FILE *fpIn)
{
  int i, v1, v2, w;
  Edge *edge;

  /* Allocates Graph */
  Graph *graph = (Graph *)malloc(sizeof(Graph));
  if (graph == NULL)
  {
    printf("ERROR: Unable to allocate memory\n");
    exit(3);
  }

  /* Reads number of vertices */
  if (fscanf(fpIn, "%d", &graph->V) != 1)
  {
    printf("ERROR: Unable to read number of vertices\n");
    exit(4);
  }

  /* Reads number of edges */
  if (fscanf(fpIn, "%d", &graph->E) != 1)
  {
    printf("ERROR: Unable to read number of edges\n");
    exit(5);
  }

  /* Allocates vertices array list */
  graph->adj = (LinkedList **)malloc(graph->V * sizeof(LinkedList *));
  if (graph->adj == NULL)
  {
    printf("ERROR: Unable to allocate memory\n");
    exit(3);
  }
  for (i = 0; i < graph->V; i++)
  {
    graph->adj[i] = initLinkedList();
  }

  /* Reads graph */
  for (i = 0; i < graph->E; i++)
  {
    /* Reads edge form input file */
    if (fscanf(fpIn, "%d %d %d", &v1, &v2, &w) != 3)
    {
      printf("ERROR: Unable to read graph edge\n");
      exit(6);
    }

    /* Allocates new v1 edge */
    edge = (Edge *)malloc(sizeof(Edge));
    if (edge == NULL)
    {
      printf("ERROR: Unable to allocate memory\n");
      exit(3);
    }

    /* Saves v2 to v1 adjacency list */
    edge->V = v2;
    edge->W = w;
    graph->adj[v1] = insertUnsortedLinkedList(graph->adj[v1], (Item)edge);

    /* Allocates new v2 edge */
    edge = (Edge *)malloc(sizeof(Edge));
    if (edge == NULL)
    {
      printf("ERROR: Unable to allocate memory\n");
      exit(3);
    }

    /* Saves v1 to v2 adjacency list */
    edge->V = v1;
    edge->W = w;
    graph->adj[v2] = insertUnsortedLinkedList(graph->adj[v2], (Item)edge);
  }

  return graph;
}

void WritesGraph(FILE *fpOut, Graph *graph)
{
  LinkedList *list;
  Edge *edge;

  /* Prints number of vertices */
  fprintf(fpOut, "%d\n", graph->V);

  /* Prints lists of adjacency vertices */
  for (int i = 0; i < graph->V; i++)
  {
    list = graph->adj[i];

    /* Writes first adjacent vertice */
    if (list != NULL)
    {
      edge = (Edge *)getItemLinkedList(list);
      fprintf(fpOut, "%d:%d ", edge->V, edge->W);
    }

    /* Writes adjacent vertices */
    while ((list = getNextNodeLinkedList(list)) != NULL)
    {
      edge = (Edge *)getItemLinkedList(list);
      fprintf(fpOut, "%d:%d ", edge->V, edge->W);
    }
    /* Writes end of list */
    fprintf(fpOut, "%d\n", (-1));
  }

  return;
}

void FreeGraph(Graph *graph)
{

  for (int i = 0; i < graph->V; i++)
  {
    if (graph->adj[i] != NULL)
      freeLinkedList(graph->adj[i], free);
    
  }
  free(graph->adj);
  free(graph);

  return;
}

void pg2() {
  FILE *fpIn, *fpOut;
  char *input_name = "grafo4.edge";
  char *output_name = "grafo4.ladj";

  fpIn = fopen(input_name, "r");
  if (fpIn == NULL)
  {
    exit(2);
  }

  Graph *graph = ReadGraph(fpIn);

  fclose(fpIn);

  fpOut = fopen(output_name, "w");
  if (fpOut == NULL)
  {
    exit(2);
  }

  WritesGraph(fpOut, graph);

  fclose(fpOut);

  FreeGraph(graph);
}