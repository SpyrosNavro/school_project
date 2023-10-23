//#include "header_files/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct graph* Graph;
typedef struct node* Node;
typedef struct edge* Edge;

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





int compute_distance (Node a, Node b, int dim)
{
    int sum = 0;
    for (int i = 0; i < dim; i++) 
    {
        sum = sum + pow(a->coord[i] - b->coord[i], 2);
    }
    sum = sqrt(sum);
    return sum;
}





int** import_data(const char *file_name, int vrows)
{
    FILE* pointer;
    int** vector = NULL; // dynamilly allocated array (vector of vectors )
    // int vrows=9759;
    int vcol=3;
     
    pointer = fopen(file_name, "r");  // reading the file 
    if (pointer == NULL) 
    {
        printf("no file was found.");
        return NULL;
    }     
    
    vector = (int**) malloc(vrows*sizeof(int* )); // 2dimensional 
    
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
    for (int i=0; i< vrows; i++){
        free(vector[i]);

    }
    free(vector);
    fclose(pointer);
   
   return vector; 
}





Graph createGraph (int nedges, const char *file_name, int row, int column) 
{
    Graph graph = malloc(sizeof(*graph));
    int** data = import_data(file_name, row);
    
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
        }

        // add directed edges to each node
        for (int j = 0; j < nedges; j++)
        {
            Edge edge = malloc(sizeof(*edge));   // allocate edge
            edge->src = id;

            do 
            {
                edge->dest = rand();
                edge->distance = compute_distance(graph->nodes[id], graph->nodes[edge->dest], graph->dim);
            } while ( (edge->dest == id) && (edge->dest < 0) && (edge->dest >= graph->nnodes) );

            graph->nodes[id]->edges[j] = edge;
        }
    }

    return graph;
}





int deleteGraph(Graph graph)
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


int main(void) 
{     
    char *filename = "5k.txt";
    int vrows = 9759;
    int** vector = import_data(filename, vrows);

    for (int i =0; i< 3; i++)
    {
        printf("row %d:", i);
        printf("hello\n");

        for(int j=0; j < 3; j++) 
        {
            printf("%d \n", vector[i][j] );
            printf("hello2\n");

        }
    }

    if(vector !=NULL )
    {
        printf("Succesfully created the vector ");

        // delete vector 
        for (int i=0; i< vrows; i++)
        {
            //free(vector[i]);
        }
        //free(vector);
    }
    else{
        printf("Failed to create vector ");
    }
    

    return 0;
}