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
    LabList* head = NULL;
    int file_out_value = 0;

    //if (DEBUG) printStrArray(argc, argv, "cmdln args");

    if (argc != 3) {
         printf("Numero de argumentos errado! \n");
        exit(EXIT_FAILURE);
    }

    char flag[2] = "-s";

    if ( strcmp(argv[1], flag) != 0 )
    {
        fprintf(stdout, "Flag '-s' necess�ria para esta fase do projeto!"); //verifica se a flag -s est� presente
        exit(EXIT_FAILURE);
    }

    char *file_arg /*argumento indicado no terminal para referir ao ficheiro*/, *filename /*nome "pr�prio" do ficheiro*/, *file_arg_aux;
    char dot = '.';
    char ponto[] = ".";
    char *extencao;
    int read_ok;

    file_arg = (char*) calloc(1, strlen(argv[2]) ); //verifica se de facto a extens�o � .in1
    file_arg_aux = (char*) calloc(1, strlen(argv[2]) );
    strcpy(file_arg, argv[2]);
    strcpy(file_arg_aux, argv[2]);
    filename = strtok(file_arg, ponto);
    extencao = strrchr(file_arg_aux, dot);

    if ((read_ok = strcmp(extencao, ".in1")) != 0 )
    {
        fprintf(stdout, "Extens�o inv�lida!");
        exit(EXIT_FAILURE);
    }

    filePtr = fopen(argv[2], "r");

    if (filePtr == NULL) {
        printf("Erro ao abrir o ficheiro %s !\n", argv[2]);
        exit(EXIT_FAILURE);
    } else {
        head = readLab(filePtr, head);
        fclose(filePtr);
    }

    FILE *file_out = fopen( strcat(filename, ".sol1"), "w");

    LabList* aux;
    aux = head;

    while (aux!= NULL) {
        switch (aux-> lab-> modo)
            {
            case 1:
                file_out_value = A1(aux);
                aux = aux-> next;
                break;
            }
    }

    freelist(head);

    fprintf(file_out, "%d\n\n", file_out_value);

    fclose(file_out);

    return EXIT_SUCCESS;
}

