#include "../header_files/graph.h"
#include "../header_files/pqueue.h"
#include "../header_files/nnd_functions.h"




taskDis disQueue[50];
int disCount = 0;
int unfinishedD;

pthread_mutex_t mutexDis;
pthread_cond_t condDis;


void executeTaskD(taskDis* task) {
    task->taskFunction(task->graph, task->id, task->pq);
}


void submitTaskD(taskDis task) {
    pthread_mutex_lock(&mutexDis);
    disQueue[disCount++] = task;
    pthread_mutex_unlock(&mutexDis);
    pthread_cond_signal(&condDis);
}



void* startThreadD() {
    taskDis task;
    //pid_t x;

    while (1) {
        pthread_mutex_lock(&mutexDis);
        while (disCount == 0) {
            if (0 == unfinishedD) 
            {            
                //printf("%d LEAVING HEYYYYYYYYYYY\n", x);
                return 0;
            }

            //printf("2nd while: %d id:%d\n", unfinishedD, x);
            pthread_cond_wait(&condDis, &mutexDis);
        }

        task = disQueue[0];
        for (int i = 0; i < disCount - 1; i++) {
            disQueue[i] = disQueue[i + 1];
        }
        disCount--;
        unfinishedD--;
        pthread_mutex_unlock(&mutexDis);
        
        executeTaskD(&task);
        
        //printf("Root: %d  \n", unfinished);

        if (0 == unfinishedD) {          
            //printf("%d LEAVING\n", x);
            break;
        }
    }
    return 0;
}






int main(void)
{
    Graph graph;
    char filename[100];
    const char* file = "configuration.txt";
    //int nedges = atoi(argv[1]);
    int nedges;
    int row;
    int col;
    int flag = 0;
    float D;
    // int false_edges;
    //Edge old_rev[row][row];
    float distance;
    int* point;
    PQ search_queue;
    int dest, add;
    Node search_node;
    struct checking closest;
    clock_t start, end;
    double time_spent;
    // pthread_t th[THREAD_NUM];

    FILE* pointer = fopen(file, "r");
    if (pointer == NULL)
    {
        printf("Couldn't open file\n");
        return 0;
    }
    fscanf(pointer, "%s %d %d %d %f", filename, &row, &col, &nedges, &D);
    fclose(pointer);

    PQ queue[row];
    struct checking valise[nedges];

    printf("%s %d %d %d %f\n", filename, row, col, nedges, D);

    start = clock();
    graph = createGraph(nedges, filename, row, col);
    srand(time(0));    
    
    // int changes = 0;
    // float D = 0.1;
    // create Priority Queue for every node
    for (int id = 0; id < row; id++)
    {
        queue[id] = createPQueue(row);
    }



    printf("\n\nNNDESCENT\n\n");
    int i = 0;
    // ITERATIONS
    do
    {
        printf("iteration: %d\n", i++);
        add = 0;
        // false_edges = 0;
        
        for (int id = 0; id < row; id++)
        {
            queue[id] = createPQueue(row);
        }

        // THREADS
        // for (int i = 0; i < THREAD_NUM; i++)
        // {
        //     if (pthread_create(&th[i], NULL, &startThread, NULL) != 0) 
        //     {
        //         perror("Failed to create thread");
        //     }
        // }
        // unfinishedD = row;

        // PUT DISTANCES IN PRIORITY QUEUE
        for (int id = 0; id < row; id++)
        {
            // NEIGHBORS
            //checkNeighbors(graph, id, queue);

            // REVERSE NEIGHBORS
            //checkReverse(graph, id, queue);

            //====================================//
            //============ LOCAL JOIN ============//
            //====================================//

            // taskDis task = {
            //     .taskFunction = &localJoin,
            //     .graph = graph,
            //     .id = id,
            //     .pq = queue
            // };

            // SUBMIT TASK
            // submitTaskD(task);

            // taskDis task = {
            //     .taskFunction = &RevlocalJoin,
            //     .graph = graph,
            //     .id = id,
            //     .pq = queue
            // };

            // SUBMIT TASK
            // submitTaskD(task);

            // NEIGHBORS
            localJoin(graph, id, queue);

            // REVERSE NEIGHBORS
            RevlocalJoin(graph, id, queue);
        }



        // for (int i = 0; i < THREAD_NUM; i++)
        // {
        //     if (pthread_join(th[i], NULL) != 0)
        //     {
        //         perror("Failed to join thread");
        //     }
        // }

        // if (false_edges == 2*(nedges*row)) flag = 1;
        
        // UPDATE EDGES
        if (flag == 0) flag = updateEdges(queue, graph, row, nedges);

        // printf("D*row*nedges= %f   ",D*row*nedges);
        // // EARLY TERMINATION
        // if (changes < D*row*nedges || changes == 0) flag =1;
        // printf("changes= %d\n",changes);

        // UPDATE REVERSE EDGES
        // if (changes > 0)
        // {
        for (int id = 0; id < row; id++)
        {
            for (int i = 0; i < nedges; i++)
            {
                dest = graph->nodes[id]->edges[i]->dest;
                graph->nodes[dest]->reverse[graph->nodes[dest]->nreverse] = graph->nodes[id]->edges[i];
                graph->nodes[dest]->reverse[graph->nodes[dest]->nreverse++]->rev_is = true;
                
            }
        }


            // for (int id = 0; id < row; id++)
            // {
            //     for (int i = 0; i < graph->nodes[id]->nreverse; i++)
            //     {
            //         int x = 0;
            //         while (old_rev[id][x] != NULL)
            //         {
            //             if (graph->nodes[id]->reverse[i]->src == old_rev[id][x]->src)
            //             {
            //                 graph->nodes[id]->reverse[i]->rev_is = false;
            //                 break;
            //             }
            //             else {
            //                 changes++;
            //             }
            //             x++;
            //         }
            //     }
            // }
        // }



        for (int id = 0; id < row; id++)
        {
            destroyPQueue(queue[id]);
        }

        printf("end\n");

    } while (flag == 0);


    //=======================================//
    //=============== RESULTS ===============//
    //=======================================//

    printf("\nFINAL\n");
    int x = 0;
    for (int id = 0; id < row; id++)
    {
        for (int i = 0; i < nedges; i++)
        {
            printf("id %d => %d\n", graph->nodes[id]->id, graph->nodes[id]->edges[i]->dest); 
            x++;
        }
    }

    int y = 0;
    for (int id = 0; id < row; id++)
    {
        printf("id %d nreverse:%d\n", id, graph->nodes[id]->nreverse);
        for (int i = 0; i < graph->nodes[id]->nreverse; i++)
        {
            printf("reverse:%d\n", graph->nodes[id]->reverse[i]->src);
            y++;
        }
    }
    printf("x = %d y = %d\n", x, y);

    //=====================================================================================//
    //=====================================   SEARCH   ====================================//
    //=====================================================================================//

    flag = 0;
    add = 0;

    // random point for search
    point = malloc(graph->dim * sizeof(*point));
    search_node = malloc(sizeof(*search_node));
    for (int i = 0; i < graph->dim; i++)
    {
        point[i] = rand()%21;
    }
    search_node->coord = point;


    // we start from this random node of the graph
    int seed = rand()%row;

    // create Priority Queue for search
    search_queue = createPQueue(row);


    int old_seed;
    // SEARCH K-NEAREST NEIGHBORS
    do
    {
        old_seed = seed;
        printf("seed: %d\n", seed);
        // insert node[seed] into search_queue
        if (graph->nodes[seed]->checked == 0)  // the mistake is here 
        {
            distance = euclideanDistance(search_node, graph->nodes[seed], graph->dim);

            if (searchPQueue(search_queue, graph->nodes[seed]) == 1) {
            insertPQueue(search_queue, graph->nodes[seed], distance); }
            
            graph->nodes[seed]->checked = 1;
        }


        // NEIGHBORS
        searchNeighbors(graph, search_queue, search_node, seed, nedges, &add);
    

        // REVERSE NEIGHBORS
        searchReverse(graph, search_queue, search_node, seed, &add);

        

        // Truncate pool to k-top 
        for (int i = 0; i < nedges; i++)
        {
            printf("extract\n");
            valise[i] = extractMin(search_queue);
        }
        destroyPQueue(search_queue);
        search_queue = createPQueue(row);
        for (int i = 0; i < nedges; i++)
        {
            printf("insert %d\n", valise[i].node->id);

            insertPQueue(search_queue, valise[i].node, valise[i].distance);
        }


        closest = valise[0];


        // have we seen all neighbors?
        if (add == nedges + graph->nodes[seed]->nreverse)
        {
            flag = 1;
        }
        add = 0;
        seed = closest.node->id;

        if (old_seed == seed) flag = 1;


    } while (flag == 0);
    


    printf("\n\n\n\nPOINT:"); for (int i = 0; i < graph->dim; i++) { printf("%d ", point[i]); } printf("\n");

    struct checking result;

    printf("K-NEAREST NODES:\n");

    for (int i = 0; i < nedges; i++)
    {
        result = extractMin(search_queue);

        for (int j = 0; j < graph->dim; j++)
        {
            printf("%d ", result.node->coord[j]);
        }
        printf(" distance: %f\n", result.distance);
    }
    
    deleteGraph(graph);
    destroyPQueue(search_queue);
    end = clock();
    time_spent = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\nTime needed for action: %fsec\n", time_spent);
    
    return 0;
}