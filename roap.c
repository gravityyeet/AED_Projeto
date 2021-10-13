/*
    Roap library
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "roap.h"


/* void printStrArray(int dim, char** strArray, char* name) {
    if (name) printf("%s:\n", name);
    for (int i=0; i<dim; i++) {
        printf("  %d: \"%s\" \n", i, strArray[i]);
    }
    printf("\n");
} */



/*void showLab(Labirinto* m) {
    // sort blocks and treasure for row then col
    // print blocks, treasure, boundaries
} */

LabList* newLabList(Labirinto* m) {
    LabList* newML = calloc(1, sizeof(LabList) );
    checkAllocationError(newML, "Error allocating labList");

    newML->lab = m;
    newML->next = NULL;

    return newML;
}



LabList* addLab(LabList* head, LabList* ML, Labirinto* m) {
    ML = newLabList(m);
    LabList* aux;

    if (head == NULL)
    {
        head = ML;
    }
    else
    {
        aux = head;
        while (aux-> next != NULL)
        {
            aux = aux-> next;
        }
    aux-> next = ML;
    ML-> lab = m;
    }

    return head;
}



void checkAllocationError(const void* ptr, const char* errorMsg) {
    if ( ! ptr ) {
        printf("\n%s\n", errorMsg);
        exit(EXIT_FAILURE);
    }
}



Labirinto* inputLab(FILE* filePtr) {
    char buffer[BUFFERSIZE];
    int lines, cols, celLine, celCol;

    int conversions = fscanf(filePtr, "%d %d %d %d",
        &lines, &cols, &celLine, &celCol);

    if( conversions != 4 ) {    // EOF
        printf("\n EOF with conversions=%d \n", conversions);
        return NULL;
    }

    Labirinto* m = calloc(1, sizeof(Labirinto) );
    checkAllocationError(m, "Erro ao alocar labirinto! m");

    m->L= lines;
    m->C = cols;
    m->cel_L = celLine;
    m->cel_C = celCol;

    printf("conversions:%d size: %d %d treasure: %d %d \n",
        conversions, m->L, m->C, m->cel_L, m->cel_C);

    conversions = fscanf(filePtr, "%s", buffer);

    printf("conversions:%d buffer=[%s] \n", conversions, buffer);

    if (buffer[0]=='A') {
        m->modo = buffer[1]-'0';
        if (m->modo == 6) {
            conversions = fscanf(filePtr, "%d %d", &m->cel_2_L, &m->cel_2_C);
            printf("conversions:%d same room? %d %d \n",
                                conversions, m->cel_2_L, m->cel_2_C);
        }
        conversions = fscanf(filePtr, "%d", &m->P);
    } else {
        m->modo = 0;
        buffer[BUFFERSIZE-1] = '\0';
        conversions = sscanf(buffer, "%d", &m->P);
    }

    printf("conversions: %d modo=%d P=%d \n",
                       conversions, m->modo, m->P);

    alloc_tabuleiro(m);

    return m;
}



/* Verifica se isto ta feito corretamente */
LabList* readLab(FILE* filePtr, LabList *head) {

    LabList* nextLabList = head;

    while( !feof(filePtr) ) {
        Labirinto* m = inputLab(filePtr);
        if (m) {
            addLab(head, nextLabList, m);
            //showLab(m);
        }
    }

    return head;
}

void freelist(LabList* head)
{
    LabList* aux;

    aux = head;
    while (head != NULL)
    {
        aux = head;
        head = head-> next;
        free_tabuleiro(aux->lab);
        free (aux->lab);
        free (aux);
    }
}

/* Alloc e free do tabuleiro 2D sugerido */
void alloc_tabuleiro(Labirinto *lab) {
    lab->tabuleiro = (int **) malloc(sizeof(int *) * lab->L);
    if (lab->tabuleiro == NULL) {
        exit(EXIT_FAILURE);
    } 
    for (int alloc_c = 0; alloc_c < lab->L; alloc_c++) {
        lab->tabuleiro[alloc_c] = (int *) malloc(sizeof(int) * lab->C);
        if (lab->tabuleiro[alloc_c] == NULL) {
            exit(EXIT_FAILURE);
        }
    }
}

void free_tabuleiro(Labirinto *lab) {
    int linhas = lab->L;

    for (int t = 0; t < lab->L; t++) {
        free(lab->tabuleiro[t]);
    }
    free(lab->tabuleiro);
}



















