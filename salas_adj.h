#ifndef salas_adjHeader
#define salas_adjHeader

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "roap.h"
#include "modosA.h"
#include "salas.h"

#include "pg2.h"
#include "linked_list.h"

Graph *criar_grafo_salas (LabList *, Sala *, Graph *);

int ligacao_possivel_salas(LabList *, Sala *, Sala *, Parede *);
int A6_modded (LabList *, int, int, Sala *);
void reset_tab(Labirinto *);
int procurar_coord (A6_coord *, int, int);

#endif