#include "../header_files/graph.h"
#include "../header_files/pqueue.h"
#include "../header_files/nnd_functions.h"



int main(int argc, char* argv[])
{
    Graph graph;
    const char* filename = "test_files/small.txt";
    //int nedges = atoi(argv[1]);
    int nedges = 4;
    int row = 10;
    int col = 3;
    int flag = 0;
    int false_edges;
    Edge old_rev[row][row];
    float distance;
    int* point;
    PQ queue[row], search_queue;
    int dest, add;
    Node search_node;
    struct checking closest;
    struct checking valise[nedges];
    int counter;

    clock_t start, end;
    double time_spent;

    printf("%d\n", argc);

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
        false_edges = 0;
        


        for (int id = 0; id < row; id++)
        {
            queue[id] = createPQueue(row);
        }


        // save old reverse neighbors
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < graph->nodes[i]->nreverse; j++)
            {
                old_rev[i][j] = graph->nodes[i]->reverse[j];
            }

            old_rev[i][graph->nodes[i]->nreverse] = NULL;
        }



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

            // NEIGHBORS
            //localJoin(graph, id, queue);  // for some weird reason this doesn't work
            int neighbor;
            for (int neighbors = 0; neighbors < nedges; neighbors++)
            {

                // count how many IS flags are false
                if (graph->nodes[id]->edges[neighbors]->is == false) 
                {
                    false_edges++;
                    counter++;
                    continue;
                }

                graph->nodes[id]->edges[neighbors]->is = false;
                
                //neighbor of node[id]
                neighbor = graph->nodes[id]->edges[neighbors]->dest;

                if (searchPQueue(queue[id], graph->nodes[neighbor]) == 1) {
                insertPQueue(queue[id], graph->nodes[neighbor], graph->nodes[id]->edges[neighbors]->distance); }

                if (searchPQueue(queue[neighbor], graph->nodes[id]) == 1) {
                insertPQueue(queue[neighbor], graph->nodes[id], graph->nodes[id]->edges[neighbors]->distance); }


                // compare with other neighbors 
                for (int i = 0; i < nedges; i++)
                {
                    int theRest = graph->nodes[id]->edges[i]->dest;
                    if (neighbor == theRest) continue;

                    distance = euclideanDistance(graph->nodes[neighbor], graph->nodes[theRest], graph->dim);

                    if (searchPQueue(queue[neighbor], graph->nodes[theRest]) == 1 ) {
                    insertPQueue(queue[neighbor], graph->nodes[theRest], distance); }

                    if (searchPQueue(queue[theRest], graph->nodes[neighbor]) == 1 ) {
                    insertPQueue(queue[theRest], graph->nodes[neighbor], distance); }
                }



                // compare with reverse neighbors
                for (int i = 0; i < graph->nodes[id]->nreverse; i++)
                {
                    int theRest = graph->nodes[id]->reverse[i]->src;

                    distance = euclideanDistance(graph->nodes[neighbor], graph->nodes[theRest], graph->dim);

                    if (searchPQueue(queue[neighbor], graph->nodes[theRest]) == 1 ) {
                    insertPQueue(queue[neighbor], graph->nodes[theRest], distance); }

                    if (searchPQueue(queue[theRest], graph->nodes[neighbor]) == 1 ) {
                    insertPQueue(queue[theRest], graph->nodes[neighbor], distance); }
                }
            }

            // REVERSE
            RevlocalJoin(graph, id, queue, &false_edges, &counter);

            if ( counter == nedges + graph->nodes[id]->nreverse ) graph->nodes[id]->same = 1;
            counter = 0;
        }



        if (false_edges == 2*(nedges*row)) flag = 1;
        printf("false edges %d %d\n",false_edges, 2*(nedges*row));

        
        // UPDATE EDGES
        if (flag == 0) flag = updateEdges(queue, graph, row, nedges);



        // UPDATE REVERSE NEIGHBORS
        if (flag == 0)
        {
            for (int id = 0; id < row; id++)
            {
                for (int i = 0; i < nedges; i++)
                {
                    dest = graph->nodes[id]->edges[i]->dest;
                    graph->nodes[dest]->reverse[(graph->nodes[dest]->nreverse)++] = graph->nodes[id]->edges[i];

                }
            }



            for (int id = 0; id < row; id++)
            {
                for (int i = 0; i < graph->nodes[id]->nreverse; i++)
                {
                    int x = 0;
                    while (old_rev[id][x] != NULL)
                    {
                        graph->nodes[id]->reverse[i]->is = true;
                        if (graph->nodes[id]->reverse[i] == old_rev[id][x])
                        {
                            graph->nodes[id]->reverse[i]->is = false;
                            break;
                        }
                        x++;
                    }
                }
            }
        }



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
    printf("x = %d y = %d", x, y);


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


    

    // SEARCH K-NEAREST NEIGHBORS
    do
    {

        // insert node[seed] into search_queue
        if (graph->nodes[seed]->checked == 0)
        {
            distance = euclideanDistance(search_node, graph->nodes[seed], graph->dim);
            //printf("id %d distance: %f\n", graph->nodes[seed]->id, distance);
            insertPQueue(search_queue, graph->nodes[seed], distance);
            graph->nodes[seed]->checked = 1;
        }


        // NEIGHBORS
        searchNeighbors(graph, search_queue, search_node, seed, nedges, &add);
    

        // REVERSE NEIGHBORS
        searchReverse(graph, search_queue, search_node, seed, &add);


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
    




    printf("\n\n\n\nPOINT:"); for (int i = 0; i < graph->dim; i++) { printf("%d ", point[i]); } printf("\n");



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