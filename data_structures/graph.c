#include "../header_files/graph.h"





float compute_distance (Node a, Node b, int dim)
{
    float sum = 0;
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
    // for (int i=0; i< vrows; i++){
    //     free(vector[i]);

    // }
    // free(vector);
    fclose(pointer);
   
   return vector; 
}





Graph createGraph (int nedges, const char *file_name, int row, int column) 
{
    Graph graph = malloc(sizeof(*graph));
    graph->nodes = malloc ( row * sizeof(*(graph->nodes) ));  // allocate array of nodes
    graph->checked = calloc(row, sizeof( *(graph->checked) ));
    int dest;

    int** data = import_data(file_name, row);
    
    graph->dim = column;
    graph->nnodes = row;
    graph->neighbors = nedges;
    
    // initialise NODES
    for (int id = 0; id < row; id++)
    { 
        graph->nodes[id] = malloc(sizeof( *(graph->nodes[id]) ));   // allocate node
        graph->nodes[id]->id = id;
        graph->nodes[id]->reverse = malloc ( nedges * sizeof(*(graph->nodes[id]->reverse)) );  // allocate reverse neighbors
        graph->nodes[id]->nreverse = 0;


        graph->checked[id] = 0;
        
        for (int j = 0; j < column; j++)
        {
            graph->nodes[id]->coord = (int*)malloc(column * sizeof( *(graph->nodes[id]->coord) ));
            *(graph->nodes[id]->coord + j) = data[id][j];   // put data in node
            printf("id%d data: %d\n", id, data[id][j]);
        }
    }



    // initialise EDGES
    for (int id = 0; id < row; id++)
    {
        // add directed edges to each node
        graph->nodes[id]->edges = malloc ( nedges * sizeof(*(graph->nodes[id]->edges)) );
                
        for (int j = 0; j < nedges; j++)
        {
            graph->nodes[id]->edges[j] = malloc(sizeof( *(graph->nodes[id]->edges[j]) ));  // allocate edge
            graph->nodes[id]->edges[j]->src = id;

            do 
            {
                // rand in range [0, rows-1]
                // rand() % (max_number + 1 - minimum_number) + minimum_number
                graph->nodes[id]->edges[j]->dest = rand()%row; 

                dest = graph->nodes[id]->edges[j]->dest;
            }
            while ( (dest == id) || (dest < 0) || (dest >= graph->nnodes) );

            // compute distance
            graph->nodes[id]->edges[j]->distance = compute_distance(graph->nodes[id], graph->nodes[graph->nodes[id]->edges[j]->dest], graph->dim);

            // save reverse edge to destination
            graph->nodes[dest]->reverse[graph->nodes[dest]->nreverse] = graph->nodes[id]->edges[j];
            graph->nodes[dest]->nreverse = graph->nodes[dest]->nreverse + 1;
            
            // realloc array of reverse neighbors
            if (graph->nodes[dest]->nreverse%nedges == 0) 
            {
                graph->nodes[dest]->reverse = realloc ( graph->nodes[dest]->reverse, 2*graph->nodes[dest]->nreverse*sizeof(Edge*) );
            }
        }
    }
    return graph;
}





int deleteGraph(Graph graph)
{   
    for (int i = 0; i < graph->nnodes - 1; i++)
    {
        for (int j = 0; j < graph->neighbors; j++)
        {
            free(graph->nodes[i]->edges[j]);
        }
        free(graph->nodes[i]);
    }

    free(graph);
    return 1;
}





// int main(void) 
// {     
//     const char *filename = "5k.txt";
//     int vrows = 9759;
//     int column = 3;
//     int nedges = 2;
//     int** vector = import_data(filename, vrows);
//     Graph graph;

//     // for (int i =0; i< 3; i++)
//     // {
//     //     printf("row %d:\n", i);

//     //     for(int j=0; j < 3; j++) 
//     //     {
//     //         printf("%d \n", vector[i][j] );

//     //     }
//     // }
    
//     if(vector !=NULL )
//     {
//         printf("Succesfully created the vector\n");

//         // delete vector 
//         for (int i=0; i< vrows; i++)
//         {
//             free(vector[i]);
//         }
//         free(vector);
//     }
//     else{
//         printf("Failed to create vector ");
//     }

//     graph = createGraph(nedges, filename, vrows, column);

//     if (deleteGraph(graph) == 1)
//     {
//         printf("delete was successful");
//     }

//     return 0;
// }