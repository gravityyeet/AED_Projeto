#ifndef DECLARACOES_H_INCLUDED
#define DECLARACOES_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _PQ {
    int V;
    struct _PQ *next;
} PQ;

PQ *PQcreateNode(int);
PQ *PQinsert (PQ *, PQ *, double *);
int PQempty (PQ *);
PQ *PQdec(PQ *, int, double *);
PQ *PQdelmin(PQ *, int *);

#endif