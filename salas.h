#ifndef salasHeader
#define salasHeader

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "roap.h"

typedef struct _Parede {
    int l, c;
    struct _Parede *next;
} Parede;

typedef struct _Sala {
    int l, c;               // Coords que definem a sala
    Parede *paredes_sala;   // Apontador para a lista com as paredes da sala
    struct _Sala *next;
} Sala;

void print_tabuleiro(Labirinto *);
Parede *A6_salas (LabList *, int, int, Parede *);
Sala *analisar_salas (LabList *, int, int);
void ver_paredes_sala (Sala *, LabList *);

void print_paredes (Parede *);
Parede *criar_No_Parede (int, int);
Parede *inserir_lista_Parede (Parede *, Parede *);

Sala *criar_sala (int, int, Parede *);
Sala *inserir_lista_sala (Sala *, Sala *);

void free_parede(Parede *);
void free_sala(Sala *);

#endif