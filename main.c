/*
    Entry point of RAIDERS OF ALL PYRAMIDS (Roap)
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "roap.h"
#include "modosA.h"
#include "salas.h"
#include "salas_adj.h"

#include "pg2.h"

int main(int argc, char** argv) {
    FILE* filePtr, *file_out;
    LabList* head = NULL, *node;
    char *filename, *extensao, *aux;
    Sala *salas_head = NULL, *salas_node = NULL;

    Graph *graph;

    if (argc != 3) {
        exit(0);
    }

    char flag[] = "-s";

    if ( strcmp(argv[1]  , flag) != 0 )
    {
        exit(0);
    }

    /* Verificao se a extensao usada no input do ficheiro esta correta */
    extensao = (char *) malloc (strlen(argv[2]) + 1);
    if (extensao == NULL) {
        exit(0);
    }
    strcpy(extensao, argv[2]);
    aux = strrchr(extensao, '.');
    if (aux == NULL) {
        free(extensao);
        exit(0);
    }
    if (strcmp(aux, ".in1") != 0) {
        free(extensao);
        exit(0);
    }

    /* Junçao de extensao de saida ao nome do ficheiro */
    filename = (char *) malloc (strlen(argv[2]) + 2);
    if (filename == NULL) {
        free(extensao);
        exit(0);
    }
    filename[0] = '\0';
    strcpy(filename, argv[2]);
    strtok(filename, ".");

    filePtr = fopen(argv[2], "r");
    if (filePtr == NULL) {
        //printf("Erro ao abrir o ficheiro %s !\n", argv[2]);
        free(extensao);
        free(filename);
        exit(0);
    }

    file_out = fopen( strcat(filename, ".sol1") , "w");

    // Criar grafo
    graph = (Graph *)malloc(sizeof(Graph));
    if (graph == NULL){
        exit(0);
    }

    /* Enquanto for encontrando informaçao, vai criando labirintos      *
     *  e colocando o seu resultado, segundo o A definido no ficheiro   *
     *  num ficheiro file_out                                           */
    while (feof(filePtr) == 0) {
        node = criar_No_Lab(filePtr);
        if (node == NULL) {
            fprintf(file_out, "%d\n\n", -2);
            continue;
        }
        head = insert_in_list(head, node);
        print_tabuleiro(node->lab);

        salas_head = analisar_salas(head, 1, 1);
        // Apontador para a lista de salas

        // Dps cria se aqui uma outra funcao para fazer o resto que precisamos
        graph = criar_grafo_salas(salas_head, graph);

        result_A(node, file_out);
    }

    /* Free e close de tudo */
    salas_node = salas_head;
    while (salas_node != NULL) {
        free_parede(salas_node->paredes_sala);

        salas_node = salas_node->next;
    }
    free_sala(salas_head);

    fclose(filePtr);
    fclose(file_out);
    free_lista(head);
    free(filename);
    free(extensao);

    return 0;
}