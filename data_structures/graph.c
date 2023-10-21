#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"

#define nnodes 6

typedef struct graph {
    Node* nodes[nnodes];
    int dim;
} Graph;

// structure of nodes 
typedef struct node {
    int* coord;  // coordinates of n-dimentional point
    int id;    // id of point 
    // struct Node* next;  not useful for now
} Node;

// structure of edge
typedef struct edge {
    int src, dest, weight;
} Edge;


int** import_data(const char *file_name, int row, int column)
{
    FILE* pointer;
    
    // atoi: char => int
    // fgetc: obtain input single character at a time. returns the ASCII code of the character read. it moves to the next character by itself

    pointer = fopen(file_name, "r");
    if (pointer == NULL) 
    {
        print("no file was found.");
        return 0;
    }

    while ( !(feof(pointer)) )
    {
        // insesrt char
        // transform string into int
        // save into node->coord
    }

    return 0;
}


Graph createGraph (int nedges, const char *file_name, int row, int column) 
{
    Graph* graph = (struct Graph*)malloc(sizeof(Graph));
    int** data = import_data(file_name, row, column);

    // initialise nodes 
    for (int row = 0; row < nnodes; row++)
    {
        for (int j = 0; j < column; j++)
        {
            *(graph->nodes[row]->coord + j) = data[row][column];
        }
    }

    // add edges to the directed graph one by one
    for (int id = 0; id < nnodes; id++)
    {
        for (int j = 0; j < nedges; j++)
        {
            Edge* edge = (struct Edge*)malloc(sizeof(Edge));
            
            edge->src = id;
            do 
            {
                edge->dest = rand();
            } while ( (edge->dest == id) && (edge->dest < 0) && (edge->dest >= nnodes) );
        }
    }

    return graph;
}