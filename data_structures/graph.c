#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nnodes 6

struct Graph {
    struct Node* nodes[nnodes];
};

// structure of nodes 
struct Node {
    int x, y;  // coordinates of point
    int id;    // id of point 
    // struct Node* next;  not useful for now
};

// structure of edge
struct Edge {
    int src, dest, weight;
};

struct Graph* createGraph (int nedges) 
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    srand(time(0));

    // initialise nodes 
    for (int i = 0; i < nnodes; i++) {
        graph->nodes[i]->x = rand();
        graph->nodes[i]->y = rand();
        graph->nodes[i]->id = i++;
    }

    // add edges to the directed graph one by one
    for (int id = 0; id < nnodes; id++)
    {
        for (int j = 0; j < nedges; j++)
        {
            struct Edge* edge = (struct Edge*)malloc(sizeof(struct Edge));
            
            edge->src = id;
            do 
            {
                edge->dest = rand();
            } while ( (edge->dest == id) && (edge->dest < 0) && (edge->dest >= nnodes) );
        }
    }

    return graph;
}