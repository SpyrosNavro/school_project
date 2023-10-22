#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nnodes 6

struct Graph {
    struct Node* nodes[nnodes];
    int dim;
};

// structure of nodes 
struct Node {
    int* coord;  // coordinates of n-dimentional point
    int id;    // id of point 
    // struct Node* next;  not useful for now
};

// structure of edge
struct Edge {
    int src, dest, weight;
};



/*

struct Graph* createGraph (int nedges, const char *file_name) 
{
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    // atoi: char => int
    // fgetc: obtain input single character at a time. returns the ASCII code of the character read. it moves to the next character by itself

    // initialise nodes 
    for (int i = 0; i < nnodes; i++) {
    //    graph->nodes[i]->x = rand();
    //    graph->nodes[i]->y = rand();
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
*/


int** import_data(const char *file_name)
{
    FILE* pointer;
     
    pointer = fopen(file_name, "r");  // reading the file 
    if (pointer == NULL) 
    {
        printf("no file was found.");
        //return 1;
    }
     
    int** vector = NULL; // dynamilly allocated array (vector of vectors )
    int vrows=9759;
    int vcol=3;
     
    
    vector = (int**) malloc(vrows * sizeof(int * )); // 2dimensional 
    if (vector == NULL){
        printf("error allocating memory for the vector");
        fclose(pointer);
        //return 1;
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

