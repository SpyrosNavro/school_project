#include "graph.h"

struct graph {
    Node* nodes;
    int dim, nnodes, neighbors;
};

// structure of nodes 
struct node {
    int* coord;  // coordinates of n-dimentional point
    int id;    // id of point 
    Edge edges[];
    // struct Node* next;  not useful for now
};

// structure of edge
struct edge {
    int src, dest, distance;
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





int compute_distance (Node a, Node b, int dim)
{
    int sum = 0;
    for (int i = 0; i < dim; i++) 
    {
        sum = sum + pow(a->coord[i] + b->coord[i], 2);
    }
    sum = sqrt(sum);
    return sum;
}





Graph createGraph (int nedges, const char *file_name, int row, int column) 
{
    Graph graph = malloc(sizeof(*graph));
    int** data = import_data(file_name, row, column);
    
    graph->dim = column;
    graph->nnodes = row;
    graph->neighbors = nedges;

    // initialise nodes 
    for (int id = 0; id < row; id++)
    {
        for (int j = 0; j < column; j++)
        {
            graph->nodes[id] = malloc(sizeof( *(graph->nodes[id]) ));   // allocate node
            graph->nodes[id]->coord[j] = data[id][j];                   // put data in node
            
            //*(graph->nodes[i]->coord + j) = data[i][j];
        }

        // add directed edges to each node
        for (int j = 0; j < nedges; j++)
        {
            Edge edge = malloc(sizeof(*edge));
            graph->nodes[id]->edges[j] = edge;
            edge->src = id;

            do 
            {
                edge->dest = rand();
                edge->distance = compute_distance(graph->nodes[id], graph->nodes[edge->dest], graph->dim);
            } while ( (edge->dest == id) && (edge->dest < 0) && (edge->dest >= graph->nnodes) );
        }
    }

    // add directed edges to each node
    // for (int id = 0; id < row; id++)
    // {
    //     for (int j = 0; j < nedges; j++)
    //     {
    //         Edge edge = malloc(sizeof(*edge));
    //         graph->nodes[id]->edges[j] = edge;
    //         edge->src = id;

    //         do 
    //         {
    //             edge->dest = rand();
    //         } while ( (edge->dest == id) && (edge->dest < 0) && (edge->dest >= graph->nnodes) );
    //     }
    // }

    return graph;
}





void deleteGraph(Graph graph)
{   
    for (int i = graph->nnodes - 1; i >= 0; i--)
    {
        for (int j = 0; j < graph->neighbors; j++)
        {
            free(graph->nodes[i]->edges[j]);
        }
        free(graph->nodes[i]);
    }

    free(graph);
    return 0;
}