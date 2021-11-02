/*
    Entry point of RAIDERS OF ALL PYRAMIDS (Roap)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "roap.h"
#include "modosA.h"
#include "short.h"


int main(int argc, char** argv) {
    FILE* filePtr, *file_out;
    LabList* head = NULL, *node;
    char *filename, *input_str;
    char *extencao, *aux;
    int fase_proj = 0;      // (fase = 0) == Fase Final; (fase = 1) == Fase Intermedia

    if (argc < 2) {
         //printf("Numero de argumentos errado! \n");
        exit(0);
    }

    if ( strcmp(argv[1]  , "-s") == 0 )
    {
        fase_proj = 1;
    }

    if (fase_proj == 0) {
        input_str = argv[1];
    } else {
        input_str = argv[2];
    }

    extencao = (char *) malloc (strlen(input_str) + 1);
    if (extencao == NULL) {
        exit(0);
    }

    strcpy(extencao, input_str);

    aux = strrchr(extencao, '.');
    if (aux == NULL) {
        free(extencao);
        exit(0);
    }

    if (fase_proj == 0) {
        if (strcmp(aux, ".in") != 0) {
            free(extencao);
            exit(0);
        }
    } else {
        if (strcmp(aux, ".in1") != 0) {
            free(extencao);
            exit(0);
        }
    }

    filename = (char *) malloc (strlen(input_str) + 2);
    if (filename == NULL) {
        free(extencao);
        exit(0);
    }
    filename[0] = '\0';
    strcpy(filename, input_str);
    strtok(filename, ".");

    filePtr = fopen(input_str, "r");
    if (filePtr == NULL) {
        //printf("Erro ao abrir o ficheiro %s !\n", input_str);
        free(extencao);
        free(filename);
        exit(0);
    }

    if (fase_proj == 0) {
        file_out = fopen( strcat(filename, ".sol") , "w");
        short_path(filePtr);
        fclose(file_out);
    }

    if (fase_proj == 1) {
        file_out = fopen( strcat(filename, ".sol1") , "w");
        while (feof(filePtr) == 0) {
            node = criar_No_Lab(filePtr);
            head = insert_in_list(head, node);
            result_A(node, file_out);
        }
        free_lista(head);
        fclose(file_out);
    }
    
    fclose(filePtr);
    free(filename);
    free(extencao);

    return 0;
}