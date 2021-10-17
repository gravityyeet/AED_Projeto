/*
    Entry point of RAIDERS OF ALL PYRAMIDS (Roap)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "roap.h"
#include "modosA.h"


int main(int argc, char** argv) {
    FILE* filePtr, *file_out;
    LabList* head = NULL, *node;

    //if (DEBUG) printStrArray(argc, argv, "cmdln args");

    if (argc != 3) {
         //printf("Numero de argumentos errado! \n");
        exit(0);
    }

    char flag[] = "-s";

    if ( strcmp(argv[1]  , flag) != 0 )
    {
        fprintf(stdout, "Flag '-s' necessária para esta fase do projeto!"); //verifica se a flag -s está presente
        exit(0);
    }

    char *filename;     // DECLARACAO LA PARA CIMA
    char *extencao, *aux;

    extencao = (char *) malloc (strlen(argv[2]) + 1);
    if (extencao == NULL) {
        exit(0);
    }
    strcpy(extencao, argv[2]);
    aux = strrchr(extencao, '.');
    if (aux == NULL) {
        free(extencao);
        exit(0);
    }
    if (strcmp(aux, ".in1") != 0) {
        free(extencao);
        exit(0);
    }
    filename = (char *) malloc (strlen(argv[2]) + 2);
    if (filename == NULL) {
        free(extencao);
        exit(0);
    }
    filename[0] = '\0';
    strcpy(filename, argv[2]);
    strtok(filename, ".");

    filePtr = fopen(argv[2], "r");
    if (filePtr == NULL) {
        //printf("Erro ao abrir o ficheiro %s !\n", argv[2]);
        free(extencao);
        free(filename);
        exit(0);
    }
    file_out = fopen( strcat(filename, ".sol1") , "w");

    while (feof(filePtr) == 0) {
        node = criar_No_Lab(filePtr);
        head = insert_in_list(head, node);
        result_A(node, file_out);
    }
    fclose(filePtr);
    fclose(file_out);

    free_lista(head);
    free(filename);
    free(extencao);

    return 0;
}