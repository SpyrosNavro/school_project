#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "graph.h"
#include "pqueue.h"

void check_neighbors(Graph graph, int id, PQ queue[]);
void check_reverse_neighbors(Graph graph, int id, PQ queue[]);
int update_edges(PQ queue[], Graph graph, int row, int nedges, int temp[]);
void search_neighbors(Graph graph, PQ search_queue, Node search_node, int seed, int nedges, int* add);
void search_reverse_neighbors(Graph graph, PQ search_queue, Node search_node, int seed, int* add);