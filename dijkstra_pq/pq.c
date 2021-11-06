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
PQ *PQinsert (PQ *head, PQ *node, double distancia[]) {
    PQ *aux1, *aux2;

    if (head == NULL) {
        head = node;
    } else {
        if (distancia[head->V] < distancia[node->V]) {
            node->next = head;
            head = node;
        } else {
            aux1 = head;
            aux2 = head->next;
            while (distancia[node->V] > distancia[aux1->V] && aux2 != NULL) {
                aux1 = aux2;
                aux2 = aux2->next;
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

void PQdec(PQ *head, int v, double distancia[]) {
    PQ *aux1, *aux2, *temp;

    aux1 = head;
    aux2 = head->next;
    while (aux2 != NULL) {
        if (aux2->V == v) {
            aux1->next = aux2->next;
            temp = aux2;        // temp = endereço na PQ do vertice a mudar a sua prioridade
            break;
        }
        aux1 = aux2;
        aux2 = aux2->next;
    }
    // Inserir temp na PQ com a nova distancia
    if (distancia[head->V] < distancia[temp->V]) {
        temp->next = head;
        head = temp;
    } else {
        aux1 = head;
        aux2 = head->next;
        while (distancia[temp->V] > distancia[aux1->V] && aux2 != NULL) {
            aux1 = aux2;
            aux2 = aux2->next;
        }
        temp->next = aux2;
        aux1->next = temp;
    }
}

int PQdelmin(PQ *head) {
    PQ *aux;
    int vret = head->V;

    aux = head;
    head = head->next;
    free(aux);

    return vret;
}