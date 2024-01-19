#include "../header_files/graph.h"
#include <stdint.h>
#include <sys/types.h>
#include <sys/syscall.h>
 
#include "../header_files/pqueue.h"
#include "../header_files/job_scheduler.h"


///////////////////////////////////////////////
/////////////////// THREADS ///////////////////
///////////////////////////////////////////////


init initQueue[50];
int initCount = 0;
int unfinished;

pthread_mutex_t mutexInit;
pthread_cond_t condInit;


void executeTask (init* task)
{
    task->taskFunction(task->graph, task->id, task->column, task->data);
}



void submitTask(init task) {
    pthread_mutex_lock(&mutexInit);
    initQueue[initCount++] = task;
    pthread_mutex_unlock(&mutexInit);
    pthread_cond_signal(&condInit);
}



void* startThread() {
    init task;
    pid_t x;

    while (1) {
        pthread_mutex_lock(&mutexInit);
        while (initCount == 0) {
            if (0 == unfinished) 
            {
                x = syscall(__NR_gettid);
            
                printf("%d LEAVING HEYYYYYYYYYYY\n", x);
                return 0;
            }
            x = syscall(__NR_gettid);

            printf("2nd while: %d id:%d\n", unfinished, x);
            pthread_cond_wait(&condInit, &mutexInit);
        }

        task = initQueue[0];
        for (int i = 0; i < initCount - 1; i++) {
            initQueue[i] = initQueue[i + 1];
        }
        initCount--;
        unfinished--;
        pthread_mutex_unlock(&mutexInit);
        
        executeTask(&task);
        
        //printf("Root: %d  \n", unfinished);

        if (0 == unfinished) {
            x = syscall(__NR_gettid);
            
            printf("%d LEAVING\n", x);
            break;
        }
    }
    return 0;
}


///////////////////////////////////////////////
///////////////////////////////////////////////
///////////////////////////////////////////////


float euclideanDistance (Node a, Node b, int dim)
{
    float sum = 0;
    sum = a->norm + b->norm;
    for (int i = 0; i < dim; i++) 
    {
        sum = sum -2*a->coord[i]*b->coord[i];
        // sum = sum + pow(a->coord[i] - b->coord[i], 2);
    }
    // sum = sqrt(sum);
     
    return sum;
}

float euclideanDistanceTest (Node a, Node b, int dim)
{
    float sum = 0;
    for (int i = 0; i < dim; i++) 
    {
        sum = sum + pow(a->coord[i] - b->coord[i], 2);
    }
    sum = sqrt(sum);
     
    return sum;
}





float manhattanDistance (Node a, Node b, int dim)
{
    float sum = 0;
    for (int i = 0; i < dim; i++) 
    {
        sum = sum + abs(a->coord[i] - b->coord[i]);
    }
     
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
                printf("Error reading the coordinates\n");
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





float** import_Binarydata(const char *file_name)
{   
    FILE* pointer;
    float** vector = NULL; // dynamilly allocated array (vector of vectors )
    int vcol=100;
    int vrows=50;

    /*  // how many rows there are in the file 
    int numberofRows=0;
    int floatSize=sizeof(float);
    int rowsize =floatSize* 100;
    int bytesRead;
    char buffer[rowsize];

    while((bytesRead= fread(buffer, 1, rowsize,file))==rowsize){
        numberofRows++;
    }
    printf("Number of rows in the binary file is: %d\n", numberofRows);
    */


    pointer = fopen(file_name, "rb");  // reading the file 
    if (pointer == NULL) 
    {
        printf("no file was found.");
        return NULL;
    }     
    // how many rows are there 

    vector = (float**) malloc(vrows*sizeof(float* ));  
    
    if (vector == NULL){
        printf("error allocating memory for the vector");
        fclose(pointer);
        return NULL;
    }
    
    for (int i =0; i< vrows; i++){
        vector[i] = (float *)malloc(vcol * sizeof(float));   
        
        if (vector[i] == NULL){
            printf("memory allocation error");
            free(vector);
            fclose(pointer);
             
        }

    }

    // save the elements of the file inside the vector (every row has three columns - its coordinates )
    uint32_t buffer;
    for(int i=0; i<vrows; i++){
        for(int j=0; j<vcol; j++){
              
            size_t items_read = fread(&buffer, sizeof(buffer),1,pointer);

            if(items_read == 1 ){
                
                vector[i][j]=buffer;
            }
            else {
                printf("could not read from the file");
                 
            }
        }

    }
    

    // printing coordinates  
    
    // for (int i =0; i< 50; i++){
    //     printf("row %d:", i+1);
    //     for(int j=0; j < 100; j++) {
    //         printf("%f \n",vector[i][j]);
    //     }
    // }
    

//     // freeing the memory of the vector 
//     // for (int i=0; i< vrows; i++){
//     //     free(vector[i]);

//     // }
//     // free(vector);
    fclose(pointer);
   
   return vector; 
}





void initialiseData (Graph graph, int id, int column, int** data)
{
    for (int j = 0; j < column; j++)
    {
        graph->nodes[id]->norm = pow(data[id][j], 2);
    }

    // printf("finished\n");
}





Graph createGraph (int nedges, const char *file_name, int row, int column) 
{
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexInit, NULL);
    pthread_cond_init(&condInit, NULL);
    int dest;

    Graph graph = malloc(sizeof(*graph));
    graph->nodes = malloc ( row * sizeof(*(graph->nodes) ));  // allocate array of nodes
    unfinished = row;

    int** data = import_data(file_name, row);

    printf("CREATE GRAPH\n\n");

    // CREATE THREADS
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_create(&th[i], NULL, &startThread, NULL) != 0) 
        {
            perror("Failed to create thread");
        }
    }
    // printf("Threads created successfully\n");
    

    graph->dim = column;
    graph->nnodes = row;
    graph->neighbors = nedges;


    // initialise NODES
    for (int id = 0; id < row; id++)
    {
        graph->nodes[id] = malloc(sizeof( *(graph->nodes[id]) ));   // allocate node
        graph->nodes[id]->id = id;
        graph->nodes[id]->reverse = malloc ( row * sizeof(*(graph->nodes[id]->reverse)) );  // allocate reverse neighbors
        graph->nodes[id]->nreverse = 0;
        graph->nodes[id]->checked = 0;
        graph->nodes[id]->same = 0;
        graph->nodes[id]->coord = malloc( column * sizeof(*(graph->nodes[id]->coord)) );
        graph->nodes[id]->norm = 0;

        for (int j = 0; j < column; j++)
        {
            graph->nodes[id]->coord[j] = data[id][j];
            //graph->nodes[id]->norm = pow(data[id][j], 2);
        }

        init task = {
            .taskFunction = &initialiseData,
            .graph = graph,
            .id = id,
            .column = column,
            .data = data
        };

        // SUBMIT TASK
        submitTask(task);
        //printf("submitted\n");
    }

    
    for (int i = 0; i < THREAD_NUM; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread");
        }
    }

    pthread_mutex_destroy(&mutexInit);
    pthread_cond_destroy(&condInit);
    


    // initialise EDGES
    for (int id = 0; id < row; id++)
    {
        // add directed edges to each node
        graph->nodes[id]->edges = malloc ( nedges * sizeof(*(graph->nodes[id]->edges)) );
                
        for (int j = 0; j < nedges; j++)
        {
            graph->nodes[id]->edges[j] = malloc(sizeof( *(graph->nodes[id]->edges[j]) ));  // allocate edge
            graph->nodes[id]->edges[j]->src = id;
            graph->nodes[id]->edges[j]->is = true;
            graph->nodes[id]->edges[j]->rev_is = true;

            do 
            {
                // rand in range [0, rows-1]
                // rand() % (max_number + 1 - minimum_number) + minimum_number
                graph->nodes[id]->edges[j]->dest = rand()%row; 

                dest = graph->nodes[id]->edges[j]->dest;
            }
            while ( (dest == id) || (dest < 0) || (dest >= graph->nnodes) );

            // compute distance
            graph->nodes[id]->edges[j]->distance = euclideanDistance(graph->nodes[id], graph->nodes[dest], graph->dim);

            // save reverse edge to destination
            graph->nodes[dest]->reverse[graph->nodes[dest]->nreverse] = graph->nodes[id]->edges[j];
            graph->nodes[dest]->nreverse++;
        }
    }
    for (int i = 0; i < row; i++)
    {
        free(data[i]);
    }
    free(data);
    return graph;
}




Graph createGraphTest (int nedges, const char *file_name, int row, int column) 
{
    int dest;

    Graph graph = malloc(sizeof(*graph));
    graph->nodes = malloc ( row * sizeof(*(graph->nodes) ));  // allocate array of nodes
    unfinished = row;

    int** data = import_data(file_name, row);

    printf("CREATE GRAPH\n\n");

    graph->dim = column;
    graph->nnodes = row;
    graph->neighbors = nedges;

    // initialise NODES
    for (int id = 0; id < row; id++)
    {
        graph->nodes[id] = malloc(sizeof( *(graph->nodes[id]) ));   // allocate node
        graph->nodes[id]->id = id;
        graph->nodes[id]->reverse = malloc ( row * sizeof(*(graph->nodes[id]->reverse)) );  // allocate reverse neighbors
        graph->nodes[id]->nreverse = 0;
        graph->nodes[id]->checked = 0;
        graph->nodes[id]->same = 0;
        graph->nodes[id]->coord = malloc( column * sizeof(*(graph->nodes[id]->coord)) );
        graph->nodes[id]->norm = 0;

        for (int j = 0; j < column; j++)
        {
            graph->nodes[id]->coord[j] = data[id][j];
            graph->nodes[id]->norm = pow(data[id][j], 2);
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
            graph->nodes[id]->edges[j]->is = true;
            graph->nodes[id]->edges[j]->rev_is = true;

            do 
            {
                // rand in range [0, rows-1]
                // rand() % (max_number + 1 - minimum_number) + minimum_number
                graph->nodes[id]->edges[j]->dest = rand()%row; 

                dest = graph->nodes[id]->edges[j]->dest;
            }
            while ( (dest == id) || (dest < 0) || (dest >= graph->nnodes) );

            // compute distance
            graph->nodes[id]->edges[j]->distance = euclideanDistance(graph->nodes[id], graph->nodes[dest], graph->dim);

            // save reverse edge to destination
            graph->nodes[dest]->reverse[graph->nodes[dest]->nreverse] = graph->nodes[id]->edges[j];
            graph->nodes[dest]->nreverse++;
        }
    }
    for (int i = 0; i < row; i++)
    {
        free(data[i]);
    }
    free(data);
    return graph;
}
 




void deleteGraph(Graph graph)
{   
    for (int i = 0; i < graph->nnodes; i++)
    {
        for (int j = 0; j < graph->neighbors; j++)
        {
            free(graph->nodes[i]->edges[j]);
        }
        free(graph->nodes[i]->reverse);
        free(graph->nodes[i]->coord);
        free(graph->nodes[i]->edges);
        free(graph->nodes[i]);
    }
    free(graph->nodes);

    free(graph);
}




