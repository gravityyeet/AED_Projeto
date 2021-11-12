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
#include "dijkstra.h"

#include "pg2.h"

int main(int argc, char** argv) {
    FILE* filePtr, *file_out;
    LabList* head = NULL, *node;
    char *filename, *extensao, *aux, *input_str;
    int fase_proj = 0;  // (fase = 0) == Fase Final; (fase = 1) == Fase Intermedia
    Sala *salas_head = NULL;
    int c = 0;

    Graph *graph;
    int *st;
    int *dist;

    if (argc < 2) {
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

    /* Verificao se a extensao usada no input do ficheiro esta correta */
    extensao = (char *) malloc (strlen(input_str) + 1);
    if (extensao == NULL) {
        exit(0);
    }

    strcpy(extensao, input_str);

    aux = strrchr(extensao, '.');
    if (aux == NULL) {
        free(extensao);
        exit(0);
    }
    if (fase_proj == 0) {
        if (strcmp(aux, ".in") != 0) {
            free(extensao);
            exit(0);
        }
    } else {
        if (strcmp(aux, ".in1") != 0) {
            free(extensao);
            exit(0);
        }
    }

    /* Junçao de extensao de saida ao nome do ficheiro */
    filename = (char *) malloc (strlen(input_str) + 2);
    if (filename == NULL) {
        free(extensao);
        exit(0);
    }
    filename[0] = '\0';
    strcpy(filename, input_str);
    strtok(filename, ".");

    filePtr = fopen(input_str, "r");
    if (filePtr == NULL) {
        free(extensao);
        free(filename);
        exit(0);
    }

    if (fase_proj == 0) {
        file_out = fopen( strcat(filename, ".sol") , "w");

        /* Enquanto for encontrando informaçao, vai criando labirintos      *
        *  e colocando o seu resultado, segundo o A definido no ficheiro   *
        *  num ficheiro file_out                                           */
        while (feof(filePtr) == 0) {
            if (c > 0) {
                fprintf(file_out, "\n\n");
            }
            c++;

            // Criar grafo
            graph = (Graph *)malloc(sizeof(Graph));
            if (graph == NULL){
                exit(0);
            }
            
            node = criar_No_Lab(filePtr);
            if (node == NULL) {
                fprintf(file_out, "-1\n");
                free(graph);
                continue;
            }
            head = insert_in_list(head, node);
            //print_tabuleiro(node->lab);

            if (node->lab->tabuleiro[node->lab->cel_L][node->lab->cel_C] != 0) {
                fprintf(file_out, "-1\n");
                free(graph);
                continue;
            }

            salas_head = analisar_salas(node, 1, 1, fase_proj);
            // Apontador para a lista de salas

            // Dps cria se aqui uma outra funcao para fazer o resto que precisamos
            graph = criar_grafo_salas(head, salas_head, graph);

            st = (int *) malloc (sizeof(int) * graph->V);
            if (st == NULL) {
                exit(0);
            }

            dist = (int *) malloc (sizeof(int) * graph->V);
            if (dist == NULL) {
                exit(0);
            }
            
            //WritesGraph(graph);

            dijkstra(graph, 0, st, dist);
            print_caminho(graph, st, dist, sala_destino(salas_head), 0, file_out);

            free_sala(salas_head);
            free(st);
            free(dist);
            FreeGraph(graph);

        }
    }

    if (fase_proj == 1) {
        file_out = fopen( strcat(filename, ".sol1") , "w");
        while (feof(filePtr) == 0) {
            node = criar_No_Lab(filePtr);
            head = insert_in_list(head, node);
            result_A(node, file_out);
        }
    }

    fclose(filePtr);
    fclose(file_out);
    free_lista(head);
    free(filename);
    free(extensao);

    return 0;
}