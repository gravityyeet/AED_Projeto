#ifndef salas_adjHeader
#define salas_adjHeader

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "roap.h"
#include "modosA.h"
#include "salas.h"

#include "pg2.h"
#include "LinkedList.h"

Graph *criar_grafo_salas (Sala *, Graph *);
Parede *comparar_salas(Sala *, Sala *);

#endif