#ifndef DECLARACOES_H_INCLUDED
#define DECLARACOES_H_INCLUDED

#include "roap.h"

typedef struct A6_coord {
    int l;
    int c;
    struct A6_coord *next; 
} A6_coord;

A6_coord *criar_No_A6 (int, int);
A6_coord *inserir_lista_A6 (A6_coord *, A6_coord *);
A6_coord *remover_lista_A6 (A6_coord *, A6_coord *);
int procurar_tesouro (A6_coord *, LabList *);

int A1 (LabList *);
int A2_4 (LabList *, int);
int A5 (LabList *);
int A6 (LabList *, int, int);

#endif // DECLARACOES_H_INCLUDED