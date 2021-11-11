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

Edge *gets_edge(Graph *graph, int sala1, int sala_vizinha) {
  LinkedList *list, *aux;
  Edge *edge1, *edge2;

  list = graph->adj[sala1];
  aux = graph->adj[sala_vizinha];

  /* Checks first adjacent vertice */
  if (list != NULL) {
    edge1 = (Edge *)getItemLinkedList(list);

    if (aux != NULL) {
      edge2 = (Edge *)getItemLinkedList(aux);
      if (edge1->l == edge2->l && edge1->c == edge2->c) {
        return edge1;
      }
    }
    aux = graph->adj[sala_vizinha];
    while ((aux = getNextNodeLinkedList(aux)) != NULL) {
      edge2 = (Edge *)getItemLinkedList(aux);
      if (edge1->l == edge2->l && edge1->c == edge2->c) {
        return edge1;
      }
    }
  }

  /* Checks adjacent vertices */
  aux = graph->adj[sala_vizinha];
  while ((list = getNextNodeLinkedList(list)) != NULL)
  {
    edge1 = (Edge *)getItemLinkedList(list);
    if (aux != NULL) {
      edge2 = (Edge *)getItemLinkedList(aux);
      if (edge1->l == edge2->l && edge1->c == edge2->c) {
        return edge1;
      }
    }
    aux = graph->adj[sala_vizinha];
    while ((aux = getNextNodeLinkedList(aux)) != NULL) {
      edge2 = (Edge *)getItemLinkedList(aux);
      if (edge1->l == edge2->l && edge1->c == edge2->c) {
        return edge1;
      }
    }
  }
  return NULL;
}

void WritesGraph(Graph *graph) {
  LinkedList *list;
  Edge *edge;

  /* Prints number of vertices */
  printf("%d\n", graph->V);

  /* Prints lists of adjacency vertices */
  for (int i = 0; i < graph->V; i++)
  {
    list = graph->adj[i];

    /* Writes first adjacent vertice */
    if (list != NULL)
    {
      edge = (Edge *)getItemLinkedList(list);
      printf("%d:%d ", edge->V, edge->W);
    }

    /* Writes adjacent vertices */
    while ((list = getNextNodeLinkedList(list)) != NULL)
    {
      edge = (Edge *)getItemLinkedList(list);
      printf("%d:%d ", edge->V, edge->W);
    }
    /* Writes end of list */
    printf("%d\n", (-1));
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

Edge *criar_No_edge (int linha, int coluna, int val) {

    Edge *newnode;

    newnode = (Edge *) calloc(1, sizeof(Edge));
    if(newnode == NULL) {
        exit(0);
    }

    newnode->l = linha;
    newnode->c = coluna;
    newnode->W = val; 

    return newnode;
}

Edge *inserir_lista_edge (Edge *head, Edge *node) {

  if (head == NULL) {
    head = node;
  } else {
    node->next = head;
    head = node;
  }

  return head;
}

void print_edges (Edge *head) {
  Edge *node;

  node = head;
  while (node != NULL) {
    printf ("%d %d %d\n", node->l, node->c, node->W);
    node = node->next;
  }
}

void free_edges(Edge *h) {
  Edge *aux;

  aux = h;
  while (h != NULL) {
    aux = h;
    h = h->next;
    free(aux);
  }
}