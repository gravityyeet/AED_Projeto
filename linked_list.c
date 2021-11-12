#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pg2.h"
#include "linked_list.h"


Listaadj *initListabase()
{
	Listaadj *head = NULL;
	return head;
}

Listaadj *novo_no (int l, int c, int v, int w) {
	Listaadj *new;

	new = (Listaadj *) malloc(sizeof(Listaadj));
	if(new == NULL) {
        exit(0);
    }

	new->aresta = (Edge *) malloc(sizeof(Edge));
	if(new->aresta == NULL) {
        exit(0);
    }

	new->aresta->l = l;
	new->aresta->c = c;
	new->aresta->V = v;
	new->aresta->W = w;
	new->next = NULL;

	return new;
}

void freeLLista(Listaadj* head)
{
	Listaadj* aux_main;
	aux_main = head;

	while (head != NULL)
	{
		aux_main = head;
		head = head->next;
		free(aux_main->aresta);
		free(aux_main);		
	}
}

Listaadj *getNextNodeLList(Listaadj* node)
{
	if (node == NULL)
	{
		return NULL;
	}
	else
	{
		return node->next;
	}
}

Listaadj* insertllist(Listaadj* head, Listaadj* node)
{
	if (head == NULL) {
    	head = node;
  	} else {
    	node->next = head;
    	head = node;
  	}

  return head;
}

Edge* getEdgeFromLList(Listaadj* sub_node)
{
	if (sub_node == NULL)
	{
		return NULL;
	}
	else {
		return sub_node->aresta;
	}

}

