#ifndef dijkstraHeader
#define dijkstraHeader

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pq.h"
#include "pg2.h"
#include "linked_list.h"

#define inf 999     // May lead to some problems. Maybe needs to be bigger (See maximum double value)

void dijkstra(Graph *, int, int *, int *);
void print_caminho(Graph *, int *, int *, int, int);

#endif