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
    struct Lablist* next;
} LabList;

/* creates a MazeList item ready to be inserted in a list of mazes */
LabList* newLabList(Labirinto* m);

void freelist(LabList* head);

/* Creates a Maze and inserts it in the list */
LabList* addLab(LabList* head, LabList* ML, Labirinto* m);

/* Build the maze list from a file */
LabList* readLab(FILE* filePtr, LabList *head);

/* Get a single Maze from a file */
Labirinto* inputLab(FILE* filePtr);

//void showLab(Labirinto* m);

//void printStrArray(int dim, char** strArray, char* name);

/* Terminates if allocation failled */
void checkAllocationError(const void* ptr, const char* errorMsg);

void alloc_tabuleiro(Labirinto *);
void free_tabuleiro(Labirinto *);

#endif
