
#ifndef Linked_ListHeader
#define Linked_ListHeader

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Edge
{
  int V;    // Adj vertex
  int W;    // Weight
  int l, c; // Coords da parede
  struct _Edge *next;
} Edge;

typedef struct _listaadj
{
	Edge *aresta;
	struct _listaadj* next;
} Listaadj;

typedef struct sublista Sublista;

Listaadj* initListabase();
Listaadj *novo_no (int, int, int, int);
Listaadj* insertllist(Listaadj* , Listaadj*);
Edge* getEdgeFromLList(Listaadj *);
Listaadj *getNextNodeLList(Listaadj *);
void freeLLista(Listaadj *);



#endif
