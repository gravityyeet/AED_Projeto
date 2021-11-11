#ifndef pqHeader
#define pqHeader

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _PQ {
    int V;
    struct _PQ *next;
} PQ;

PQ *PQcreateNode(int);
PQ *PQinsert (PQ *, PQ *, int *);
int PQempty (PQ *);
PQ *PQdec(PQ *, int, int *);
PQ *PQdelmin(PQ *, int *);

#endif