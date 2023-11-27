#include "../header_files/graph.h"
#include "../header_files/pqueue.h"
#include "../header_files/nnd_functions.h"

// argc the number of command line arguments 
// argv is the array of strings containing the arguments 

int main(int argc, char* argv[])
{   
    //for (int i=0; i<argc; i++){
    //    printf("Argument %d= %s\n",i, argv[i]);   // argv[0]=./nndescent , arg[1]= first arguments
    //}

    Graph graph;
    const char* filename = "test_files/1k.txt";
    int nedges = 2;
    int row = 6673;
    int col = 3;
    int flag = 0;
    float distance;
    int* point;
    PQ queue[row], search_queue;
    int add;
    int temp[row];
    Node search_node;
    struct checking closest;
    struct checking valise[nedges];

    clock_t start, end;
    double time_spent;


    start = clock();
    graph = createGraph(nedges, filename, row, col);
    srand(time(0));    


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
        
        // PUT DISTANCES IN PRIORITY QUEUE
        for (int id = 0; id < row; id++)
        {
            // NEIGHBORS
            check_neighbors(graph, id, queue);

            // REVERSE NEIGHBORS
            check_reverse_neighbors(graph, id, queue);
        }


        // INITIALISE REVERSE
        for (int id = 0; id < row; id++)
        {
            temp[id] = 0;
        }

        // UPDATE EDGES
        flag = update_edges(queue, graph, row, nedges, temp);
        
        
        if (flag == 0)
        {
            for (int id = 0; id < row; id++)
            {
                graph->nodes[id]->nreverse = temp[id];
            }
        }

    } while (flag == 0);



    printf("\nFINAL\n");
    for (int id = 0; id < row; id++)
    {
        for (int i = 0; i < nedges; i++)
        {
            //printf("id %d => %d\n", graph->nodes[id]->id, graph->nodes[id]->edges[i]->dest);
            
        }
    }

    for (int id = 0; id < row; id++)
    {
        for (int i = 0; i < graph->nodes[id]->nreverse; i++)
        {
            printf("id %d has reverse neighbor %d\n", id, graph->nodes[id]->reverse[i]->src);
        }
    }

    // free queue
    for (int id = 0; id < row; id++)
    {
        destroyPQueue(queue[id]);
    }



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


    printf("\n\n\n");

    // SEARCH K-NEAREST NEIGHBORS
    do
    {

        // insert node[seed] into search_queue
        if (graph->nodes[seed]->checked == 0)
        {
            distance = compute_distance(search_node, graph->nodes[seed], graph->dim);

            insertPQueue(search_queue, graph->nodes[seed], distance);
            graph->nodes[seed]->checked = 1;
        }


        // NEIGHBORS
        search_neighbors(graph, search_queue, search_node, seed, nedges, &add);
        

        // REVERSE NEIGHBORS
        search_reverse_neighbors(graph, search_queue, search_node, seed, &add);

        // Truncate pool to k-top 
        for (int i = 0; i < nedges; i++)
        {
            valise[i] = extractMin(search_queue);
        }
        destroyPQueue(search_queue);
        search_queue = createPQueue(row);
        for (int i = 0; i < nedges; i++)
        {
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


    } while (flag == 0);
    




    printf("\nPOINT:"); for (int i = 0; i < graph->dim; i++) { printf("%d ", point[i]); } printf("\n");



    printf("K-NEAREST NODES:\n");

    for (int i = 0; i < nedges; i++)
    {
        for (int j = 0; j < graph->dim; j++)
        {
            printf("%d ", valise[i].node->coord[j]);
        }
        printf(" distance: %f\n", valise[i].distance);
    }
    
    deleteGraph(graph);
    end = clock();
    time_spent = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\nTime needed for action: %fsec\n", time_spent);
    
    return 0;
}