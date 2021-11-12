#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "pg2.h"
#include "linked_list.h"

Edge *gets_edge(Graph *graph, int sala1, int sala_vizinha) {
  Listaadj *list, *aux;

  list = graph->adj[sala1];

  while (list != NULL) {
    aux = graph->adj[sala_vizinha];
    while (aux != NULL) {
      if (list->aresta->l == aux->aresta->l && list->aresta->c == aux->aresta->c) {
        return list->aresta;
      }
      aux = getNextNodeLList(aux);
    }
    list = getNextNodeLList(list);
  }

  return NULL;
}

void WritesGraph(Graph *graph) {
  Listaadj *list;
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
      edge = getEdgeFromLList(list);
      printf("%d %d %d:%d   ",edge->l, edge->c, edge->V, edge->W);
    }

    /* Writes adjacent vertices */
    while ((list = getNextNodeLList(list)) != NULL)
    {
      edge = getEdgeFromLList(list);
      printf("%d %d %d:%d   ",edge->l, edge->c, edge->V, edge->W);
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
      freeLLista(graph->adj[i]);
    
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

void print_edges (Edge *head, FILE *fp) {
  Edge *node;

  node = head;
  while (node != NULL) {
    fprintf (fp, "%d %d %d\n", node->l, node->c, node->W);
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