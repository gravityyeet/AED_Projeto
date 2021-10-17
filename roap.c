/*
    Roap library
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "roap.h"
#include "modosA.h"

void checkAllocationError(const void* ptr, const char* errorMsg) {
    if ( ! ptr ) {
        //printf("\n%s\n", errorMsg);
        exit(0);
    }
}

void result_A (LabList *node, FILE *file_out) {
    int value_out = -10;

    switch (node->lab->modo) {
        case 1:
            value_out = A1(node);
            break;
        case 2:
        case 3:
        case 4:
            value_out = A2_4(node, node->lab->modo);
            break;
        case 5: 
            value_out = A5(node);
            break;
        case 6:
            value_out = A6(node, node->lab->cel_L, node->lab->cel_C);
            break;
        default:
            value_out = -10;
            break;
    }
    fprintf(file_out, "%d\n\n", value_out);
    free_tabuleiro(node->lab);
    free(node->lab);
}

void free_lista(LabList *head) {
    LabList *aux;

    aux = head;

    while (head != NULL) {
        aux = head;
        head = head->next;
        free(aux);  
    }
}

LabList *criar_No_Lab (FILE *fp) {

    LabList *newnode;

    newnode = (LabList *) malloc(sizeof(LabList));
    if(newnode == NULL) {
        exit(0);
    }

    newnode->lab = inputLab(fp);
    newnode->next = NULL;

    return newnode;
}

LabList *insert_in_list (LabList *head, LabList *innode) {

    LabList *auxA, *auxN;

    if (head == NULL) {
        head = innode;
    } else {
        auxA = head;
        auxN = head->next;
        while (auxN != NULL) {
            auxA = auxN;
            auxN = auxN->next;
        }
        auxA->next = innode;
    }
    return head;
}



Labirinto* inputLab(FILE* filePtr) {
    char buffer[BUFFERSIZE];
    int lines, cols, celLine, celCol;
    int parede1 = 0, parede2 = 0, parede_v = 0;

    int conversions = fscanf(filePtr, "%d %d %d %d",
        &lines, &cols, &celLine, &celCol);

    if( conversions != 4 ) {    // EOF
        //printf("\n EOF with conversions=%d \n", conversions);
        return NULL;
    }

    Labirinto* m = calloc(1, sizeof(Labirinto) );
    checkAllocationError(m, "Erro ao alocar labirinto! m");

    m->L= lines;
    m->C = cols;
    m->cel_L = celLine;
    m->cel_C = celCol;

    //printf("conversions:%d size: %d %d treasure: %d %d \n",
    //    conversions, m->L, m->C, m->cel_L, m->cel_C);

    conversions = fscanf(filePtr, "%s", buffer);
    if (conversions != 1) {
        return NULL;
    }

    //printf("conversions:%d buffer=[%s] \n", conversions, buffer);

    if (buffer[0]=='A') {
        m->modo = buffer[1]-'0';
        if (m->modo == 6) {
            conversions = fscanf(filePtr, "%d %d", &m->cel_2_L, &m->cel_2_C);
            //printf("conversions:%d same room? %d %d \n",
            //                    conversions, m->cel_2_L, m->cel_2_C);
            if (conversions != 2) {
                return NULL;
            }
        }
        conversions = fscanf(filePtr, "%d", &m->P);
        if (conversions != 1) {
            return NULL;
        }
    } else {
        m->modo = 0;
        buffer[BUFFERSIZE-1] = '\0';
        conversions = sscanf(buffer, "%d", &m->P);
        if (conversions != 1) {
            return NULL;
        }
    }

    //printf("conversions: %d modo=%d P=%d \n",
    //                   conversions, m->modo, m->P);

    /* Alloc and read info from file to tabuleiro */
    alloc_tabuleiro(m);
    for (int t = 0; t < m->P; t++) {
        conversions = fscanf(filePtr, "%d %d %d", &parede1, &parede2, &parede_v);
        if (conversions != 3) {
            return NULL;
        }
        m->tabuleiro[parede1][parede2] = parede_v;
    }

    /* Criacao das bordas do tabuleiro */
    for (int t = 0; t < m->C + 2; t++) {
        m->tabuleiro[0][t] = -2;
        m->tabuleiro[m->L + 1][t] = -2;
    }
    for (int t = 0; t < m->L + 2; t++) {
        m->tabuleiro[t][0] = -2;
        m->tabuleiro[t][m->C + 1] = -2;
    }  

    conversions = fscanf(filePtr, " ");
    return m;
}

/* Alloc e free do tabuleiro 2D sugerido */
void alloc_tabuleiro(Labirinto *lab) {
    lab->tabuleiro = (int **) calloc(1, sizeof(int *) * (lab->L + 2));
    if (lab->tabuleiro == NULL) {
        exit(0);
    } 
    for (int alloc_c = 0; alloc_c < lab->L + 2; alloc_c++) {
        lab->tabuleiro[alloc_c] = (int *) calloc(1, sizeof(int) * (lab->C + 2));
        if (lab->tabuleiro[alloc_c] == NULL) {
            exit(0);
        }
    }
}

void free_tabuleiro(Labirinto *lab) {

    for (int t = 0; t < lab->L + 2; t++) {
        free(lab->tabuleiro[t]);
    }
    free(lab->tabuleiro);
}



















