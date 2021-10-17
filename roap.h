/*
    Roap definitions
*/
#ifndef ROAP
#define ROAP

#include <stdio.h>

//#define DEBUG      1
#define BUFFERSIZE 5

typedef struct Labirinto {
    /* dimensao do labirinto ints L e C */
    /* ints Lt e Ct das coordenadas do ponto de chegada */
    /* int P celulas negras/cinzentas */
    int L, C, cel_L, cel_C, P;
    int modo;           // 1..6
    int cel_2_L, cel_2_C;         // same room test coords
    int **tabuleiro;
} Labirinto;

/* Strictly has just one maze, however it also iterates the maze list */
typedef struct LabList {
    Labirinto* lab;
    struct LabList* next;
} LabList;

/* Get a single Maze from a file */
Labirinto* inputLab(FILE* filePtr);

/* Terminates if allocation failled */
void checkAllocationError(const void* ptr, const char* errorMsg);

void alloc_tabuleiro(Labirinto *);
void free_tabuleiro(Labirinto *);

LabList *criar_No_Lab (FILE *);
LabList *insert_in_list (LabList *, LabList *);
void result_A (LabList *, FILE*);
void free_lista(LabList *);

#endif
