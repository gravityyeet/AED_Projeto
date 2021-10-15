/*
    Entry point of RAIDERS OF ALL PYRAMIDS (Roap)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "roap.h"
#include "modosA.h"


int main(int argc, char** argv) {
    FILE* filePtr;
    LabList* head = NULL, *node;
    int value_out = 0;
    int DEBUG_COUNTER = 0;

    //if (DEBUG) printStrArray(argc, argv, "cmdln args");

    if (argc != 3) {
         printf("Numero de argumentos errado! \n");
        exit(EXIT_FAILURE);
    }

    char flag[] = "-s";

    if ( strcmp(argv[1]  , flag) != 0 )
    {
        fprintf(stdout, "Flag '-s' necessária para esta fase do projeto!"); //verifica se a flag -s está presente
        exit(EXIT_FAILURE);
    }

    char *filename;     // DECLARACAO LA PARA CIMA
    char *extencao, *aux;

    extencao = (char *) malloc (strlen(argv[2]) + 1);
    if (extencao == NULL) {
        exit(EXIT_FAILURE);
    }
    strcpy(extencao, argv[2]);
    aux = strchr(extencao, '.');
    if (aux == NULL) {
        exit(EXIT_FAILURE);
    }
    if (strcmp(aux, ".in1") != 0) {
        exit(EXIT_FAILURE);
    }
    filename = (char *) malloc (strlen(argv[2]) + 2);
    if (filename == NULL) {
        exit(EXIT_FAILURE);
    }
    filename[0] = '\0';
    strcpy(filename, argv[2]);
    strtok(filename, ".");

    filePtr = fopen(argv[2], "r");
    if (filePtr == NULL) {
        printf("Erro ao abrir o ficheiro %s !\n", argv[2]);
        exit(EXIT_FAILURE);
    }
    
    while (feof(filePtr) == 0) {
        node = criar_No_Lab(filePtr);
        head = insert_in_list(head, node);
        DEBUG_COUNTER++;        // DEBUG RETIRAR NA VERSAO FINAL
    }
    fclose(filePtr);

    FILE* file_out = fopen( strcat(filename, ".sol1") , "w");

    node = head;
    while (node != NULL) {
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
            case 6:
                //trata do big boss desta fase
            default:
                exit(EXIT_FAILURE);
                break;
        }
        fprintf(file_out, "%d\n\n", value_out);
        node = node->next;
    }

    fclose(file_out);

    free_lista(head);
    free(filename);
    free(extencao);

    return EXIT_SUCCESS;
}

