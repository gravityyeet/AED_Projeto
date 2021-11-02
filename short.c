#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "short.h"

void short_path(FILE *ptr) {
    LabList* head = NULL, *node;

    while (feof(ptr) == 0) {
        node = criar_No_Lab(ptr);
        head = insert_in_list(head, node);
    }

    print_tabuleiro(head->lab);
}