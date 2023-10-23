#include <stdio.h>
#include <stdlib.h>

//#include "graph.h"
/*
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




struct Graph* createGraph (int nedges, const char *file_name) 
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

*/

int** import_data(const char *file_name, int vrows)
{
    FILE* pointer;
     
    pointer = fopen(file_name, "r");  // reading the file 
    if (pointer == NULL) 
    {
        printf("no file was found.");
        return NULL;
    }
     
    int** vector = NULL; // dynamilly allocated array (vector of vectors )
    
    int vcol=3;
     
    
    vector = (int**) malloc(vrows * sizeof(int * )); // 2dimensional 
    if (vector == NULL){
        printf("error allocating memory for the vector");
        fclose(pointer);
        return NULL;
    }
    
    for (int i =0; i< vrows; i++){
        vector[i] = (int *)malloc(vcol * sizeof(int));  // 2D array , allocate memory for 3 elements of every row 
        
        if (vector[i] == NULL){
            printf("memory allocation error");
            free(vector);
            fclose(pointer);
             
        }

    }

    

    // save the elements of the file inside the vector (every row has three columns - its coordinates )
    for (int i= 0; i < vrows; i++){
        int j=0;
        int indicator=0;
        
            if (fscanf(pointer, "%d %d %d %d", &indicator, &vector[i][j], &vector[i][j+1], &vector[i][j+2]) != vcol+1) {
                printf("Error reading the coordinates");
            }

        
    }

    // printing coordinates  
    /*
    for (int i =0; i< 3; i++){
        printf("row %d:", i+1);
        for(int j=0; j < vcol; j++) {
            printf("%d \n",vector[i][j]);
             
        }
    }
    */

    // freeing the memory of the vector 
    /*
    for (int i=0; i< vrows; i++){
        free(vector[i]);

    }
    free(vector);
    */
    fclose(pointer);
   
    
    
   return vector; 
}

