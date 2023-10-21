#include "graph.h"

#define nnodes 6

struct graph {
    Node nodes[nnodes];
    int dim;  // incomplete
};

// structure of nodes 
struct node {
    int* coord;  // coordinates of n-dimentional point
    int id;    // id of point 
    // struct Node* next;  not useful for now
};

// structure of edge
struct edge {
    int src, dest, weight;
};


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
    Graph graph = malloc(sizeof(*graph));
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
            Edge edge = malloc(sizeof(*edge));
            
            edge->src = id;
            do 
            {
                edge->dest = rand();
            } while ( (edge->dest == id) && (edge->dest < 0) && (edge->dest >= nnodes) );
        }
    }

    return graph;
}

void deleteGraph(Graph graph)
{
    return 0;
}