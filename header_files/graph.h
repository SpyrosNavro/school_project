#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6

struct Graph {
    struct Node* nodes[N];
};

struct Node {
    int x, y;
    int dest;
    struct Node* next;
};

struct Edge {
    int src, dest, weight;
};

struct Graph* createGraph (struct Edge edges[], int n) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    srand(time(0));

    for (int i = 0; i < n; i++) {
        graph->nodes[i]->x = rand();
        graph->nodes[i]->y = rand();
    }
}