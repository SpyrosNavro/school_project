#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "graph.h"
#include "pqueue.h"

typedef struct taskDis {
    void (*taskFunction)(Graph, int, PQ*);
    Graph graph;
    int id;
    PQ* pq;
} taskDis;

void executeTaskD(taskDis* task);
void submitTaskD(taskDis task);
void* startThreadD();

void checkNeighbors(Graph graph, int id, PQ queue[]);
void checkReverse(Graph graph, int id, PQ queue[]);
int updateEdges(PQ queue[], Graph graph, int row, int nedges);
void searchNeighbors(Graph graph, PQ search_queue, Node search_node, int seed, int nedges, int* add);
void searchReverse(Graph graph, PQ search_queue, Node search_node, int seed, int* add);
void localJoin(Graph graph, int id, PQ queue[]);
void RevlocalJoin(Graph graph, int id, PQ queue[]);
void brute_force_algorithm(Graph graph, int row, int nedges);