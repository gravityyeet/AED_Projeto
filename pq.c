#include "pq.h"

// Criar no para inserir na priority queue
PQ *PQcreateNode(int V) {
    PQ *node;

    node = (PQ *) malloc (sizeof(PQ));
    if (node == NULL) {
        exit(0);
    }
    node->V = V;
    node->next = NULL;

    return node;
}

// Inserir no na priority queue de forma ordenada por distancia (na head esta a mais pequena)
PQ *PQinsert (PQ *head, PQ *node, int distancia[]) {
    PQ *aux1, *aux2;

    if (head == NULL) {
        head = node;
    } else {
        if (distancia[head->V] > distancia[node->V]) {
            node->next = head;
            head = node;
        } else {
            aux1 = head;
            aux2 = head->next;
            while (aux2 != NULL) {
                if (distancia[node->V] > distancia[aux2->V]) {
                    aux1 = aux2;
                    aux2 = aux2->next;  
                } else {
                    break;
                }
            }
            node->next = aux2;
            aux1->next = node;
        }
    }
    return head;
}

// Verifica se a priority queue esta vazia
int PQempty (PQ *head) {
    if (head == NULL) {
        return 1;
    } else {
        return 0;
    }
}

// Atualiza a ordem da PQ
PQ *PQdec(PQ *head, int v, int distancia[]) {
    PQ *aux1, *aux2, *temp;

    // Encontrar o endereço do no a mudar e retira lo da PQ
    aux1 = head;
    aux2 = head->next;
    if (head->V == v) {
        temp = head;
        head = head->next;
    } else {
        while (aux2->V != v) {
            aux1 = aux2;
            aux2 = aux2->next;
        }
        temp = aux2;
        aux1->next = aux2->next;
    }

    // Inserir temp na PQ com a nova distancia
    if (head == NULL) {
        head = temp;
        temp->next = NULL;
    } else {
        if (distancia[head->V] > distancia[temp->V]) {
            temp->next = head;
            head = temp;
        } else {
            aux1 = head;
            aux2 = head->next;
            while (aux2 != NULL) {
                if (distancia[temp->V] > distancia[aux2->V]) {
                    aux1 = aux2;
                    aux2 = aux2->next;
                } else {
                    break;
                }
            }
            temp->next = aux2;
            aux1->next = temp;
        }
    }
    return head;
}

// Remove a head da PQ
PQ *PQdelmin(PQ *head, int *v1) {
    PQ *aux;
    
    *v1 = head->V;

    aux = head;
    head = head->next;
    free(aux);

    return head;
}